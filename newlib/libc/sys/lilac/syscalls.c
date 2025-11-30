#include <sys/syscall.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/dirent.h>
#include <sys/mman.h>
#include <stdarg.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <termios.h>

extern char **environ;

int	access (const char *__path, int __amode)
{
    return 0;
}

int open(const char *pathname, int flags, ...)
{
    va_list ap;
    va_start(ap, flags);
    long fd = syscall3(SYS_open, (long)pathname, (long)flags, (long)va_arg(ap, int));
    va_end(ap);
    if (fd < 0) {
        errno = -fd;
        return -1;
    }
    return fd;
}

int stat(const char *pathname, struct stat *buf)
{
    long err = syscall2(SYS_stat, (long)pathname, (long)buf);
    if (err < 0) {
        errno = -err;
        return -1;
    }
    return 0;
}

int	mkdir(const char *_path, mode_t __mode)
{
    long err = syscall2(SYS_mkdir, (long)_path, (long)__mode);
    if (err < 0) {
        errno = -err;
        return -1;
    }
    return 0;
}

int getdents(int fd, void *dirp, int count)
{
    long err = syscall3(SYS_getdents, fd, (long)dirp, count);
    if (err < 0) {
        errno = -err;
        return -1;
    }
    return err;
}

pid_t waitpid(pid_t pid, int *wstatus, int options)
{
    long err = syscall3(SYS_waitpid, pid, (long)wstatus, options);
    if (err < 0) {
        errno = -err;
        return -1;
    }
    return err;
}

void __attribute__((noreturn)) _exit(int status)
{
    while (1)
        syscall1(SYS_exit, status);
    __builtin_unreachable();
}

int chdir(const char *path)
{
    long err = syscall1(SYS_chdir, (long)path);
    if (err < 0) {
        errno = -err;
        return -1;
    }
    return 0;
}

int read(int file, char *ptr, int len)
{
    long bytes = syscall3(SYS_read, file, (long)ptr, len);
    if (bytes < 0) {
        errno = -bytes;
        return -1;
    }
    return bytes;
}

int lseek (int file, int ptr, int dir)
{
    long offset = syscall3(SYS_lseek, file, (long)ptr, dir);
    if (offset < 0) {
        errno = -offset;
        return -1;
    }
    return offset;
}

int write(int file, char *ptr, int len)
{
    long bytes = syscall3(SYS_write, file, (long)ptr, len);
    if (bytes < 0) {
        errno = -bytes;
        return -1;
    }
    return bytes;
}

int close(int file)
{
    long err = syscall1(SYS_close, file);
    if (err < 0) {
        errno = -err;
        return -1;
    }
    return 0;
}

caddr_t sbrk (int incr)
{
    caddr_t ptr = (caddr_t)syscall1(SYS_sbrk, incr);
    if (ptr == (caddr_t)-1) {
        errno = ENOMEM;
        return (caddr_t)-1;
    }
    return ptr;
}

int fstat (int file, struct stat *st)
{
    long err = syscall2(SYS_fstat, file, (uintptr_t)st);
    if (err < 0) {
        errno = err;
        return -1;
    }
    return 0;
}

int lstat (const char *path, struct stat *st)
{
    return stat(path, st);
}

int unlink()
{
    return -1;
}

int _isatty(int fd)
{
    return 1;
}

int kill(int pid, int sig)
{
    long err = syscall2(SYS_kill, pid, sig);
    if (err < 0) {
        errno = -err;
        return -1;
    }
    return err;
}

int killpg (pid_t pgrp, int sig)
{
    return kill (-pgrp, sig);
}

_sig_func_ptr signal(int sig, _sig_func_ptr handler)
{
    long err = syscall2(SYS_signal, sig, (long)handler);
    if (err < 0) {
        errno = -err;
        return SIG_ERR;
    }
    return (_sig_func_ptr)err;
}

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)
{
    long err = syscall3(SYS_sigaction, signum, (long)act, (long)oldact);
    if (err < 0) {
        errno = -err;
        return -1;
    }
    return 0;
}

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset)
{
    long err = syscall3(SYS_sigprocmask, how, (long)set, (long)oldset);
    if (err < 0) {
        errno = -err;
        return -1;
    }
    return 0;
}

int sigpending(sigset_t *set)
{
    long err = syscall1(SYS_sigpending, (long)set);
    if (err < 0) {
        errno = -err;
        return -1;
    }
    return 0;
}

int sigsuspend(const sigset_t *set)
{
    long err = syscall1(SYS_sigsuspend, (long)set);
    errno = -err;
    return -1;
}

pid_t getpid(void)
{
    return syscall0(SYS_getpid);
}

pid_t getppid(void)
{
    return syscall0(SYS_getppid);
}

char * getcwd(char *buf, size_t size)
{
    long err = syscall2(SYS_getcwd, (long)buf, size);
    if (err < 0) {
        errno = -err;
        return NULL;
    }
    return buf;
}

char * getwd(char *buf)
{
    return getcwd(buf, 64); // FIXME: use PATH_MAX
}

int truncate(const char *path, off_t length)
{
    return -1;
}

int ftruncate(int fd, off_t length)
{
    return -1;
}

int chmod(const char *path, mode_t mode)
{
    return -1;
}

int fchmod(int fd, mode_t mode)
{
    return -1;
}

int chown(const char *path, short owner, short group)
{
    return  -1;
}

int utime (const char *path, char *times)
{
    return -1;
}

pid_t fork()
{
    long err = syscall0(SYS_fork);
    if (err < 0) {
        errno = -err;
        return -1;
    }
    return (pid_t)err;
}

int wait(int *statusp)
{
    return waitpid(-1, statusp, 0);
}

int _execve(const char *path, char *const argv[], char *const envp[])
{
    long err = syscall3(SYS_execve, (long)path, (long)argv, (long)envp);
    if (err < 0) {
        errno = -err;
        return -1;
    }
    __unreachable();
}


int pipe(int *fd)
{
    long err = syscall1(SYS_pipe, (long)fd);
    if (err < 0) {
        errno = -err;
        return -1;
    }
    return 0;
}

int dup(int fd)
{
    long new_fd = syscall1(SYS_dup, fd);
    if (new_fd < 0) {
        errno = -new_fd;
        return -1;
    }
    return (int)new_fd;
}

int dup2(int fd, int fd2)
{
    long new_fd = syscall2(SYS_dup2, fd, fd2);
    if (new_fd < 0) {
        errno = -new_fd;
        return -1;
    }
    return (int)new_fd;
}

pid_t getpgid(pid_t pid)
{
    long ret = syscall1(SYS_getpgid, pid);
    if (ret < 0) {
        errno = -ret;
        return -1;
    }
    return ret;
}

int getpgrp(void)
{
    return getpgid(0);
}

pid_t getsid(pid_t pid)
{
    long ret = syscall1(SYS_getsid, pid);
    if (pid < 0) {
        errno = -ret;
        return -1;
    }
    return ret;
}

pid_t setpgid(pid_t pid, pid_t pgid)
{
    long ret = syscall2(SYS_setpgid, pid, pgid);
    if (ret < 0) {
        errno = -ret;
        return -1;
    }
    return ret;
}

int setpgrp(void)
{
    return setpgid(0,0);
}

pid_t setsid(void)
{
    long pid = syscall0(SYS_setsid);
    if (pid < 0) {
        errno = -pid;
        return -1;
    }
    return pid;
}

int gettimeofday(struct timeval *restrict tv, struct timezone *restrict tz)
{
    long err = syscall2(SYS_gettimeofday, (long)tv, (long)tz);
    if (err < 0) {
        errno = -err;
        return -1;
    }
    return 0;
}

uid_t getuid(void)
{
    return 0;
}

uid_t geteuid(void)
{
    return 0;
}

gid_t getgid(void)
{
    return 0;
}

gid_t getegid(void)
{
    return 0;
}

pid_t vfork(void)
{
    return fork();
}

mode_t umask(mode_t mask)
{
    return 0;
}

int nanosleep(const struct timespec *duration, struct timespec *rem)
{
    long err = syscall2(SYS_nanosleep, (long)duration, (long)rem);
    if (err < 0) {
        errno = -err;
        return -1;
    }
    return 0;
}

unsigned int alarm(unsigned int seconds)
{
    errno = ENOSYS;
    return 0;
}

int ioctl(int fd, int op, ...)
{
    va_list list;
    va_start(list, op);
    long err = syscall3(SYS_ioctl, fd, op, (long)va_arg(list, void *));
    if (err < 0) {
        errno = -err;
        return -1;
    }
    return 0;
}

int getgroups(int size, gid_t list[])
{
    if (size < 0) {
        errno = EINVAL;
        return -1;
    }
    if (size == 0)
        return 1;
    list[0] = 0;
    return 1;
}

int fcntl(int fd, int cmd, ...)
{
    long error;
    va_list ap;
    va_start(ap, cmd);
    error = syscall3(SYS_fcntl, fd, cmd, va_arg(ap, long));
    va_end(ap);
    if (error < 0) {
        errno = -error;
        return -1;
    }
    return error;
}

void * mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    long ret = syscall6(SYS_mmap, (long)addr, length, prot, flags, fd, offset);
    if (ret < 0) {
        errno = -ret;
        return MAP_FAILED;
    }
    return (void *)ret;
}

int munmap(void *addr, size_t length)
{
    long err = syscall2(SYS_munmap, (long)addr, length);
    if (err < 0) {
        errno = -err;
        return -1;
    }
    return 0;
}

int link(const char *existing, const char *new)
{
    errno = ENOSYS;
    return -1;
}
