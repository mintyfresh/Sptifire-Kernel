OUTPUT_FORMAT(elf32-i386)
ENTRY(_startLow)

PHYSICAL = 0x00100000;
VIRTUAL  = 0xC0000000;

SECTIONS {

	. = PHYSICAL;

	_pstart = .;

	. += VIRTUAL;

	_vstart = .;

	.text ALIGN(4) : AT(ADDR(.text) - VIRTUAL) {
		*(.mboot)
		*(.textlow)
		*(.text)
	}

	.rodata ALIGN(4) : AT(ADDR(.rodata) - VIRTUAL) {
		*(.rodata)
	}

	.data ALIGN(4K) : AT(ADDR(.data) - VIRTUAL) {
		*(.data)
	}

	.bss ALIGN(32) : AT(ADDR(.bss) - VIRTUAL) {
		*(COMMON)
		*(.bss)
	}

	_end = .;

}

