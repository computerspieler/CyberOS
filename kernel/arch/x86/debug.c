#include <stddef.h>

#include "debug.h"
#include "memory.h"
#include "serial.h"

int debug_init()
{
	return 0;
}

int debug_print_multiboot(Multiboot_Info* info)
{
	Multiboot_Memory_Map_Entry *entry;

	serial_send_string("CyberOS version unknown");
	serial_send_char('\n');

	serial_send_string("=== Multiboot info ===\n");
	serial_send_string("Flags: ");
	serial_send_value(2, info->flags);

	serial_send_string("\nLow memory: ");
	serial_send_value(16, info->mem_lower);
	serial_send_string("\nHigh memory: ");
	serial_send_value(16, info->mem_upper);

	serial_send_string("\nMemory map : Address: ");
	serial_send_value(16, info->mmap_address);
	serial_send_string("; Length: ");
	serial_send_value(16, info->mmap_length);

	for(entry = (Multiboot_Memory_Map_Entry*) info->mmap_address;
		entry < (Multiboot_Memory_Map_Entry*)(info->mmap_address + info->mmap_length);
		entry = (Multiboot_Memory_Map_Entry*) ((uint32_t)entry + entry->size + sizeof(entry->size)))
	{
		serial_send_string("\n Memory entry: Address: ");
		serial_send_value(16, entry->address >> 32);
		serial_send_value(16, (uint32_t) entry->address);
		serial_send_string("; Length (in pages): ");
		serial_send_value(10, entry->length / MEMORY_PAGE_SIZE);
		serial_send_string("; Type: ");
		serial_send_value(16, entry->type);
	}

	serial_send_char('\n');

	return 0;
}

int debug_print_gdt(GDT_Descriptor* descriptor)
{
	int i;
	int j;

	GDT_Entry entry;

	serial_send_string("=== GDT Descriptor ===\n");
	serial_send_string("Address: ");
	serial_send_value(16, descriptor->address);
	serial_send_string("\nSize: ");
	serial_send_value(16, descriptor->size);
	serial_send_string("\nEntries: \n");

	for(i = 0; i < descriptor->size / sizeof(GDT_Entry); i++)
	{
		entry = descriptor->address[i];

		serial_send_string(" Base: ");
		serial_send_value(16, (entry.base_high << 24) + entry.base_low);

		serial_send_string("; Limit: ");
		serial_send_value(16, (entry.limit_high << 16) + entry.limit_low);

		serial_send_string("; Access: ");
		serial_send_value(16, entry.access);

		serial_send_string("; Flags: ");
		serial_send_value(16, entry.flags);

		serial_send_string("; Address : ");
		serial_send_value(16, (uint32_t)(&descriptor->address[i]));

		serial_send_char('\n');
	}

	return 0;
}
