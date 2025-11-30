#ifndef _SYS_MMAN_H
#define _SYS_MMAN_H

#include <sys/types.h>
#include <stddef.h>
#include <asm/mman-bits.h>

#define MAP_FAILED ((void *) -1)

void * mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *addr, size_t length);

#endif
