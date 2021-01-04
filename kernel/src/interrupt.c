#include "asm.h"
#include "idt.h"
#include "interrupt.h"
#include "memory.h"
#include "pic.h"
#include "serial.h"

static IDT_Descriptor idt_descriptor;
static IDT_Entry idt_entries[NB_IDT_ENTRIES];

void interrupt_init()
{
	extern uint32_t* interrupt_table_ptr;
	extern uint32_t interrupt_table_size;

	int i;

	serial_send_string("=== Interrupts ===\n");

	serial_send_string("Interrupt table: ");
	serial_send_value(16, (uint32_t) interrupt_table_ptr);
	serial_send_char('\n');

	for(i = 0; i < (int) interrupt_table_size; i++)
		idt_entries[i] = IDT_create_entry(KERNEL_CODE_SEGMENT, (uint32_t) interrupt_table_ptr[i], 0x8E);

	PIC_init();

	idt_descriptor.address = idt_entries;
	idt_descriptor.size = NB_IDT_ENTRIES * sizeof(IDT_Entry);

	IDT_PUSH_DESCRIPTOR(&idt_descriptor);
}

void general_interrupt_handler(uint32_t irq_id)
{
	serial_send_string("IRQ no ");
	serial_send_value(10, irq_id);
	serial_send_char('\n');

	if(irq_id >= MASTER_PIC_OFFSET && irq_id <= MASTER_PIC_OFFSET + 7)
		PIC_send_EOI(true, false);

	if(irq_id >= SLAVE_PIC_OFFSET && irq_id <= SLAVE_PIC_OFFSET + 7)
		PIC_send_EOI(true, true);
}