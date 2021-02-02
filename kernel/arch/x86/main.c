#include <stddef.h>

#include "debug.h"
#include "interrupt.h"
#include "memory.h"
#include "multiboot.h"
#include "segments.h"
#include "serial.h"

void kmain(Multiboot_Info* info, uint32_t magic)
{
	int i;
	void* address;

	serial_init();
	debug_init();
/*
	For some reasons, interrupts needs to be initialized before memory,
	since the IDT overwrite the GDT, weird right ?
*/
	interrupt_init();
	segments_init(info);

	serial_send_string("Magic number: ");
	serial_send_value(16, magic);
	serial_send_char('\n');

	memory_init();
	serial_send_string("=== Page allocations ===\n");
	for(i = 0; i < 10; i++)
	{
		serial_send_string("Page ");
		serial_send_value(10, i);
		serial_send_string(": Address = ");
		address = memory_find_available_page(info);
		serial_send_value(16, (uint32_t) address);
		serial_send_char('\n');
	}

	enable_interrupt();
	while(true);
}
