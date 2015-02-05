# ifndef __K_GDT_H__
# define __K_GDT_H__

# ifndef _TYPE_SIZE_T
#	include "kstring.h"
# endif /* size_t */

# define GDT_ACCESSED		(1 << 0)
# define GDT_READONLY		(0 << 1)
# define GDT_READWRITE		(1 << 1)
# define GDT_DATAUP			(0 << 2)
# define GDT_DATADOWN		(1 << 2)
# define GDT_CONFORMING		(1 << 2)
# define GDT_DATA_SELECTOR	(0 << 3)
# define GDT_CODE_SELECTOR	(1 << 3)
# define GDT_ALWAYS_1		(1 << 4)
# define GDT_RING_0			(0 << 5)
# define GDT_RING_1			(1 << 5)
# define GDT_RING_2			(2 << 5)
# define GDT_RING_3			(3 << 5)
# define GDT_PRESENT		(1 << 7)

# define GDT_PROTECTED_16	(0 << 10)
# define GDT_PROTECTED_32	(1 << 10)
# define GDT_BYTE_GRAN		(0 << 11)
# define GDT_PAGE_GRAN		(1 << 11)

# define KERNEL_CODE (\
	GDT_PRESENT | GDT_CODE_SELECTOR | GDT_RING_0 | GDT_READONLY | \
	GDT_PROTECTED_32 | GDT_PAGE_GRAN | GDT_ALWAYS_1)

# define KERNEL_DATA (\
	GDT_PRESENT | GDT_DATA_SELECTOR | GDT_RING_0 | GDT_READWRITE | \
	GDT_PROTECTED_32 | GDT_PAGE_GRAN | GDT_ALWAYS_1)

# define USER_CODE (\
	GDT_PRESENT | GDT_CODE_SELECTOR | GDT_RING_3 | GDT_READONLY | \
	GDT_PROTECTED_32 | GDT_PAGE_GRAN | GDT_ALWAYS_1)

# define USER_DATA (\
	GDT_PRESENT | GDT_DATA_SELECTOR | GDT_RING_3 | GDT_READWRITE | \
	GDT_PROTECTED_32 | GDT_PAGE_GRAN | GDT_ALWAYS_1)

void gdtInstall();

void gdtCreate(void *base, size_t limit, int flags);

# endif /* kgdt.h */
