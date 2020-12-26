#include "typedef.h"

#include "kernel/debug.h"
#include "kernel/interrupt.h"
#include "kernel/multiboot.h"
#include "kernel/serial.h"

void main(Multiboot_Info* info, u32 magic)
{
	serial_init();
	debug_init();
/*
	For some reasons, interrupts needs to be initialized before memory,
	since the IDT overwrite the GDT, weird right ?
*/
	interrupt_init();
	memory_init(info);

	serial_send_string("Magic number: ");
	serial_send_value(16, magic);
	serial_send_char('\n');

	enable_interrupt();
	while(true);
}
