#include <unistd.h>
#include "substdio.h"
#include "readwrite.h"
#include "wait.h"
#include "exit.h"
#include "fork.h"
#include "fd.h"
#include "qmail.h"
#include "auto_qmail.h"

#ifdef ALTQUEUE
#include "env.h"

static char *binqqargs[2] = { 0, 0 } ;

static void
setup_qqargs(void)
{
  if(!binqqargs[0])
    binqqargs[0] = (char *)env_get("QMAILQUEUE");
  if(!binqqargs[0])
    binqqargs[0] = (char *)"bin/qmail-queue";
}

#else
static char *binqqargs[2] = { "bin/qmail-queue", 0 } ;
#endif


int qmail_open(qq)
struct qmail *qq;
{
  int pim[2];
  int pie[2];
  int pierr[2];

#ifdef ALTQUEUE
  setup_qqargs();
#endif

  if (pipe(pim) == -1) return -1;
  if (pipe(pie) == -1) { close(pim[0]); close(pim[1]); return -1; }
  if (pipe(pierr) == -1) {
    close(pim[0]); close(pim[1]);
    close(pie[0]); close(pie[1]);
    return -1;
  }
 
  switch(qq->pid = vfork()) {
    case -1:
      close(pim[0]); close(pim[1]);
      close(pie[0]); close(pie[1]);
      close(pierr[0]); close(pierr[1]);
      return -1;
    case 0:
      close(pim[1]);
      close(pie[1]);
      close(pierr[0]);
      if (fd_move(0,pim[0]) == -1) _exit(120);
      if (fd_move(1,pie[0]) == -1) _exit(120);
      if (fd_move(4,pierr[1]) == -1) _exit(120);
      if (chdir(auto_qmail) == -1) _exit(61);
      execv(*binqqargs,binqqargs);
      _exit(120);
  }

  qq->fdm = pim[1]; close(pim[0]);
  qq->fde = pie[1]; close(pie[0]);
  qq->fderr = pierr[0]; close(pierr[1]);
  substdio_fdbuf(&qq->ss,subwrite,qq->fdm,qq->buf,sizeof(qq->buf));
  qq->flagerr = 0;
  return 0;
}

int qmail_remote(qq, host)
struct qmail *qq;
char *host;
{
  int pim[2];
  int pie[2];
  char *(args[3]);

  args[0] = (char *)"bin/qmail-qmqpc";
  args[1] = host;
  args[2] = 0;

  if (pipe(pim) == -1) return -1;
  if (pipe(pie) == -1) { close(pim[0]); close(pim[1]); return -1; }
 
  switch(qq->pid = vfork()) {
    case -1:
      close(pim[0]); close(pim[1]);
      close(pie[0]); close(pie[1]);
      return -1;
    case 0:
      close(pim[1]);
      close(pie[1]);
      if (fd_move(0,pim[0]) == -1) _exit(120);
      if (fd_move(1,pie[0]) == -1) _exit(120);
      if (chdir(auto_qmail) == -1) _exit(61);
      execv(*args,args);
      _exit(120);
  }

  qq->fdm = pim[1]; close(pim[0]);
  qq->fde = pie[1]; close(pie[0]);
  substdio_fdbuf(&qq->ss,subwrite,qq->fdm,qq->buf,sizeof(qq->buf));
  qq->flagerr = 0;
  return 0;
}

unsigned long qmail_qp(qq) struct qmail *qq;
{
  return qq->pid;
}

void qmail_fail(qq) struct qmail *qq;
{
  qq->flagerr = 1;
}

void qmail_put(qq,s,len) struct qmail *qq; const char *s; int len;
{
  if (!qq->flagerr) if (substdio_put(&qq->ss,s,len) == -1) qq->flagerr = 1;
}

void qmail_puts(qq,s) struct qmail *qq; const char *s;
{
  if (!qq->flagerr) if (substdio_puts(&qq->ss,s) == -1) qq->flagerr = 1;
}

void qmail_from(qq,s) struct qmail *qq; const char *s;
{
  if (substdio_flush(&qq->ss) == -1) qq->flagerr = 1;
  close(qq->fdm);
  substdio_fdbuf(&qq->ss,subwrite,qq->fde,qq->buf,sizeof(qq->buf));
  qmail_put(qq,"F",1);
  qmail_puts(qq,s);
  qmail_put(qq,"",1);
}

void qmail_to(qq,s) struct qmail *qq; const char *s;
{
  qmail_put(qq,"T",1);
  qmail_puts(qq,s);
  qmail_put(qq,"",1);
}

static char errstr[256];

const char *qmail_close(qq)
struct qmail *qq;
{
  int wstat;
  int exitcode;
  size_t len;
  char ch;

  qmail_put(qq,"",1);
  if (!qq->flagerr) if (substdio_flush(&qq->ss) == -1) qq->flagerr = 1;
  close(qq->fde);

  substdio_fdbuf(&qq->ss,subread,qq->fderr,qq->buf,sizeof(qq->buf));
  for (len = 0; substdio_bget(&qq->ss, &ch, 1) && len < 255; len++)
    errstr[len]=ch;
  if (len > 0) errstr[len]='\0';
  close(qq->fderr);


  if ((unsigned long)wait_pid(&wstat,qq->pid) != qq->pid)
    return "Zqq waitpid surprise (#4.3.0)";
  if (wait_crashed(wstat))
    return "Zqq crashed (#4.3.0)";
  exitcode = wait_exitcode(wstat);

  switch(exitcode) {
    case 115: /* compatibility */
    case 11: return "Denvelope address too long for qq (#5.1.3)";
    case 31: return "Dmail server permanently rejected message (#5.3.0)";
    case 51: return "Zqq out of memory (#4.3.0)";
    case 52: return "Zqq timeout (#4.3.0)";
    case 53: return "Zqq write error or disk full (#4.3.0)";
    case 0: if (!qq->flagerr) return ""; /* fall through */
    case 54: return "Zqq read error (#4.3.0)";
    case 55: return "Zqq unable to read configuration (#4.3.0)";
    case 56: return "Zqq trouble making network connection (#4.3.0)";
    case 61: return "Zqq trouble in home directory (#4.3.0)";
    case 63:
    case 64:
    case 65:
    case 66:
    case 62: return "Zqq trouble creating files in queue (#4.3.0)";
    case 71: return "Zmail server temporarily rejected message (#4.3.0)";
    case 72: return "Zconnection to mail server timed out (#4.4.1)";
    case 73: return "Zconnection to mail server rejected (#4.4.1)";
    case 74: return "Zcommunication with mail server failed (#4.4.2)";
    case 91: /* fall through */
    case 81: return "Zqq internal bug (#4.3.0)";
    case 120: return "Zunable to exec qq (#4.3.0)";
    case 82:
      if (len > 2)
	return errstr;
    default:
      if ((exitcode >= 11) && (exitcode <= 40))
	return "Dqq permanent problem (#5.3.0)";
      return "Zqq temporary problem (#4.3.0)";
  }
}
