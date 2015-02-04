
# define hang() for(;;)

__attribute__((noinline))
void testWrite(char ch) {
	*((char *)0xC00B8000) = ch;
}

void kmain(int magic, void *mboot) {
	if(magic != 0x2BADB002) {
		// TODO : Assert me.
	}

	testWrite('A');
	((void)mboot);

	hang();
}
