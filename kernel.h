# ifndef __KERNEL_H__
# define __KERNEL_H__

__attribute__((noreturn))
void hang();

__attribute__((noreturn))
void panic(char *text, char *file, int line);

__attribute__((noreturn))
void abort(char *text);

# define interrupts_on()	\
	__asm__ __volatile__("sti")

# define interrupts_off()	\
	__asm__ __volatile__("cli")

# define assert(expr)			\
	((void)((expr) ? 0 : panic(	\
		"Assertion failed: " #expr, __FILE__, __LINE__)))

# endif /* kernel.h */