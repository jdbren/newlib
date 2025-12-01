#ifndef _LIBC_SYSCALL_H
#define _LIBC_SYSCALL_H

#define SYS_restart_syscall 0
#define SYS_exit 1
#define SYS_fork 2
#define SYS_read 3
#define SYS_write 4
#define SYS_open 5
#define SYS_close 6
#define SYS_waitpid 7
#define SYS_creat 8
#define SYS_execve 9
#define SYS_chdir 10
#define SYS_time 11
#define SYS_stat 12
#define SYS_lseek 13
#define SYS_getpid 14
#define SYS_mount 15
#define SYS_umount 16
#define SYS_getdents 17
#define SYS_getcwd 18
#define SYS_mkdir 19
#define SYS_unlink 20
#define SYS_dup 21
#define SYS_pipe 22
#define SYS_brk 23
#define SYS_sbrk 24
#define SYS_reboot 25
#define SYS_dup2 26
#define SYS_kill 27
#define SYS_signal 28
#define SYS_getppid 29
#define SYS_sigaction 30
#define SYS_sigreturn 31
#define SYS_sigprocmask 32
#define SYS_sigpending 33
#define SYS_getpgid 34
#define SYS_setpgid 35
#define SYS_getsid 36
#define SYS_setsid 37
#define SYS_sched_yield 38
#define SYS_fstat 39
#define SYS_ioctl 40
#define SYS_memfd_create 41
#define SYS_sigsuspend 42
#define SYS_fcntl 43
#define SYS_mmap 44
#define SYS_munmap 45
#define SYS_nanosleep 46
#define SYS_gettimeofday 47

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __x86_64__
static inline long syscall0(long number)
{
    long ret;
    asm volatile ("syscall" : "=a"(ret) : "a"(number) : "rcx", "r11", "memory", "rdi");
    return ret;
}

static inline long syscall1(long number, long arg0)
{
    long ret;
    asm volatile (
        "syscall" : "=a"(ret) : "a"(number), "D"(arg0)
        : "rcx", "r11", "memory"
    );
    return ret;
}

static inline long syscall2(long number, long arg0, long arg1)
{
    long ret;
    asm volatile (
        "syscall" : "=a"(ret) : "a"(number), "D"(arg0), "S"(arg1)
        : "rcx", "r11", "memory"
    );
    return ret;
}

static inline long syscall3(long number, long arg0, long arg1, long arg2)
{
    long ret;
    asm volatile (
        "syscall" : "=a"(ret) : "a"(number), "D"(arg0), "S"(arg1), "d"(arg2)
        : "rcx", "r11", "memory"
    );
    return ret;
}

static inline long syscall4(long number, long arg0, long arg1, long arg2,
    long arg3)
{
    long ret;
    asm volatile (
        "mov %5, %r10\n\t"
        "syscall" : "=a"(ret) :
        "a"(number), "D"(arg0), "S"(arg1), "d"(arg2), "r"(arg3)
        : "rcx", "r11", "memory", "r10"
    );
    return ret;
}

static inline long syscall5(long number, long arg0, long arg1, long arg2,
    long arg3, long arg4)
{
    long ret;
    asm volatile (
        "mov %5, %r10\n\t"
        "mov %6, %r8\n\t"
        "syscall" : "=a"(ret) :
        "a"(number), "D"(arg0), "S"(arg1), "d"(arg2), "r"(arg3), "r"(arg4)
        : "rcx", "r11", "memory", "r10", "r8"
    );
    return ret;
}

static inline long syscall6(long number, long arg0, long arg1, long arg2,
    long arg3, long arg4, long arg5)
{
    long ret;
    register long r10 asm("r10") = arg3;
    register long r8 asm("r8") = arg4;
    register long r9 asm("r9") = arg5;

    asm volatile (
        "syscall"
        : "=a" (ret)
        : "a" (number), "D" (arg0), "S" (arg1), "d" (arg2),
          "r" (r10), "r" (r8), "r" (r9)
        : "rcx", "r11", "memory"
    );
    return ret;
}
#else // !__x86_64__ :
static inline long syscall0(long number)
{
    long ret;
    asm volatile(
        "int $0x80" :
        "=a"(ret) :
        "a"(number)
    );
    return ret;
}

static inline long syscall1(long number, long arg0)
{
    long ret;
    asm volatile(
        "int $0x80" :
        "=a"(ret) :
        "a"(number), "b"(arg0)
    );
    return ret;
}

static inline long syscall2(long number, long arg0, long arg1)
{
    long ret;
    asm volatile(
        "int $0x80" :
        "=a"(ret) :
        "a"(number), "b"(arg0), "c"(arg1)
    );
    return ret;
}

static inline long syscall3(long number, long arg0, long arg1, long arg2)
{
    long ret;
    asm volatile(
        "int $0x80" :
        "=a"(ret) :
        "a"(number), "b"(arg0), "c"(arg1), "d"(arg2)
    );
    return ret;
}

static inline long syscall4(long number, long arg0, long arg1, long arg2, long arg3)
{
    long ret;
    asm volatile(
        "int $0x80" :
        "=a"(ret) :
        "a"(number), "b"(arg0), "c"(arg1), "d"(arg2), "S"(arg3)
    );
    return ret;
}

static inline long syscall5(long number, long arg0, long arg1, long arg2, long arg3, long arg4)
{
    long ret;
    asm volatile(
        "int $0x80" :
        "=a"(ret) :
        "a"(number), "b"(arg0), "c"(arg1), "d"(arg2), "S"(arg3), "D"(arg4)
    );
    return ret;
}

static inline long syscall6(long number, long arg0, long arg1, long arg2, long arg3, long arg4, long arg5)
{
    long ret;
    asm volatile(
        "pushl %%ebp\n\t"
        "movl %[arg5], %%ebp\n\t"
        "int $0x80\n\t"
        "popl %%ebp"
        : "=a"(ret)
        : "a"(number), "b"(arg0), "c"(arg1), "d"(arg2),
          "S"(arg3), "D"(arg4), [arg5]"rm"(arg5)
        : "memory"
    );
    return ret;
}
#endif // __x86_64__

#ifdef __cplusplus
}
#endif

#endif // _LIBC_SYSCALL_H
