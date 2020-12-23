#include "kernel/idt.h"

IDT_Entry IDT_create_entry(u16 selector, u32 offset, u8 flags)
{
	IDT_Entry entry;

	entry  = offset & 0xFFFF0000;
	entry |= flags << 8;

	entry <<= 32;

	entry |= selector << 16;
	entry |= offset   & 0xFFFF;

	return entry; 
}