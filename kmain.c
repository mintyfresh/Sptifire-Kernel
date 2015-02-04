
# include "kernel.h"
# include "kscreen.h"

void kmain(int magic, void *mboot) {
	// Validate multiboot magic
	assert(magic == 0x2BADB002);

	writeString("Hello\n");
	writeString("Hello\n");
	kprintf("Words!\n");
	kprintf("More %s!\n", "words");
	kprintf("A character %c.\n", 'A');
	kprintf("A number %d!\n", 12345);
	kprintf("A number %d!\n", -12345);
	kprintf("Function 0x%p.\n", kmain);

	((void)mboot);

	hang();
}
