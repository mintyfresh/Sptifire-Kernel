
.file "kisrs.asm"

.global _isr0
_isr0:
	call testIsr
	iret
