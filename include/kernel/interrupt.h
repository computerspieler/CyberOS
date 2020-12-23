#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

void interrupt_init();
void general_interrupt_handler(u32 irq_id);

#endif