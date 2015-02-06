# ifndef __K_IDT_H__
# define __K_IDT_H__

# include <stdint.h>

void idtInstall();

void idtCreate(void *handler, uint16_t selector, uint8_t flags);

# endif /* kidt.h */
