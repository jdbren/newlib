#ifndef _SYS_WAIT_H
#define _SYS_WAIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#define WAIT_ANY (-1)
#define WAIT_MYPGRP 0

#define WNOHANG 1
#define WUNTRACED 2

#define WIFEXITED(w)	(((w) & 0xff) == 0)
#define WIFSIGNALED(w)	(((w) & 0x7f) > 0 && (((w) & 0x7f) < 0x7f))
#define WCOREDUMP(w)	(((w) & 0x80) != 0)
#define WIFSTOPPED(w)	(((w) & 0xff) == 0x7f)
#define WIFCONTINUED(w)	((w) == 0xffff)
#define WEXITSTATUS(w)	(((w) >> 8) & 0xff)
#define WTERMSIG(w)	((w) & 0x7f)
#define WSTOPSIG	WEXITSTATUS

pid_t wait (int *);
pid_t waitpid (pid_t, int *, int);

#ifdef _LIBC
pid_t _wait (int *);
#endif

/* Provide prototypes for most of the _<systemcall> names that are
   provided in newlib for some compilers.  */
pid_t _wait (int *);

#ifdef __cplusplus
};
#endif

#endif
