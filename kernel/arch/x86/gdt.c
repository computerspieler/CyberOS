#include "kernel/gdt.h"

GDT_Entry GDT_create_entry(u32 base_address, u32 limit, u8 flags, u8 access)
{
	GDT_Entry entry;

	entry  = base_address & 0xFF000000;
	entry |= (access & 0xF) << 20;
	entry |= limit & 0xF0000;
	entry |= flags << 8;
	entry |= base_address >> 16 & 0xFF;

	entry <<= 32;

	entry |= base_address & 0xFFFF << 16;
	entry |= limit & 0xFFFF;

	return entry; 
}