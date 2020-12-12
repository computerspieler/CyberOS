#include "kernel/idt.h"
#include "kernel/interrupt.h"
#include "kernel/pic.h"
#include "kernel/serial.h"

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
