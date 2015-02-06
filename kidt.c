
# include "kidt.h"

struct idt_pointer {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

struct idt_descriptor {
	uint16_t offset0;
	uint16_t selector;

	uint8_t zero;
	uint8_t flags;

	uint16_t offset1;
} __attribute__((packed));

static struct idt_pointer pointer;
static struct idt_descriptor entries[256];

static int idx = 0;

extern void _isr0();

void testIsr() {
	extern void writeString(char *);
	writeString("It worked!\n");
}

void idtInstall() {
	extern void idtCommit();

	int i;
	for(i = 0; i < 32; i++)
	idtCreate(_isr0, 0x08, 0x8E);

	// Commit IDT structure
	idtCommit();
}

void idtCreate(void *handler, uint16_t selector, uint8_t flags) {
	struct idt_descriptor *entry = &entries[idx++];

	entry->offset0 = (uint16_t)(((int)handler >> 00) & 0xFFFF);
	entry->offset1 = (uint16_t)(((int)handler >> 16) & 0xFFFF);

	entry->selector = selector;
	entry->flags = flags;
	entry->zero = 0;
}

void idtCommit() {
	pointer.limit = idx * sizeof(struct idt_descriptor) - 1;
	pointer.base = (uint32_t)(void *)&entries;

	__asm__("lidt (%0)" :: "r"(&pointer));
}
