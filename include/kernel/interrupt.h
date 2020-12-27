#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

void interrupt_init();
void general_interrupt_handler(uint32_t irq_id);

#endif