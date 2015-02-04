
# include "kernel.h"
# include "kscreen.h"

void kmain(int magic, void *mboot) {
	// Validate multiboot magic
	assert(magic == 0x2BADB002 + 1);

	writeString("Hello");

	((void)mboot);

	hang();
}
