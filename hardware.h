# ifndef __HARDWARE_H__
# define __HARDWARE_H__

# include <stdint.h>

# define PIC1_COMMAND 0x20
# define PIC2_COMMAND 0xA0

# define PIC1_DATA 0x21
# define PIC2_DATA 0xA1

# define PIC_EOI 0x20

# define ICW1_ICW4 0x01
# define ICW1_INIT 0x10
# define ICW4_8086 0x01

# define interrupts_on()	\
	__asm__ __volatile__("sti")

# define interrupts_off()	\
	__asm__ __volatile__("cli")

static __inline__
uint8_t inb(short port) {
	uint8_t value;
	__asm__ __volatile__("inb %1, %0"
			: "=a"(value)
			: "Nd"(port));
	return value;
}

static __inline__
uint16_t inw(short port) {
	uint16_t value;
	__asm__ __volatile__("inw %1, %0"
			: "=a"(value)
			: "Nd"(port));
	return value;
}

static __inline__
uint32_t inl(short port) {
	uint32_t value;
	__asm__ __volatile__("inl %1, %0"
			: "=a"(value)
			: "Nd"(port));
	return value;
}

static __inline__
void outb(short port, uint8_t value) {
	__asm__ __volatile__("outb %0, %1"
			:: "a"(value), "Nd"(port));
}

static __inline__
void outw(short port, uint16_t value) {
	__asm__ __volatile__("outw %0, %1"
			:: "a"(value), "Nd"(port));
}

static __inline__
void outl(short port, uint32_t value) {
	__asm__ __volatile__("outl %0, %1"
			:: "a"(value), "Nd"(port));
}

# define ioWait() outb(0x80, 0)

static __inline__
void invlpg(void *addr) {
	__asm__ __volatile__("invlpg (%0)"
			:: "b"(addr) : "memory");
}

static __inline__
uint64_t readMSR(uint32_t id) {
	uint64_t value;
	__asm__ __volatile__("rdmsr"
			: "=A"(value) : "c"(id));
	return value;
}

static __inline__
void writeMSR(uint32_t id, uint64_t value) {
	__asm__ __volatile__("wrmsr"
			:: "c"(id), "A"(value));
}

static __inline__
void sendEOI(uint8_t irq) {
	if(irq >= 8) outb(PIC2_COMMAND, PIC_EOI);
	outb(PIC1_COMMAND, PIC_EOI);
}

void remapPIC(int master, int slave);

void toggleIRQ(uint8_t irq, int state);

# endif /* hardware.h */