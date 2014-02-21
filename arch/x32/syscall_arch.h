#define __SYSCALL_LL_E(x) (x)
#define __SYSCALL_LL_O(x) (x)

#define __scc(X) sizeof(1?(X):0ULL) < 8 ? (unsigned long) (X) : (long long) (X)
#define __sca long long
struct __timespec { long long tv_sec; long tv_nsec; };
#define __tsc(X) ((struct __timespec*)(unsigned long)(X))

static __inline long __syscall0(long long n)
{
	unsigned long ret;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n) : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall1(long long n, long long a1)
{
	unsigned long ret;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1) : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall2(long long n, long long a1, long long a2)
{
	unsigned long ret;
	struct __timespec *ts2 = 0;
	switch (n) {
	case SYS_nanosleep:
		if(a1) a1 = (unsigned long) (&(struct __timespec) {
		.tv_sec = __tsc(a1)->tv_sec, .tv_nsec = __tsc(a1)->tv_nsec});
	case SYS_clock_getres:  case SYS_clock_gettime:
	case SYS_clock_settime: case SYS_sched_rr_get_interval:
		ts2 = __tsc(a2);
		if(a2) a2 = (unsigned long) (&(struct __timespec) {
		.tv_sec = __tsc(a2)->tv_sec, .tv_nsec = __tsc(a2)->tv_nsec});
	default:
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2)
						: "rcx", "r11", "memory");
	}
	switch (n) {
	case SYS_nanosleep: case SYS_clock_getres:
	case SYS_clock_gettime: case SYS_sched_rr_get_interval:
		if(ts2) {
			ts2->tv_sec  = __tsc(a2)->tv_sec;
			ts2->tv_nsec = __tsc(a2)->tv_nsec;
		}
	}
	return ret;
}

static __inline long __syscall3(long long n, long long a1, long long a2, long long a3)
{
	unsigned long ret;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3) : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall4(long long n, long long a1, long long a2, long long a3,
                                     long long a4)
{
	unsigned long ret;
	register long long r10 __asm__("r10") = a4;
	struct __timespec *ts4 = 0;
	switch (n) {
	case SYS_utimensat:
		if(a3) a3 = (unsigned long) ((struct __timespec[2]) {
		[0] = {.tv_sec = __tsc(a3)[0].tv_sec, .tv_nsec = __tsc(a3)[0].tv_nsec},
		[1] = {.tv_sec = __tsc(a3)[1].tv_sec, .tv_nsec = __tsc(a3)[1].tv_nsec},
		});
		goto def;
	case SYS_clock_nanosleep: case SYS_semtimedop:
		ts4 = __tsc(r10);
		if(r10) r10 = (unsigned long) (&(struct __timespec) {
		.tv_sec = __tsc(r10)->tv_sec, .tv_nsec = __tsc(r10)->tv_nsec});
		if(n == SYS_semtimedop) goto def;
	case SYS_rt_sigtimedwait: case SYS_ppoll:
		if(a3) a3 = (unsigned long) (&(struct __timespec) {
		.tv_sec = __tsc(a3)->tv_sec, .tv_nsec = __tsc(a3)->tv_nsec});
	default: def:
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3), "r"(r10): "rcx", "r11", "memory");
	}
	if(n == SYS_clock_nanosleep && ts4) {
		ts4->tv_sec  = __tsc(r10)->tv_sec;
		ts4->tv_nsec = __tsc(r10)->tv_nsec;
	}
	return ret;
}

static __inline long __syscall5(long long n, long long a1, long long a2, long long a3,
                                     long long a4, long long a5)
{
	unsigned long ret;
	register long long r10 __asm__("r10") = a4;
	register long long r8 __asm__("r8") = a5;
	switch (n) {
	case SYS_mq_timedsend: case SYS_mq_timedreceive:
		if(r8) r8 = (unsigned long) (&(struct __timespec) {
		.tv_sec = __tsc(r8)->tv_sec, .tv_nsec = __tsc(r8)->tv_nsec});
	default:
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3), "r"(r10), "r"(r8) : "rcx", "r11", "memory");
	}
	return ret;
}

static __inline long __syscall6(long long n, long long a1, long long a2, long long a3,
                                     long long a4, long long a5, long long a6)
{
	unsigned long ret;
	register long long r10 __asm__("r10") = a4;
	register long long r8 __asm__("r8") = a5;
	register long long r9 __asm__("r9") = a6;
	switch (n) {
	case SYS_pselect6:
		if(r8) r8 = (unsigned long) (&(struct __timespec) {
		.tv_sec = __tsc(r8)->tv_sec, .tv_nsec = __tsc(r8)->tv_nsec});
	default:
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3), "r"(r10), "r"(r8), "r"(r9) : "rcx", "r11", "memory");
	}
	return ret;
}
