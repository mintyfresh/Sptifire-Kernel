
.file "isrdef.asm"

.macro isr id
	.global _isr\id
	.extern isrHandle\id
	.type _isr\id, @function
	_isr\id:
		call isrHandle\id
		iret
.endm
