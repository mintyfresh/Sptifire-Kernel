OUTPUT_FORMAT(elf32-i386)
ENTRY(_startLow)

SECTIONS {

	. = 0x00100000;

	_pstart = .;

	.mboot ALIGN(4) : AT(ADDR(.mboot)) {
		*(.mboot)
		*(.textlow)
	}

	. += 0xC0000000;

	_vstart = .;

	.text ALIGN(4) : AT(ADDR(.text) - 0xC0000000) {
		*(.text)
	}

	.rodata ALIGN(4) : AT(ADDR(.rodata) - 0xC0000000) {
		*(.rodata)
	}

	.data ALIGN(4K) : AT(ADDR(.data) - 0xC0000000) {
		*(.data)
	}

	.bss ALIGN(32) : AT(ADDR(.bss) - 0xC0000000) {
		*(COMMON)
		*(.bss)
	}

	_end = .;

}

