#ifndef _SYS_RESOURCE_H_
#define _SYS_RESOURCE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/time.h>

#define	RUSAGE_SELF	0		/* calling process */
#define	RUSAGE_CHILDREN	-1		/* terminated child processes */
#if __GNU_VISIBLE
#define	RUSAGE_THREAD	1
#endif

struct rusage {
  	struct timeval ru_utime;	/* user time used */
	struct timeval ru_stime;	/* system time used */
};

int	getrusage (int, struct rusage*);

/* rlimit stubs */
typedef unsigned long rlim_t;

struct rlimit {
    rlim_t rlim_cur;
    rlim_t rlim_max;
};

#define RLIM_INFINITY ((rlim_t)-1)

static inline int setrlimit(int r, const struct rlimit *l)
{
    (void)r; (void)l;
    return 0;
}

static inline int getrlimit(int r, struct rlimit *l)
{
    (void)r;
    if (l) {
        l->rlim_cur = RLIM_INFINITY;
        l->rlim_max = RLIM_INFINITY;
    }
    return 0;
}

#ifdef __cplusplus
}
#endif
#endif /* !_SYS_RESOURCE_H_ */