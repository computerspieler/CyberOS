#include "kernel/gdt.h"

GDT_Entry GDT_create_entry(u32 base_address, u32 limit, u8 flags, u8 access)
{
	GDT_Entry entry;

	entry.base_low = base_address & 0xFFFFFF;
	entry.base_high = base_address >> 24 & 0xFF;

	entry.limit_low = limit & 0xFFFF;
	entry.limit_high = limit >> 16 & 0xF;

	entry.access = access;
	entry.flags = flags & 0xF;

	return entry; 
}
