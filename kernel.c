
# include "kscreen.h"

__attribute__((noreturn))
void hang() {
	for(;;) __asm__("hlt");
}

__attribute__((noreturn))
void panic(char *text, char *file, int line) {
	setColor(White, White);
	clear();

	setCursor(34, 9);
	setColor(Red, White);
	kprintf(" Kernel Panic! \n\n");

	setColor(White, Red);
	kprintf("%s\n", text);
	kprintf("In %s at line %d.\n", file, line);

	__asm__("cli");
	hang();
}

__attribute__((noreturn))
void abort(char *text) {
	writeString(text);

	__asm__("cli");
	hang();
}
