#include "kernel/asm.h"

void outb(u16 port, u8 data)
{
	asm volatile("out %0, %1" : : "r" (data), "r" (port));
}

u8 inb(u16 port)
{
	u8 data = 0;
	asm volatile("in %1, %0" : "+r" (data) : "r" (port));
	return data;
}