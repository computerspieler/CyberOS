#include "kernel/idt.h"
#include "kernel/interrupt.h"
#include "kernel/pic.h"
#include "kernel/serial.h"

static IDT_Descriptor descriptor;
static IDT_Entry entries[NB_IDT_ENTRIES];

void interrupt_init()
{
	extern u32* interrupt_table;
	extern u32 interrupt_table_size;

	int i;

	for(i = 0; i < (int)(interrupt_table_size / sizeof(u32)); i++)
		entries[i] = IDT_create_entry(0x08, (u32) &interrupt_table[i], 0x8E);

	descriptor.address = entries;
	descriptor.size = NB_IDT_ENTRIES * sizeof(IDT_Entry);

	asm volatile("lidt (%0)" : : "r" (&descriptor));
}

void general_interrupt_handler(u32 irq_id)
{
	serial_send_string(0, "IRQ no ");
	serial_send_value(0, 10, irq_id);
	serial_send_char(0, '\n');

	if(irq_id >= 0x08 && irq_id <= 0x0F)
		PIC_send_EOI(true, false);

	if(irq_id >= 0x70 && irq_id <= 0x77)
		PIC_send_EOI(true, true);
}