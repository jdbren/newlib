/* errno is not a global variable, because that would make using it
   non-reentrant.  Instead, its address is returned by the function
   __errno.  */

#ifndef _SYS_ERRNO_H_
#ifdef __cplusplus
extern "C" {
#endif
#define _SYS_ERRNO_H_

#include <sys/reent.h>

#ifdef _REENT_THREAD_LOCAL
#define errno (_tls_errno)
#else /* _REENT_THREAD_LOCAL */

#ifndef _REENT_ONLY
#define errno (*__errno())
extern int *__errno (void);
#endif

#endif /* _REENT_THREAD_LOCAL */

/* Please don't use these variables directly.
   Use strerror instead. */
extern __IMPORT const char * const _sys_errlist[];
extern __IMPORT int _sys_nerr;
#ifdef __CYGWIN__
extern __IMPORT const char * const sys_errlist[];
extern __IMPORT int sys_nerr;
extern __IMPORT char *program_invocation_name;
extern __IMPORT char *program_invocation_short_name;
#endif

#define __errno_r(ptr) _REENT_ERRNO(ptr)

#include <asm/errno.h>

#define __ELASTERROR 2000	/* Users can add values starting here */

#ifdef __cplusplus
}
#endif
#endif /* _SYS_ERRNO_H */
