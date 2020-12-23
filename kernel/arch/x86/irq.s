.code32
.altmacro

# Handlers
.macro INTERRUPT_HANDLER id
	.global irq\id\()_handler_entry
	irq\id\()_handler_entry:
		pusha
		movw \id, %ax
		pushl %eax
		call general_interrupt_handler
		popl %eax
		popa
		iret 
.endm

.section .text
.set i, 0
.rept 256
	INTERRUPT_HANDLER %i
	.set i, i+1
.endr

# Table
.macro INTERRUPT_ENTRY id
	.long irq\id\()_handler_entry
.endm

.section .data
.global interrupt_table
interrupt_table:
	.set i, 0
	.rept 256
		INTERRUPT_ENTRY %i
		.set i, i+1
	.endr

.global interrupt_table_size
interrupt_table_size: .long . - interrupt_table
