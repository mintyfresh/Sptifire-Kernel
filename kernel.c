
# include "kscreen.h"

__attribute__((noreturn))
void hang() {
	for(;;) __asm__("hlt");
}

__attribute__((noreturn))
void panic(char *text, char *file, int line) {
	writeString("Kernel Panic!");

	// TODO
	((void)text);
	((void)file);
	((void)line);

	hang();
}

__attribute__((noreturn))
void abort(char *text) {
	writeString(text);

	__asm__("cli");
	hang();
}
