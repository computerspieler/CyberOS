#include "kernel/asm.h"
#include "kernel/idt.h"
#include "kernel/interrupt.h"
#include "kernel/memory.h"
#include "kernel/pic.h"
#include "kernel/serial.h"

static IDT_Descriptor idt_descriptor;
static IDT_Entry idt_entries[NB_IDT_ENTRIES];

void interrupt_init()
{
	extern u32* interrupt_table_ptr;
	extern u32 interrupt_table_size;

	int i;

	serial_send_string("=== Interrupts ===\n");

	serial_send_string("Interrupt table: ");
	serial_send_value(16, (u32) interrupt_table_ptr);
	serial_send_char('\n');

	for(i = 0; i < (int) interrupt_table_size; i++)
		idt_entries[i] = IDT_create_entry(KERNEL_CODE_SEGMENT, (u32) interrupt_table_ptr[i], 0x8E);

	PIC_init();

	idt_descriptor.address = idt_entries;
	idt_descriptor.size = NB_IDT_ENTRIES * sizeof(IDT_Entry);

	IDT_PUSH_DESCRIPTOR(&idt_descriptor);
}

void general_interrupt_handler(u32 irq_id)
{
	serial_send_string("IRQ no ");
	serial_send_value(10, irq_id);
	serial_send_char('\n');

	if(irq_id >= 0x08 && irq_id <= 0x0F)
		PIC_send_EOI(true, false);

	if(irq_id >= 0x70 && irq_id <= 0x77)
		PIC_send_EOI(true, true);
}