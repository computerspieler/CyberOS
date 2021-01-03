#ifndef _ASM_H_
#define _ASM_H_

#include "typedef.h"

void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);

void enable_interrupt();
void disable_interrupt();

#endif