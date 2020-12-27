#include "kernel/asm.h"

void outb(uint16_t port, uint8_t data)
{
	asm volatile("out %0, %1" : : "r" (data), "r" (port));
}

uint8_t inb(uint16_t port)
{
	uint8_t data = 0;
	asm volatile("in %1, %0" : "+r" (data) : "r" (port));
	return data;
}

void enable_interrupt()
{
	asm("sti");
}

void disable_interrupt()
{
	asm("cli");
}