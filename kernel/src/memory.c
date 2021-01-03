#include "asm.h"
#include "gdt.h"
#include "memory.h"
#include "multiboot.h"
#include "serial.h"

#define XSTR(x) STR(x)
#define STR(x) #x

static GDT_Descriptor gdt_descriptor;
static GDT_Entry gdt_entries[3];

void memory_init(Multiboot_Info* info)
{
	GDT_Descriptor* old_descriptor;

	debug_print_multiboot(info);
	GDT_FETCH_DESCRIPTOR(old_descriptor);
	debug_print_gdt(old_descriptor);

	// Create the new segments for the kernel
	gdt_descriptor.address = gdt_entries;
	gdt_descriptor.size = 3 * sizeof(GDT_Entry);

	gdt_entries[0] = GDT_create_entry(0, 0, 0, 0);
	/* Kernel Code Entry */
	gdt_entries[1] = GDT_create_code_selector(0, 0xFFFFF, GDT_FLAGS_PAGE_BLOCK | GDT_FLAGS_32_BITS_SELECTOR, 0);
	/* Kernel Data Entry */
	gdt_entries[2] = GDT_create_data_selector(0, 0xFFFFF, GDT_FLAGS_PAGE_BLOCK | GDT_FLAGS_32_BITS_SELECTOR, 0);
	
	serial_send_string("[INFO] Push a new GDT\n");
	debug_print_gdt(&gdt_descriptor);

	GDT_PUSH_DESCRIPTOR(&gdt_descriptor);

	// Reload segments
	asm("mov $" XSTR(KERNEL_DATA_SEGMENT) ", %ax");
	asm("mov %ax, %ds");
	asm("mov %ax, %es");
	asm("mov %ax, %fs");
	asm("mov %ax, %gs");
	asm("mov %ax, %ss");
	asm("ljmp $" XSTR(KERNEL_CODE_SEGMENT) ", $next");
	asm("next:");
}