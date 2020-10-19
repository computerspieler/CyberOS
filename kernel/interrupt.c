#include "kernel/idt.h"
#include "kernel/interrupt.h"
#include "kernel/serial.h"

#define IRQ_HANDLER(x) \
	__attribute__((interrupt)) void irq##x##_handler(struct interrupt_frame* frame) \
	{ \
		general_interrupt_handler(frame, x); \
	}

IRQ_HANDLER(0)
IRQ_HANDLER(1)
IRQ_HANDLER(2)
IRQ_HANDLER(3)
IRQ_HANDLER(4)
IRQ_HANDLER(5)
IRQ_HANDLER(6)
IRQ_HANDLER(7)
IRQ_HANDLER(8)
IRQ_HANDLER(9)
IRQ_HANDLER(10)
IRQ_HANDLER(11)
IRQ_HANDLER(12)
IRQ_HANDLER(13)
IRQ_HANDLER(14)
IRQ_HANDLER(15)
IRQ_HANDLER(16)
IRQ_HANDLER(17)
IRQ_HANDLER(18)
IRQ_HANDLER(19)
IRQ_HANDLER(20)
IRQ_HANDLER(21)
IRQ_HANDLER(22)
IRQ_HANDLER(23)
IRQ_HANDLER(24)
IRQ_HANDLER(25)
IRQ_HANDLER(26)
IRQ_HANDLER(27)
IRQ_HANDLER(28)
IRQ_HANDLER(29)
IRQ_HANDLER(30)
IRQ_HANDLER(31)
IRQ_HANDLER(32)

void general_interrupt_handler(struct interrupt_frame* frame, int irq_id)
{
	serial_send_string(0, "IRQ");
	serial_send_value(0, 10, irq_id);
	serial_send_char(0, '\n');
}