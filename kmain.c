
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

	int x = 1;
	x = x / (x - 1);
	kprintf("k : %d.\n", x);

	kprintf("Done.\n");

	((void)mboot);

	hang();
}
