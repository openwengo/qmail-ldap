#include <unistd.h>
#include "stralloc.h"
#include "substdio.h"
#include "qmail.h"
#include "now.h"
#include "str.h"
#include "fmt.h"
#include "env.h"
#include "sig.h"
#include "rcpthosts.h"
#include "auto_qmail.h"
#include "readwrite.h"
#include "control.h"
#include "received.h"
#include "scan.h"

void badproto() { _exit(100); }
void resources() { _exit(111); }

int safewrite(int fd, void *buf, int len)
{
  int r;
  r = write(fd,buf,len);
  if (r <= 0) _exit(0);
  return r;
}

char ssoutbuf[256];
substdio ssout = SUBSTDIO_FDBUF(safewrite,1,ssoutbuf,sizeof ssoutbuf);

int saferead(int fd, void *buf, int len)
{
  int r;
  substdio_flush(&ssout);
  r = read(fd,buf,len);
  if (r <= 0) _exit(0);
  return r;
}

char ssinbuf[512];
substdio ssin = SUBSTDIO_FDBUF(saferead,0,ssinbuf,sizeof ssinbuf);

unsigned long getlen(void)
{
  unsigned long len = 0;
  char ch;
  for (;;) {
    substdio_get(&ssin,&ch,1);
    if (len > 200000000) resources();
    if (ch == ':') return len;
    if (ch < '0' || ch > '9') badproto();
    len = 10 * len + (ch - '0');
  }
}

void getcomma()
{
  char ch;
  substdio_get(&ssin,&ch,1);
  if (ch != ',') badproto();
}

unsigned long databytes = 0;
unsigned long bytestooverflow = 0;
struct qmail qq;

char buf[1000];
char buf2[100];

const char *remotehost;
const char *remoteinfo;
const char *remoteip;
const char *local;

stralloc failure = {0};

char *relayclient;
unsigned int relayclientlen;

int main()
{
  char ch;
  unsigned int i;
  unsigned long biglen;
  unsigned long len;
  int flagdos;
  int flagsenderok;
  int flagbother;
  int flagnolocal = 0;
  unsigned long qp;
  const char *result;
  char *x;
 
  sig_pipeignore();
  sig_alarmcatch(resources);
  alarm(3600);
 
  if (chdir(auto_qmail) == -1) resources();
 
  if (control_init() == -1) resources();
  if (rcpthosts_init() == -1) resources();
  relayclient = env_get("RELAYCLIENT");
  relayclientlen = relayclient ? str_len(relayclient) : 0;
 
  if (control_readulong(&databytes,"control/databytes") == -1) resources();
  x = env_get("DATABYTES");
  if (x) scan_ulong(x,&databytes);
  if (!(databytes + 1)) --databytes;
 
  remotehost = env_get("TCPREMOTEHOST");
  if (!remotehost) remotehost = "unknown";
  remoteinfo = env_get("TCPREMOTEINFO");
  remoteip = env_get("TCPREMOTEIP");
  if (!remoteip) remoteip = "unknown";
  local = env_get("TCPLOCALHOST");
  if (!local) local = env_get("TCPLOCALIP");
  if (!local) local = "unknown";
  if (env_get("NOLOCAL")) flagnolocal = 1;
 
  flagdos = 0;
  for (;;) {
    if (!stralloc_copys(&failure,"")) resources();
    flagsenderok = 1;
 
    len = getlen();
    if (len == 0) badproto();
 
    if (databytes) bytestooverflow = databytes + 1;
    if (qmail_open(&qq) == -1) resources();
    qp = qmail_qp(&qq);
 
    substdio_get(&ssin,&ch,1);
    --len;
    if (ch == 10) flagdos = 0;
    else if (ch == 13) flagdos = 1;
    else badproto();
 
    received(&qq,"QMTP",local,remoteip,remotehost,remoteinfo,(char *) 0,(char *) 0,(char *) 0);
 
    /* XXX: check for loops? only if len is big? */
 
    if (flagdos)
      while (len > 0) {
        substdio_get(&ssin,&ch,1);
        --len;
        while ((ch == 13) && len) {
          substdio_get(&ssin,&ch,1);
          --len;
          if (ch == 10) break;
          if (bytestooverflow) if (!--bytestooverflow) qmail_fail(&qq);
          qmail_put(&qq,"\015",1);
        }
        if (bytestooverflow) if (!--bytestooverflow) qmail_fail(&qq);
        qmail_put(&qq,&ch,1);
      }
    else {
      if (databytes)
        if (len > databytes) {
          bytestooverflow = 0;
          qmail_fail(&qq);
        }
      while (len > 0) { /* XXX: could speed this up, obviously */
        substdio_get(&ssin,&ch,1);
        --len;
        qmail_put(&qq,&ch,1);
      }
    }
    getcomma();
 
    len = getlen();
 
    if (len >= 1000) {
      buf[0] = 0;
      flagsenderok = 0;
      for (i = 0;i < len;++i)
        substdio_get(&ssin,&ch,1);
    }
    else {
      for (i = 0;i < len;++i) {
        substdio_get(&ssin,buf + i,1);
        if (!buf[i]) flagsenderok = 0;
      }
      buf[len] = 0;
    }
    getcomma();
 
    flagbother = 0;
    qmail_from(&qq,buf);
    if (!flagsenderok) qmail_fail(&qq);
 
    biglen = getlen();
    while (biglen > 0) {
      if (!stralloc_append(&failure,"")) resources();
 
      len = 0;
      for (;;) {
        if (!biglen) badproto();
        substdio_get(&ssin,&ch,1);
        --biglen;
        if (len > 200000000) resources();
        if (ch == ':') break;
	if (ch < '0' || ch > '9') badproto();
        len = 10 * len + (ch - '0');
      }
      if (len >= biglen) badproto();
      if (len + relayclientlen >= 1000) {
        failure.s[failure.len - 1] = 'L';
        for (i = 0;i < len;++i)
          substdio_get(&ssin,&ch,1);
      }
      else {
        for (i = 0;i < len;++i) {
          substdio_get(&ssin,buf + i,1);
          if (!buf[i]) failure.s[failure.len - 1] = 'N';
        }
        buf[len] = 0;
 
        if (relayclient)
          str_copy(buf + len,relayclient);
        else
          switch(rcpthosts(buf,len,flagnolocal)) {
            case -1: resources();
            case 0: failure.s[failure.len - 1] = 'D';
          }
 
        if (!failure.s[failure.len - 1]) {
          qmail_to(&qq,buf);
          flagbother = 1;
        }
      }
      getcomma();
      biglen -= (len + 1);
    }
    getcomma();
 
    if (!flagbother) qmail_fail(&qq);
    result = qmail_close(&qq);
    if (!flagsenderok) result = "Dunacceptable sender (#5.1.7)";
    if (databytes) if (!bytestooverflow) result = "Dsorry, that message size exceeds my databytes limit (#5.3.4)";
 
    if (*result)
      len = str_len(result);
    else {
      /* success! */
      len = 0;
      len += fmt_str(buf2 + len,"Kok ");
      len += fmt_ulong(buf2 + len,(unsigned long) now());
      len += fmt_str(buf2 + len," qp ");
      len += fmt_ulong(buf2 + len,qp);
      buf2[len] = 0;
      result = buf2;
    }
      
    len = fmt_ulong(buf,len);
    buf[len++] = ':';
    len += fmt_str(buf + len,result);
    buf[len++] = ',';
 
    for (i = 0;i < failure.len;++i)
      switch(failure.s[i]) {
        case 0:
          substdio_put(&ssout,buf,len);
          break;
        case 'D':
          substdio_puts(&ssout,"66:Dsorry, that domain isn't in my list of allowed rcpthosts (#5.7.1),");
          break;
        default:
          substdio_puts(&ssout,"46:Dsorry, I can't handle that recipient (#5.1.3),");
          break;
      }
 
    /* ssout will be flushed when we read from the network again */
  }
  /* NOTREACHED */
  return 0;
}
