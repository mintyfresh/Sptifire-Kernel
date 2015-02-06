
# include "kgdt.h"
# include "kidt.h"
# include "kernel.h"
# include "kscreen.h"
# include "kstring.h"

void kmain(int magic, void *mboot) {
	// Validate multiboot magic
	assert(magic == 0x2BADB002);

	kprintf("Loading GDT.\n");
	gdtInstall();

	kprintf("Loading IDT.\n");
	idtInstall();

	__asm__("int $5");

	kprintf("Done.\n");

	((void)mboot);

	hang();
}
