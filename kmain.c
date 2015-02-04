
# define hang() for(;;)

extern void writeString(char *);
extern void setColor(char, char);

void kmain(int magic, void *mboot) {
	if(magic != 0x2BADB002) {
		// TODO : Assert me.
	}

	setColor(0, 15);
	writeString("Hello");

	((void)mboot);

	hang();
}
