#include <stddef.h>

#include "debug.h"
#include "interrupt.h"
#include "multiboot.h"
#include "serial.h"

void kmain(Multiboot_Info* info, uint32_t magic)
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