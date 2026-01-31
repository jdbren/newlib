#ifndef _SYS_UTIME_H
#define _SYS_UTIME_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

struct utimbuf
{
    time_t actime;
    time_t modtime;
};

int utime(const char *filename, const struct utimbuf *times);

#ifdef __cplusplus
};
#endif

#endif /* _SYS_UTIME_H */
