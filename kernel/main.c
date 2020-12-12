#include "typedef.h"

#include "kernel/idt.h"
#include "kernel/interrupt.h"
#include "kernel/multiboot.h"
#include "kernel/serial.h"

static IDT_Descriptor descriptor;
static IDT_Entry entries[NB_IDT_ENTRIES];

void interrupt_init();

void main(Multiboot_Info* info, u32 magic)
{
	serial_init();
	interrupt_init();

	serial_send_string(0, "Magic number: ");
	serial_send_value(0, 16, magic);

	serial_send_string(0, "\nFlags: ");
	serial_send_value(0, 2, info->flags);

	serial_send_string(0, "\n\nLow memory: ");
	serial_send_value(0, 16, info->mem_lower);
	serial_send_string(0, "\nHigh memory: ");
	serial_send_value(0, 16, info->mem_upper);

	serial_send_string(0, "\n\nMemory map : Address: ");
	serial_send_value(0, 16, info->mmap_address);
	serial_send_string(0, "; Length: ");
	serial_send_value(0, 16, info->mmap_length);
	serial_send_string(0, "\n");

	for(Multiboot_Memory_Map_Entry *entry = (Multiboot_Memory_Map_Entry*) info->mmap_address;
		entry < (info->mmap_address + info->mmap_length);
		entry = (Multiboot_Memory_Map_Entry*) ((u32)entry + entry->size + sizeof(entry->size)))
	{
		serial_send_string(0, "\nMemory entry: Address: ");
		serial_send_value(0, 16, entry->address_high);
		serial_send_value(0, 16, entry->address_low);
		serial_send_string(0, "; Length: ");
		serial_send_value(0, 10, entry->length);
		serial_send_string(0, "; Type: ");
		serial_send_value(0, 16, entry->type);
	}

	asm("sti");
	while(true);
}

void interrupt_init()
{
	extern u32* interrupt_table;
	extern u32 interrupt_table_size;

	int i;

	for(i = 0; i < interrupt_table_size / sizeof(u32); i++)
		entries[i] = IDT_create_entry(0x08, &interrupt_table[i], 0x8E);

	descriptor.address = entries;
	descriptor.size = NB_IDT_ENTRIES * sizeof(IDT_Entry);

	asm volatile("lidt (%0)" : : "r" (&descriptor));
}