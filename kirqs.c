
# include "hardware.h"

void remapPIC(int master, int slave) {
	uint8_t mask0 = inb(PIC1_DATA);
	uint8_t mask1 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT + ICW1_ICW4);
	ioWait();
	outb(PIC2_COMMAND, ICW1_INIT + ICW1_ICW4);
	ioWait();

	outb(PIC1_DATA, master);
	ioWait();
	outb(PIC2_DATA, slave);
	ioWait();

	outb(PIC1_DATA, 0b0100);
	ioWait();
	outb(PIC2_DATA, 0b0010);
	ioWait();

	outb(PIC1_DATA, ICW4_8086);
	ioWait();
	outb(PIC2_DATA, ICW4_8086);
	ioWait();

	outb(PIC1_DATA, mask0);
	outb(PIC2_DATA, mask1);
}

void toggleIRQ(uint8_t irq, int state) {
	uint8_t value;
	uint16_t port;
	if(irq >= 8) {
		port = PIC2_DATA;
		irq -= 8;
	} else {
		port = PIC1_DATA;
	}

	value = state ?
			inb(port) | (1 << irq) :
			inb(port) & ~(1 << irq);
	outb(port, value);
}
