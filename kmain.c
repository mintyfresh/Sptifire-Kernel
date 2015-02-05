
# include "kernel.h"
# include "kscreen.h"
# include "kstring.h"

void kmain(int magic, void *mboot) {
	// Validate multiboot magic
	assert(magic == 0x2BADB002);

	kprintf("Done.\n");

	char *test = "Hello!";
	char buffer[64];

	kprintf("%s : %s.\n", test, strcpy(buffer, test));

	((void)mboot);

	hang();
}
