
# include "kscreen.h"

# define hang() for(;;)

void kmain(int magic, void *mboot) {
	if(magic != 0x2BADB002) {
		// TODO : Assert me.
	}

	setColor(0, 15);
	writeString("Hello");

	((void)mboot);

	hang();
}
