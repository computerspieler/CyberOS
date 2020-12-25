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

	serial_send_string(0, "=== Multiboot info ===\n");
	serial_send_string(0, "Flags: ");
	serial_send_value(0, 2, info->flags);

	serial_send_string(0, "\nLow memory: ");
	serial_send_value(0, 16, info->mem_lower);
	serial_send_string(0, "\nHigh memory: ");
	serial_send_value(0, 16, info->mem_upper);

	serial_send_string(0, "\nMemory map : Address: ");
	serial_send_value(0, 16, info->mmap_address);
	serial_send_string(0, "; Length: ");
	serial_send_value(0, 16, info->mmap_length);

	for(entry = (Multiboot_Memory_Map_Entry*) info->mmap_address;
		entry < (Multiboot_Memory_Map_Entry*)(info->mmap_address + info->mmap_length);
		entry = (Multiboot_Memory_Map_Entry*) ((u32)entry + entry->size + sizeof(entry->size)))
	{
		serial_send_string(0, "\n Memory entry: Address: ");
		serial_send_value(0, 16, entry->address_high);
		serial_send_value(0, 16, entry->address_low);
		serial_send_string(0, "; Length: ");
		serial_send_value(0, 10, entry->length);
		serial_send_string(0, "; Type: ");
		serial_send_value(0, 16, entry->type);
	}

	serial_send_string(0, "\n");

	return 0;
}

int debug_print_gdt(GDT_Descriptor* descriptor)
{
	GDT_Entry* entry;
	u32 entry_address;
	u32 entry_limit;
	u8 entry_access;
	u8 entry_flags;

	serial_send_string(0, "=== GDT Descriptor ===\n");
	serial_send_string(0, "Address: ");
	serial_send_value(0, 16, descriptor->address);
	serial_send_string(0, "\nSize: ");
	serial_send_value(0, 16, descriptor->size);
	serial_send_string(0, "\nEntries: \n");
	for(entry = (GDT_Entry*) descriptor->address;
		entry < (GDT_Entry*)(descriptor->address + descriptor->size);
		entry += sizeof(GDT_Entry))
	{
		entry_address = (*entry >> 56 & 0xFF << 24) + (*entry >> 16 & 0xFFFFFF);
		entry_limit = (*entry >> 48 & 0xFF << 16) + (*entry & 0xFFFF);
		entry_access = *entry >> 40 & 0xFF;
		entry_flags	= *entry >> 52 & 0xF;

		serial_send_string(0, " Address: ");
		serial_send_value(0, 16, entry_address);

		serial_send_string(0, "; Limit: ");
		serial_send_value(0, 16, entry_limit);

		serial_send_string(0, "; Access: ");
		serial_send_value(0, 16, entry_access);

		serial_send_string(0, "; Flags: ");
		serial_send_value(0, 16, entry_flags);
		
		serial_send_string(0, "\n");
	}

	return 0;
}