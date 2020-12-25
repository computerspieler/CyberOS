#include "typedef.h"

#include "kernel/asm.h"
#include "kernel/debug.h"
#include "kernel/interrupt.h"
#include "kernel/multiboot.h"
#include "kernel/serial.h"

void main(Multiboot_Info* info, u32 magic)
{
	GDT_Descriptor* actual_gdt;

	serial_init();
	interrupt_init();
	debug_init();

	serial_send_string(0, "Magic number: ");
	serial_send_value(0, 16, magic);
	serial_send_string(0, "\n");

	debug_print_multiboot(info);
	extract_actual_gdt(actual_gdt);
	debug_print_gdt(actual_gdt);
	//enable_interrupt();

	while(true);
}
