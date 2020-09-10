
# include "kgdt.h"
# include <stdint.h>

struct gdt_descriptor {
	uint16_t size;
	uint32_t offset;
} __attribute__((packed));

struct gdt_entry {
	uint16_t limit0;
	uint16_t base0;

	uint8_t base1;
	uint8_t access;

	uint8_t limit1 : 4;
	uint8_t flags : 4;

	uint8_t base2;
} __attribute__((packed));

static struct gdt_descriptor descriptor;
static struct gdt_entry entries[6];

static int idx = 0;

void gdtInstall() {
	extern void gdtCommit();

	gdtCreate(NULL, 0x00000000, 0);
	gdtCreate(NULL, 0xFFFFFFFF, KERNEL_CODE);
	gdtCreate(NULL, 0xFFFFFFFF, KERNEL_DATA);
	gdtCreate(NULL, 0xFFFFFFFF, USER_CODE);
	gdtCreate(NULL, 0xFFFFFFFF, USER_DATA);

	// Commit GDT structure
	gdtCommit();
}

void gdtCreate(void *base, size_t limit, int flags) {
	struct gdt_entry *entry = &entries[idx++];

	entry->limit0 = (limit & 0xFFFF);
	entry->limit1 = (limit >> 16) & 0xF;

	entry->base0 = ((int)base & 0xFFFF);
	entry->base1 = ((int)base >> 16) & 0xFF;
	entry->base2 = ((int)base >> 24) & 0xFF;

	entry->access = flags & 0xFF;
	entry->flags = (flags >> 8) & 0xF;
}

__attribute__((noinline)) void gdtCommit() {
	descriptor.size = sizeof(struct gdt_entry) * idx - 1;
	descriptor.offset = (uint32_t)(void *)&entries;

	__asm__("lgdt (%0)" :: "r"(&descriptor));
	__asm__("movl %0, %%ds" :: "a"(0x10));
	__asm__("movl %0, %%es" :: "a"(0x10));
	__asm__("movl %0, %%fs" :: "a"(0x10));
	__asm__("movl %0, %%gs" :: "a"(0x10));
	__asm__("movl %0, %%ss" :: "a"(0x10));
	__asm__("jmp $0x8, $gdt_commit_end");
	__asm__("gdt_commit_end:");
}
