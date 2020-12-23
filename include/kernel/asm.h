#ifndef _ASM_H_
#define _ASM_H_

#include "typedef.h"

void outb(u16 port, u8 data);
u8 inb(u16 port);

void enable_interrupt();
void disable_interrupt();

#endif