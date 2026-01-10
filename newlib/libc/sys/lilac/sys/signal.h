/* sys/signal.h */

#ifndef _SYS_SIGNAL_H
#define _SYS_SIGNAL_H
#ifdef __cplusplus
extern "C" {
#endif

#include "_ansi.h"
#include <sys/cdefs.h>
#include <sys/features.h>
#include <sys/types.h>
#include <sys/_sigset.h>
#include <sys/_timespec.h>
#include <stdint.h>

#if !defined(_SIGSET_T_DECLARED)
#define	_SIGSET_T_DECLARED
typedef	__sigset_t	sigset_t;
#endif

#if defined(_POSIX_REALTIME_SIGNALS) || __POSIX_VISIBLE >= 199309

/* sigev_notify values
   NOTE: P1003.1c/D10, p. 34 adds SIGEV_THREAD.  */

#define SIGEV_NONE   1  /* No asynchronous notification shall be delivered */
                        /*   when the event of interest occurs. */
#define SIGEV_SIGNAL 2  /* A queued signal, with an application defined */
                        /*  value, shall be delivered when the event of */
                        /*  interest occurs. */
#define SIGEV_THREAD 3  /* A notification function shall be called to */
                        /*   perform notification. */

/*  Signal Generation and Delivery, P1003.1b-1993, p. 63
    NOTE: P1003.1c/D10, p. 34 adds sigev_notify_function and
          sigev_notify_attributes to the sigevent structure.  */

union sigval {
  int    sival_int;    /* Integer signal value */
  void  *sival_ptr;    /* Pointer signal value */
};

struct sigevent {
  int              sigev_notify;               /* Notification type */
  int              sigev_signo;                /* Signal number */
  union sigval     sigev_value;                /* Signal value */

#if defined(_POSIX_THREADS)
  void           (*sigev_notify_function)( union sigval );
                                               /* Notification function */
  pthread_attr_t  *sigev_notify_attributes;    /* Notification Attributes */
#endif
};

/* Signal Actions, P1003.1b-1993, p. 64 */
/* si_code values, p. 66 */

#define SI_USER    1    /* Sent by a user. kill(), abort(), etc */
#define SI_QUEUE   2    /* Sent by sigqueue() */
#define SI_TIMER   3    /* Sent by expiration of a timer_settime() timer */
#define SI_ASYNCIO 4    /* Indicates completion of asycnhronous IO */
#define SI_MESGQ   5    /* Indicates arrival of a message at an empty queue */

typedef struct {
  int          si_signo;    /* Signal number */
  int          si_code;     /* Cause of the signal */
  union sigval si_value;    /* Signal value */
} siginfo_t;
#endif /* defined(_POSIX_REALTIME_SIGNALS) || __POSIX_VISIBLE >= 199309 */

typedef void (*__sighandler_t) (int);

/* Structure describing the action to be taken when a signal arrives.  */
struct sigaction {
    /* Signal handler.  */
#if defined __USE_POSIX199309 || defined __USE_XOPEN_EXTENDED
    union {
        /* Used if SA_SIGINFO is not set.  */
        __sighandler_t sa_handler;
        /* Used if SA_SIGINFO is set.  */
        void (*sa_sigaction) (int, siginfo_t *, void *);
    } __sigaction_handler;
# define sa_handler     __sigaction_handler.sa_handler
# define sa_sigaction   __sigaction_handler.sa_sigaction
#else
    __sighandler_t sa_handler;
#endif

    /* Additional set of signals to be blocked.  */
    __sigset_t sa_mask;

    /* Special flags.  */
    int sa_flags;

    /* Restore handler.  */
    void (*sa_restorer) (void);
};

/* Bits in `sa_flags'.  */
#define SA_NOCLDSTOP  1          /* Don't send SIGCHLD when children stop.  */
#define SA_NOCLDWAIT  2          /* Don't create zombie on child death.  */
#define SA_SIGINFO    4          /* Invoke signal-catching function with
                                    three arguments instead of one.  */
#define SA_ONSTACK   0x08000000 /* Use signal stack by using `sa_restorer'. */
#define SA_RESTART   0x10000000 /* Restart syscall on signal return.  */
#define SA_NODEFER   0x40000000 /* Don't automatically block the signal when
                                    its handler is being executed.  */
#define SA_RESETHAND 0x80000000 /* Reset to SIG_DFL on entry to handler.  */
#define SA_INTERRUPT 0x20000000 /* Historical no-op.  */

/* Some aliases for the SA_ constants.  */
#define SA_NOMASK    SA_NODEFER
#define SA_ONESHOT   SA_RESETHAND
#define SA_STACK     SA_ONSTACK


#if defined __USE_POSIX199309 || defined __USE_XOPEN_EXTENDED
typedef void (*_sig_func_ptr)(int sig, siginfo_t *info, void *ucontext);
#else
typedef void (*_sig_func_ptr)(int);
#endif

#if __BSD_VISIBLE || __XSI_VISIBLE >= 4 || __POSIX_VISIBLE >= 200809
/*
 * Minimum and default signal stack constants. Allow for target overrides
 * from <sys/features.h>.
 */
#ifndef	MINSIGSTKSZ
#define	MINSIGSTKSZ	2048
#endif
#ifndef	SIGSTKSZ
#define	SIGSTKSZ	8192
#endif

/*
 * Possible values for ss_flags in stack_t below.
 */
#define	SS_ONSTACK	0x1
#define	SS_DISABLE	0x2

#endif

/*
 * Structure used in sigaltstack call.
 */
typedef struct sigaltstack {
  void     *ss_sp;    /* Stack base or pointer.  */
  int       ss_flags; /* Flags.  */
  size_t    ss_size;  /* Stack size.  */
} stack_t;

#if __POSIX_VISIBLE
#define SIG_SETMASK 0	/* set mask with sigprocmask() */
#define SIG_BLOCK 1	/* set of signals to block */
#define SIG_UNBLOCK 2	/* set of signals to, well, unblock */

int sigprocmask (int, const sigset_t *, sigset_t *);
#endif

#if __POSIX_VISIBLE >= 199506
int pthread_sigmask (int, const sigset_t *, sigset_t *);
#endif

#ifdef _LIBC
int _kill (pid_t, int);
#endif /* _LIBC */

#if __POSIX_VISIBLE
int kill (pid_t, int);
#endif

#if __BSD_VISIBLE || __XSI_VISIBLE >= 4
int killpg (pid_t, int);
#endif
#if __POSIX_VISIBLE
int sigaction (int, const struct sigaction *, struct sigaction *);
int sigaddset (sigset_t *, const int);
int sigdelset (sigset_t *, const int);
int sigismember (const sigset_t *, int);
int sigfillset (sigset_t *);
int sigemptyset (sigset_t *);
int sigpending (sigset_t *);
int sigsuspend (const sigset_t *);
int sigwait (const sigset_t *, int *);

#define sigaddset(what,sig) (*(what) |= (1<<(sig)), 0)
#define sigdelset(what,sig) (*(what) &= ~(1<<(sig)), 0)
#define sigemptyset(what)   (*(what) = 0, 0)
#define sigfillset(what)    (*(what) = ~(0), 0)
#define sigismember(what,sig) (((*(what)) & (1<<(sig))) != 0)
#endif /* __POSIX_VISIBLE */

/* There are two common sigpause variants, both of which take an int argument.
   If you request _XOPEN_SOURCE or _GNU_SOURCE, you get the System V version,
   which removes the given signal from the process's signal mask; otherwise
   you get the BSD version, which sets the process's signal mask to the given
   value. */
#if __XSI_VISIBLE
# ifdef __GNUC__
int sigpause (int) __asm__ (__ASMNAME ("__xpg_sigpause"));
# else
int __xpg_sigpause (int);
#  define sigpause __xpg_sigpause
# endif
#elif __BSD_VISIBLE
int sigpause (int);
#endif

#if __BSD_VISIBLE || __XSI_VISIBLE >= 4 || __POSIX_VISIBLE >= 200809
int sigaltstack (const stack_t *__restrict, stack_t *__restrict);
#endif

#if __POSIX_VISIBLE >= 199506
int pthread_kill (pthread_t, int);
#endif

#if __POSIX_VISIBLE >= 199309

/*  3.3.8 Synchronously Accept a Signal, P1003.1b-1993, p. 76
    NOTE: P1003.1c/D10, p. 39 adds sigwait().  */

int sigwaitinfo (const sigset_t *, siginfo_t *);
int sigtimedwait (const sigset_t *, siginfo_t *, const struct timespec *);
/*  3.3.9 Queue a Signal to a Process, P1003.1b-1993, p. 78 */
int sigqueue (pid_t, int, const union sigval);

#endif /* __POSIX_VISIBLE >= 199309 */

/* Using __MISC_VISIBLE until POSIX Issue 8 is officially released */
#if __MISC_VISIBLE

/* POSIX Issue 8 adds sig2str() and str2sig() */

#if __SIZEOF_INT__ >= 4
#define SIG2STR_MAX 17	/* (sizeof("RTMAX+") + sizeof("4294967295") - 1) */
#else
#define SIG2STR_MAX 12	/* (sizeof("RTMAX+") + sizeof("65535") - 1) */
#endif

int sig2str(int, char *);
int str2sig(const char *__restrict, int *__restrict);

#endif /* __MISC_VISIBLE */


#include <asm/signo.h>

#ifdef __cplusplus
}
#endif

#ifndef _SIGNAL_H_
/* Some applications take advantage of the fact that <sys/signal.h>
 * and <signal.h> are equivalent in glibc.  Allow for that here.  */
#include <signal.h>
#endif
#endif /* _SYS_SIGNAL_H */
