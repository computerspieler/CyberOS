#include "asm.h"
#include "gdt.h"
#include "segments.h"
#include "multiboot.h"
#include "serial.h"
#include "tss.h"

#define XSTR(x) STR(x)
#define STR(x) #x

#define NB_GDT_ENTRIES 6

static Task_State_Structure kernel_tss;
static GDT_Descriptor gdt_descriptor;
static GDT_Entry gdt_entries[NB_GDT_ENTRIES];

void segments_init(Multiboot_Info* info)
{
	GDT_Descriptor* old_descriptor;

	debug_print_multiboot(info);
	GDT_FETCH_DESCRIPTOR(old_descriptor);
	debug_print_gdt(old_descriptor);

	// Create the new segments for the kernel
	gdt_descriptor.address = gdt_entries;
	gdt_descriptor.size = NB_GDT_ENTRIES * sizeof(GDT_Entry);

	// Create kernel's TSS
	kernel_tss.ss0 = 2 * sizeof(GDT_Entry);			// Kernel's data segment
	kernel_tss.esp0 = 0;							// Stack pointer value during system call, unset for now
	kernel_tss.iopb = sizeof(Task_State_Structure);	// There's no plan to use io bitmap for now

	gdt_entries[0] = GDT_create_entry(0, 0, 0, 0);
	/* Kernel Code Entry */
	gdt_entries[1] = GDT_create_code_selector(0, 0xFFFFF, GDT_FLAGS_PAGE_BLOCK | GDT_FLAGS_32_BITS_SELECTOR, 0);
	/* Kernel Data Entry */
	gdt_entries[2] = GDT_create_data_selector(0, 0xFFFFF, GDT_FLAGS_PAGE_BLOCK | GDT_FLAGS_32_BITS_SELECTOR, 0);
	/* Kernel TSS */
	gdt_entries[3] = GDT_create_task_segment_selector(&kernel_tss, 0);
	/* Userspace Code Entry */
	gdt_entries[4] = GDT_create_code_selector(0, 0xFFFFF, GDT_FLAGS_PAGE_BLOCK | GDT_FLAGS_32_BITS_SELECTOR, 3);
	/* Userspace Data Entry */
	gdt_entries[5] = GDT_create_data_selector(0, 0xFFFFF, GDT_FLAGS_PAGE_BLOCK | GDT_FLAGS_32_BITS_SELECTOR, 3);
	
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
