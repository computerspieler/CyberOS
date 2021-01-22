#include "gdt.h"

GDT_Entry GDT_create_entry(uint32_t base_address, uint32_t limit, uint8_t flags, uint8_t access)
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

GDT_Entry GDT_create_code_selector(uint32_t base_address, uint32_t limit, uint8_t flags, uint8_t privilege)
{
	return GDT_create_entry(0, 0xFFFFF, flags,
		GDT_ACCESS_PRESENT				|
		GDT_ACCESS_PRIVILEGE(privilege) |
		GDT_ACCESS_DESCRIPTOR			|
		GDT_ACCESS_CODE_SELECTOR		|
		GDT_ACCESS_READ_WRITE);
}

GDT_Entry GDT_create_data_selector(uint32_t base_address, uint32_t limit, uint8_t flags, uint8_t privilege)
{
	return GDT_create_entry(0, 0xFFFFF, flags,
		GDT_ACCESS_PRESENT				|
		GDT_ACCESS_PRIVILEGE(privilege) |
		GDT_ACCESS_DESCRIPTOR			|
		GDT_ACCESS_READ_WRITE);
}

GDT_Entry GDT_create_task_segment_selector(Task_State_Structure* tss, uint8_t privilege)
{
	return GDT_create_entry(tss, sizeof(Task_State_Structure), GDT_FLAGS_32_BITS_SELECTOR,
		GDT_ACCESS_PRESENT				|
		GDT_ACCESS_PRIVILEGE(privilege) |
		GDT_ACCESS_CODE_SELECTOR		|
		GDT_ACCESS_READ_WRITE);
}