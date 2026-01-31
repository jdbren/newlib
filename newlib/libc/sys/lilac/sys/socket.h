#ifndef __SYS_SOCKET_H_
#define __SYS_SOCKET_H_

#include <sys/cdefs.h>
#include <sys/_types.h>

typedef __socklen_t socklen_t;
typedef __sa_family_t sa_family_t;

struct sockaddr {
    unsigned char   sa_len;         /* total length */
    sa_family_t     sa_family;      /* address family */
    char            sa_data[14];    /* actually longer; address value */
};

#endif
