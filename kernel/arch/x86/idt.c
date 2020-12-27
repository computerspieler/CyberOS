#include "kernel/idt.h"

IDT_Entry IDT_create_entry(u16 selector, u32 offset, u8 flags)
{
	IDT_Entry entry;

	entry.offset_low = offset & 0xFFFF;
	entry.offset_high = offset >> 16;

	entry.flags = flags;
	entry.selector = selector;

	return entry; 
}