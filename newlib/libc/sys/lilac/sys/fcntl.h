
#ifndef	_SYS__DEFAULT_FCNTL_H_
#ifdef __cplusplus
extern "C" {
#endif
#define	_SYS__DEFAULT_FCNTL_H_
#include <_ansi.h>
#include <sys/cdefs.h>
#include <asm/fcntl.h>

/*#include <sys/stdtypes.h>*/

#if __MISC_VISIBLE
/* extended file segment locking set data type */
struct eflock {
	short	l_type;		/* F_RDLCK, F_WRLCK, or F_UNLCK */
	short	l_whence;	/* flag to choose starting offset */
	long	l_start;	/* relative offset, in bytes */
	long	l_len;		/* length, in bytes; 0 means lock to EOF */
	short	l_pid;		/* returned with F_GETLK */
	short	l_xxx;		/* reserved for future use */
	long	l_rpid;		/* Remote process id wanting this lock */
	long	l_rsys;		/* Remote system id wanting this lock */
};
#endif	/* __MISC_VISIBLE */

#include <sys/types.h>
#include <sys/stat.h>		/* sigh. for the mode bits for open/creat */

extern int open (const char *, int, ...);
#if __ATFILE_VISIBLE
extern int openat (int, const char *, int, ...);
#endif
extern int creat (const char *, mode_t);
extern int fcntl (int, int, ...);
#if __BSD_VISIBLE
extern int flock (int, int);
#endif
#if __GNU_VISIBLE
#include <sys/time.h>
extern int futimesat (int, const char *, const struct timeval [2]);
#endif

/* Provide _<systemcall> prototypes for functions provided by some versions
   of newlib.  */
#ifdef _LIBC
extern int _open (const char *, int, ...);
extern int _fcntl (int, int, ...);
#ifdef __LARGE64_FILES
extern int _open64 (const char *, int, ...);
#endif
#endif

#ifdef __cplusplus
}
#endif
#endif	/* !_SYS__DEFAULT_FCNTL_H_ */
