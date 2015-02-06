# ifndef __HARDWARE_H__
# define __HARDWARE_H__

# include <stdint.h>

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

# endif /* hardware.h */