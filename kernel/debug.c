#include "typedef.h"

#include "kernel/debug.h"
#include "kernel/serial.h"

int debug_init()
{
	return 0;
}

int debug_print_multiboot(Multiboot_Info* info)
{
	Multiboot_Memory_Map_Entry *entry;

	serial_send_string("CyberOS build ");
	serial_send_value(10, BUILD_NO);
	serial_send_string("\n");

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
		entry = (Multiboot_Memory_Map_Entry*) ((u32)entry + entry->size + sizeof(entry->size)))
	{
		serial_send_string("\n Memory entry: Address: ");
		serial_send_value(16, entry->address_high);
		serial_send_value(16, entry->address_low);
		serial_send_string("; Length: ");
		serial_send_value(10, entry->length);
		serial_send_string("; Type: ");
		serial_send_value(16, entry->type);
	}

	serial_send_string("\n");

	return 0;
}

int debug_print_gdt(GDT_Descriptor* descriptor)
{
	GDT_Entry* entry;
	u32 entry_address;
	u32 entry_limit;
	u8 entry_access;
	u8 entry_flags;

	serial_send_string("=== GDT Descriptor ===\n");
	serial_send_string("Address: ");
	serial_send_value(16, descriptor->address);
	serial_send_string("\nSize: ");
	serial_send_value(16, descriptor->size);
	serial_send_string("\nEntries: \n");
	for(entry = (GDT_Entry*) descriptor->address;
		entry < (GDT_Entry*)(descriptor->address + descriptor->size);
		entry += sizeof(GDT_Entry))
	{
		entry_address = (*entry >> 56 & 0xFF << 24) + (*entry >> 16 & 0xFFFFFF);
		entry_limit = (*entry >> 48 & 0xFF << 16) + (*entry & 0xFFFF);
		entry_access = *entry >> 40 & 0xFF;
		entry_flags	= *entry >> 52 & 0xF;

		serial_send_string(" Address: ");
		serial_send_value(16, entry_address);

		serial_send_string("; Limit: ");
		serial_send_value(16, entry_limit);

		serial_send_string("; Access: ");
		serial_send_value(16, entry_access);

		serial_send_string("; Flags: ");
		serial_send_value(16, entry_flags);
		
		serial_send_string("\n");
	}

	return 0;
}