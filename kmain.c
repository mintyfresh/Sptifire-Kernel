
# include "kernel.h"
# include "kscreen.h"

void kmain(int magic, void *mboot) {
	// Validate multiboot magic
	assert(magic == 0x2BADB002);

	kprintf("Done.\n");

	((void)mboot);

	hang();
}
