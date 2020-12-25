#include "kernel/asm.h"
#include "kernel/idt.h"
#include "kernel/interrupt.h"
#include "kernel/pic.h"
#include "kernel/serial.h"

static IDT_Descriptor descriptor;
static IDT_Entry entries[NB_IDT_ENTRIES];

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
		entries[i] = IDT_create_entry(0x10, (u32) interrupt_table_ptr[i], 0x8E);

	descriptor.address = entries;
	descriptor.size = NB_IDT_ENTRIES * sizeof(IDT_Entry);

	PIC_init();

	asm volatile("lidt (%0)" : : "r" (&descriptor));
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