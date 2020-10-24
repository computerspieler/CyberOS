#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

struct interrupt_frame;

void general_interrupt_handler(u32 irq_id, struct interrupt_frame* frame);

#endif