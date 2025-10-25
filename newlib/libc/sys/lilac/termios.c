#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

int tcgetattr(int fd, struct termios *t)
{
    return ioctl(fd, TCGETS, t);
}

int tcsetattr(int fd, int a, const struct termios *t)
{
    switch (a) {
    case TCSANOW:
        return ioctl(fd, TCSETS, t);
    case TCSADRAIN:
        return ioctl(fd, TCSETSW, t);
    case TCSAFLUSH:
        return ioctl(fd, TCSETSF, t);
    default:
        errno = EINVAL;
        return -1;
    }
}

int tcgetpgrp(int fd)
{
    pid_t res = -1;
    long err = ioctl(fd, TIOCGPGRP, &res);
    if (err < 0) {
        errno = -err;
        return -1;
    }
    return res;
}

int tcsetpgrp(int fd, pid_t pgrp)
{
    return ioctl(fd, TIOCSPGRP, &pgrp);
}

speed_t cfgetospeed(const struct termios *tp)
{
	return tp->c_ospeed;
}

speed_t cfgetispeed(const struct termios *tp)
{
    return tp->c_ispeed;
}

int tcsendbreak(int fd, int duration)
{
    return 0; /* Not implemented */
}

int tcdrain(int fd)
{
    return 0; /* Not implemented */
}

int tcflush(int fd, int queue_selector)
{
    return 0; /* Not implemented */
}

int tcflow(int fd, int action)
{
    return 0; /* Not implemented */
}

void cfmakeraw(struct termios *termios_p)
{
    termios_p->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    termios_p->c_oflag &= ~OPOST;
    termios_p->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    termios_p->c_cflag &= ~(CSIZE | PARENB);
    termios_p->c_cflag |= CS8;
}


int cfsetispeed(struct termios *termios_p, speed_t speed)
{
    termios_p->c_ispeed = speed;
    return 0;
}

int cfsetospeed(struct termios *termios_p, speed_t speed)
{
    termios_p->c_ospeed = speed;
    return 0;
}

int cfsetspeed(struct termios *termios_p, speed_t speed)
{
    termios_p->c_ispeed = speed;
    termios_p->c_ospeed = speed;
    return 0;
}

char *getlogin(void)
{
    return "username";
}
