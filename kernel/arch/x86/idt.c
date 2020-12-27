#include "kernel/idt.h"

IDT_Entry IDT_create_entry(uint16_t selector, uint32_t offset, uint8_t flags)
{
	IDT_Entry entry;

	entry.offset_low = offset & 0xFFFF;
	entry.offset_high = offset >> 16;

	entry.flags = flags;
	entry.selector = selector;

	return entry; 
}