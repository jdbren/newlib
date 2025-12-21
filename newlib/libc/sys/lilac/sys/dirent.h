#ifndef _SYS_DIRENT_H
#define _SYS_DIRENT_H

#include <sys/types.h>

struct dirent {
    unsigned long   d_fileno;   /* file number of entry */
    unsigned long   d_off;      /* directory offset of entry */
    unsigned short  d_reclen;   /* length of this record */
    char            d_name[128];
    char            pad;
    char            d_type;
};

typedef struct _dirdesc {
    int     dd_fd;
    long    dd_loc;
    long    dd_size;
    char    *dd_buf;
    int     dd_len;
    long    dd_seek;
} DIR;

#define    d_ino        d_fileno    /* backward and XSI compatibility */
#define __dirfd(dp)    ((dp)->dd_fd)

#if __BSD_VISIBLE

/*
 * File types
 */
#define    DT_UNKNOWN     0
#define    DT_FIFO        1
#define    DT_CHR         2
#define    DT_DIR         4
#define    DT_BLK         6
#define    DT_REG         8
#define    DT_LNK        10
#define    DT_SOCK       12
#define    DT_WHT        14

/*
 * Convert between stat structure types and directory types.
 */
#define    IFTODT(mode)    (((mode) & 0170000) >> 12)
#define    DTTOIF(dirtype)    ((dirtype) << 12)

#endif /* __BSD_VISIBLE */

int getdents(int fd, void *dirp, int bufsz);

#endif
