
.file "kisrs.asm"

.global _isr0
_isr0:
	leal (testIsr), %ecx
	call *%ecx
	iret
