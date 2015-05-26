#include "auto_qmail_inst.h"
#include "auto_split.h"
#include "auto_uids.h"
#include "auto_userl.h"
#include "fmt.h"
#include "fifo.h"

char buf[100 + FMT_ULONG];

extern void c(const char *, const char *, const char *, int, int, int);
extern void C(const char *, const char *, const char *, const char *,
 int, int, int);
extern void d(const char *, const char *, int, int, int);
extern void h(const char *, int, int, int);
extern void l(const char *, const char *, const char *, const char *,
 int, int, int);
extern void p(const char *, const char *, int, int, int);
extern void z(const char *, const char *, int, int, int, int);

void dsplit(base,uid,mode)
char *base; /* must be under 100 bytes */
int uid;
int mode;
{
  char *x;
  unsigned long i;

  d(auto_qmail_inst,base,uid,auto_gidq,mode);

  for (i = 0;i < auto_split;++i) {
    x = buf;
    x += fmt_str(x,base);
    x += fmt_str(x,"/");
    x += fmt_ulong(x,i);
    *x = 0;

    d(auto_qmail_inst,buf,uid,auto_gidq,mode);
  }
}

void hier()
{
  h(auto_qmail_inst,auto_uido,auto_gidq,0755);

  d(auto_qmail_inst,"control",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"users",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"bin",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot",auto_uido,auto_gidq,0755);

  /* boot restructured for daemontools */
  d(auto_qmail_inst,"boot",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail/env",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail/log",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-smtpd",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-smtpd/env",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-smtpd/log",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-qmqpd",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-qmqpd/env",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-qmqpd/log",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-pop3d",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-pop3d/env",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-pop3d/log",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-imapd",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-imapd/env",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-imapd/log",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-pop3d-ssl",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-pop3d-ssl/env",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-pop3d-ssl/log",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-imapd-ssl",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-imapd-ssl/env",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-imapd-ssl/log",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-pbsdbd",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-pbsdbd/env",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"boot/qmail-pbsdbd/log",auto_uido,auto_gidq,0755);

  /* logging restructured for daemontools */
  d(auto_qmail_inst,"log",auto_uidl,auto_gidq,0755);
  d(auto_qmail_inst,"log/qmail",auto_uidl,auto_gidq,0755);
  d(auto_qmail_inst,"log/qmail-smtpd",auto_uidl,auto_gidq,0755);
  d(auto_qmail_inst,"log/qmail-qmqpd",auto_uidl,auto_gidq,0755);
  d(auto_qmail_inst,"log/qmail-pop3d",auto_uidl,auto_gidq,0755);
  d(auto_qmail_inst,"log/qmail-imapd",auto_uidl,auto_gidq,0755);
  d(auto_qmail_inst,"log/qmail-pop3d-ssl",auto_uidl,auto_gidq,0755);
  d(auto_qmail_inst,"log/qmail-imapd-ssl",auto_uidl,auto_gidq,0755);
  d(auto_qmail_inst,"log/qmail-pbsdbd",auto_uidl,auto_gidq,0755);

  d(auto_qmail_inst,"doc",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"man",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"man/cat1",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"man/cat5",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"man/cat7",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"man/cat8",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"man/man1",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"man/man5",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"man/man7",auto_uido,auto_gidq,0755);
  d(auto_qmail_inst,"man/man8",auto_uido,auto_gidq,0755);

  d(auto_qmail_inst,"alias",auto_uida,auto_gidq,02755);

  d(auto_qmail_inst,"queue",auto_uidq,auto_gidq,0750);
  d(auto_qmail_inst,"queue/pid",auto_uidq,auto_gidq,0700);
#ifndef BIGTODO
  d(auto_qmail_inst,"queue/intd",auto_uidq,auto_gidq,0700);
  d(auto_qmail_inst,"queue/todo",auto_uidq,auto_gidq,0750);
#endif
  d(auto_qmail_inst,"queue/bounce",auto_uids,auto_gidq,0700);

  dsplit("queue/mess",auto_uidq,0750);
  dsplit("queue/info",auto_uids,0700);
  dsplit("queue/local",auto_uids,0700);
  dsplit("queue/remote",auto_uids,0700);
#ifdef BIGTODO
  dsplit("queue/intd",auto_uidq,0700);
  dsplit("queue/todo",auto_uidq,0750);
#endif

  d(auto_qmail_inst,"queue/lock",auto_uidq,auto_gidq,0750);
  z(auto_qmail_inst,"queue/lock/tcpto",1024,auto_uidr,auto_gidq,0644);
  z(auto_qmail_inst,"queue/lock/sendmutex",0,auto_uids,auto_gidq,0600);
  p(auto_qmail_inst,"queue/lock/trigger",auto_uids,auto_gidq,0622);

  /* rules file for tcpserver */
  C(auto_qmail_inst,"control","qmail-smtpd.rules","qmail-smtpd.rules",auto_uido,auto_gidq,0644);
  C(auto_qmail_inst,"control","qmail-qmqpd.rules","qmail-qmqpd.rules",auto_uido,auto_gidq,0644);
  C(auto_qmail_inst,"control","qmail-pop3d.rules","qmail-pop3d.rules",auto_uido,auto_gidq,0644);
  C(auto_qmail_inst,"control","qmail-imapd.rules","qmail-imapd.rules",auto_uido,auto_gidq,0644);
  
  /* Makefile for cdb creation */
  C(auto_qmail_inst,"control","Makefile","Makefile.cdb-p",auto_uido,auto_gidq,0644);
  
  /* signature file for qmail-smtpd ecexcheck freature */
  C(auto_qmail_inst,"control","signatures","signatures",auto_uido,auto_gidq,0644);

  /* run files for boot/supervise scripts */
  C(auto_qmail_inst,"boot/qmail", "run", "qmail.run",auto_uido,auto_gidq,0755);
  C(auto_qmail_inst,"boot/qmail-smtpd", "run", "qmail-smtpd.run",auto_uido,auto_gidq,0755);
  C(auto_qmail_inst,"boot/qmail-qmqpd", "run", "qmail-qmqpd.run",auto_uido,auto_gidq,0755);
  C(auto_qmail_inst,"boot/qmail-pop3d", "run", "qmail-pop3d.run",auto_uido,auto_gidq,0755);
  C(auto_qmail_inst,"boot/qmail-imapd", "run", "qmail-imapd.run",auto_uido,auto_gidq,0755);
  C(auto_qmail_inst,"boot/qmail-pop3d-ssl", "run", "qmail-pop3d-ssl.run",auto_uido,auto_gidq,0755);
  C(auto_qmail_inst,"boot/qmail-imapd-ssl", "run", "qmail-imapd-ssl.run",auto_uido,auto_gidq,0755);
  C(auto_qmail_inst,"boot/qmail-pbsdbd", "run", "qmail-pbsdbd.run",auto_uido,auto_gidq,0755);

  /* run files for logging process */
  l(auto_qmail_inst,"boot/qmail/log","log/qmail",auto_userl,auto_uido,auto_gidq,0755);
  l(auto_qmail_inst,"boot/qmail-smtpd/log","log/qmail-smtpd",auto_userl,auto_uido,auto_gidq,0755);
  l(auto_qmail_inst,"boot/qmail-qmqpd/log","log/qmail-qmqpd",auto_userl,auto_uido,auto_gidq,0755);
  l(auto_qmail_inst,"boot/qmail-pop3d/log","log/qmail-pop3d",auto_userl,auto_uido,auto_gidq,0755);
  l(auto_qmail_inst,"boot/qmail-imapd-ssl/log","log/qmail-imapd-ssl",auto_userl,auto_uido,auto_gidq,0755);
  l(auto_qmail_inst,"boot/qmail-pop3d-ssl/log","log/qmail-pop3d-ssl",auto_userl,auto_uido,auto_gidq,0755);
  l(auto_qmail_inst,"boot/qmail-imapd/log","log/qmail-imapd",auto_userl,auto_uido,auto_gidq,0755);
  l(auto_qmail_inst,"boot/qmail-pbsdbd/log","log/qmail-pbsdbd",auto_userl,auto_uido,auto_gidq,0755);

  c(auto_qmail_inst,"doc","FAQ",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","UPGRADE",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","SENDMAIL",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","INSTALL",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","INSTALL.alias",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","INSTALL.ctl",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","INSTALL.ids",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","INSTALL.maildir",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","INSTALL.mbox",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","INSTALL.vsm",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","TEST.deliver",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","TEST.receive",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","REMOVE.sendmail",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","REMOVE.binmail",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","PIC.local2alias",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","PIC.local2ext",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","PIC.local2local",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","PIC.local2rem",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","PIC.local2virt",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","PIC.nullclient",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","PIC.relaybad",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","PIC.relaygood",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","PIC.rem2local",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","QLDAPGROUP",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","QLDAPINSTALL",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","QLDAPNEWS",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","QLDAPTODO",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","QLDAPPICTURE",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","EXTTODO",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"doc","POPBEFORESMTP",auto_uido,auto_gidq,0644);

  c(auto_qmail_inst,"bin","qmail-queue",auto_uidq,auto_gidq,04711);
  c(auto_qmail_inst,"bin","qmail-lspawn",auto_uido,auto_gidq,0700);
  c(auto_qmail_inst,"bin","qmail-start",auto_uido,auto_gidq,0700);
  c(auto_qmail_inst,"bin","qmail-getpw",auto_uido,auto_gidq,0711);
  c(auto_qmail_inst,"bin","qmail-local",auto_uido,auto_gidq,0711);
  c(auto_qmail_inst,"bin","qmail-remote",auto_uido,auto_gidq,0711);
  c(auto_qmail_inst,"bin","qmail-rspawn",auto_uido,auto_gidq,0711);
  c(auto_qmail_inst,"bin","qmail-clean",auto_uido,auto_gidq,0711);
  c(auto_qmail_inst,"bin","qmail-send",auto_uido,auto_gidq,0711);
#ifdef EXTERNAL_TODO
  c(auto_qmail_inst,"bin","qmail-todo",auto_uido,auto_gidq,0711);
#endif
  c(auto_qmail_inst,"bin","splogger",auto_uido,auto_gidq,0711);
  c(auto_qmail_inst,"bin","qmail-newu",auto_uido,auto_gidq,0700);
  c(auto_qmail_inst,"bin","qmail-newmrh",auto_uido,auto_gidq,0700);
  c(auto_qmail_inst,"bin","qmail-pw2u",auto_uido,auto_gidq,0711);
  c(auto_qmail_inst,"bin","qmail-inject",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","predate",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","datemail",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","mailsubj",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qmail-showctl",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qmail-qread",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qmail-qstat",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qmail-tcpto",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qmail-tcpok",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qmail-pop3d",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qmail-popup",auto_uido,auto_gidq,0711);
  c(auto_qmail_inst,"bin","qmail-qmqpc",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qmail-qmqpd",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qmail-qmtpd",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qmail-smtpd",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","sendmail",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","tcp-env",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qreceipt",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qsmhook",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qbiff",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","forward",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","preline",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","condredirect",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","condwrite",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","bouncesaying",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","except",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","maildirmake",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","maildir2mbox",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","maildirwatch",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qail",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","elq",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","pinq",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qmail-reply",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qmail-quotawarn",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","auth_pop",auto_uido,auto_gidq,0700);
  c(auto_qmail_inst,"bin","auth_imap",auto_uido,auto_gidq,0700);
  c(auto_qmail_inst,"bin","auth_smtp",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","auth_dovecot",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qmail-verify",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qmail-ldaplookup",auto_uido,0,0750);
  c(auto_qmail_inst,"bin","qmail-cdb",auto_uido,auto_gidq,0700);
  c(auto_qmail_inst,"bin","digest",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","pbsadd",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","pbscheck",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","pbsdbd",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qmail-forward",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qmail-secretary",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","qmail-group",auto_uido,auto_gidq,0755);
  
  c(auto_qmail_inst,"man/man5","addresses.5",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat5","addresses.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man5","envelopes.5",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat5","envelopes.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man5","maildir.5",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat5","maildir.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man5","mbox.5",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat5","mbox.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man5","dot-qmail.5",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat5","dot-qmail.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man5","qmail-control.5",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat5","qmail-control.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man5","qmail-header.5",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat5","qmail-header.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man5","qmail-log.5",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat5","qmail-log.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man5","qmail-users.5",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat5","qmail-users.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man5","tcp-environ.5",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat5","tcp-environ.0",auto_uido,auto_gidq,0644);

  c(auto_qmail_inst,"man/man7","forgeries.7",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat7","forgeries.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man7","qmail-limits.7",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat7","qmail-limits.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man7","qmail.7",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat7","qmail.0",auto_uido,auto_gidq,0644);

  c(auto_qmail_inst,"man/man1","forward.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","forward.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man1","condredirect.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","condredirect.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man1","bouncesaying.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","bouncesaying.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man1","except.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","except.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man1","maildirmake.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","maildirmake.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man1","maildir2mbox.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","maildir2mbox.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man1","maildirwatch.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","maildirwatch.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man1","mailsubj.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","mailsubj.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man1","qreceipt.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","qreceipt.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man1","qbiff.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","qbiff.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man1","preline.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","preline.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man1","tcp-env.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","tcp-env.0",auto_uido,auto_gidq,0644);

  c(auto_qmail_inst,"man/man8","qmail-local.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-local.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-lspawn.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-lspawn.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-getpw.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-getpw.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-remote.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-remote.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-rspawn.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-rspawn.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-clean.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-clean.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-send.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-send.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-start.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-start.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","splogger.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","splogger.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-queue.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-queue.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-inject.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-inject.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-showctl.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-showctl.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-newmrh.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-newmrh.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-newu.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-newu.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-pw2u.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-pw2u.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-qread.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-qread.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-qstat.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-qstat.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-tcpok.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-tcpok.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-tcpto.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-tcpto.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-pop3d.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-pop3d.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-popup.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-popup.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-qmqpc.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-qmqpc.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-qmqpd.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-qmqpd.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-qmtpd.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-qmtpd.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-smtpd.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-smtpd.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man8","qmail-command.8",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat8","qmail-command.0",auto_uido,auto_gidq,0644);

  c(auto_qmail_inst,"bin","dot-forward",auto_uido,auto_gidq,0755);

  c(auto_qmail_inst,"man/man1","dot-forward.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","dot-forward.0",auto_uido,auto_gidq,0644);

  d(auto_qmail_inst,"doc/fastforward",auto_uido,auto_gidq,0755);

  c(auto_qmail_inst,"bin","fastforward",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","printforward",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","setforward",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","newaliases",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","printmaillist",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","setmaillist",auto_uido,auto_gidq,0755);
  c(auto_qmail_inst,"bin","newinclude",auto_uido,auto_gidq,0755);

  c(auto_qmail_inst,"doc/fastforward","ALIASES",auto_uido,auto_gidq,0644);

  c(auto_qmail_inst,"man/man1","fastforward.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man1","printforward.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man1","setforward.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man1","newaliases.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man1","printmaillist.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man1","setmaillist.1",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/man1","newinclude.1",auto_uido,auto_gidq,0644);

  c(auto_qmail_inst,"man/cat1","fastforward.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","printforward.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","setforward.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","newaliases.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","printmaillist.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","setmaillist.0",auto_uido,auto_gidq,0644);
  c(auto_qmail_inst,"man/cat1","newinclude.0",auto_uido,auto_gidq,0644);
}
