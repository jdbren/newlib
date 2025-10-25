#ifndef _SYS_IOCTL_H
#define _SYS_IOCTL_H

#include <sys/types.h>
#include <asm/ioctls.h>

#ifdef __cplusplus
extern "C" {
#endif

int ioctl(int fd, int op, ...);

#ifdef __cplusplus
}
#endif

#endif
