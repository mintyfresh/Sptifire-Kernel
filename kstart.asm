
.file "kstart.asm"
.extern kmain

# Constant Definitions

.set FLAGS,		1 + 2
.set MAGIC,		0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)

.set PRESENT,	(1 << 0)
.set READWRITE,	(1 << 1)
.set LARGEPAGE,	(1 << 7)

.set VOFFSET,	0xC0000000

# Multiboot Header

.section .mboot
.align 4

.global _mbootHeader
_mbootHeader:
	.long MAGIC
	.long FLAGS
	.long CHECKSUM

# Kernel Entry (Lower Half)

.section .textlow
.align 4

.global _startLow
_startLow:
	cli

	movl $(_pageDirectory - VOFFSET), %ecx
	movl %ecx, %cr3

	movl %cr4, %ecx
	orl $0x10, %ecx
	movl %ecx, %cr4

	movl %cr0, %ecx
	orl $0x80000000, %ecx
	movl %ecx, %cr0

	leal (_start), %ecx
	jmp *%ecx

# Kernel Entry (Higher Half)

.section .text
.align 4

.global _start
_start:
	movl $_stackStart, %esp

	pushl $0
	popf

	addl $VOFFSET, %ebx
	pushl %ebx # Multiboot Pointer
	pushl %eax # Multiboot Magic

	call kmain

_kHang:
	hlt
	jmp _kHang

# Kernel Page Directory

.section .data
.align 4096

.global _pageDirectory
_pageDirectory:
	.long PRESENT | READWRITE | LARGEPAGE
	.fill 768 - 1, 4, 0
	.long PRESENT | READWRITE | LARGEPAGE
	.fill 1024 - 786, 4, 0

# Kernel Stack

.section .bss
.align 32

_stackEnd:
	.fill 8192
_stackStart:
