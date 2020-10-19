#include "typedef.h"

#include "kernel/idt.h"
#include "kernel/interrupt.h"
#include "kernel/multiboot.h"
#include "kernel/serial.h"

#define NB_IDT_ENTRIES 256

static IDT_Descriptor descriptor;
static IDT_Entry entries[NB_IDT_ENTRIES];

void interrupt_init();

void main(Multiboot_Info* info, u32 magic)
{
	serial_init();
	interrupt_init();
	/*
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
	*/

	asm("sti");
	while(true);
}

void interrupt_init()
{
	int i;

	for(i = 0; i < NB_IDT_ENTRIES; i++)
		entries[i] = IDT_create_entry(0, 0, 0);

	entries[0] = IDT_create_entry(0x08, (u32) irq0_handler, 0x8E);
	entries[1] = IDT_create_entry(0x08, (u32) irq1_handler, 0x8E);
	entries[2] = IDT_create_entry(0x08, (u32) irq2_handler, 0x8E);
	entries[3] = IDT_create_entry(0x08, (u32) irq3_handler, 0x8E);
	entries[4] = IDT_create_entry(0x08, (u32) irq4_handler, 0x8E);
	entries[5] = IDT_create_entry(0x08, (u32) irq5_handler, 0x8E);
	entries[6] = IDT_create_entry(0x08, (u32) irq6_handler, 0x8E);
	entries[7] = IDT_create_entry(0x08, (u32) irq7_handler, 0x8E);
	entries[8] = IDT_create_entry(0x08, (u32) irq8_handler, 0x8E);
	entries[9] = IDT_create_entry(0x08, (u32) irq9_handler, 0x8E);

	entries[10] = IDT_create_entry(0x08, (u32) irq10_handler, 0x8E);
	entries[11] = IDT_create_entry(0x08, (u32) irq11_handler, 0x8E);
	entries[12] = IDT_create_entry(0x08, (u32) irq12_handler, 0x8E);
	entries[13] = IDT_create_entry(0x08, (u32) irq13_handler, 0x8E);
	entries[14] = IDT_create_entry(0x08, (u32) irq14_handler, 0x8E);
	entries[15] = IDT_create_entry(0x08, (u32) irq15_handler, 0x8E);
	entries[16] = IDT_create_entry(0x08, (u32) irq16_handler, 0x8E);
	entries[17] = IDT_create_entry(0x08, (u32) irq17_handler, 0x8E);
	entries[18] = IDT_create_entry(0x08, (u32) irq18_handler, 0x8E);
	entries[19] = IDT_create_entry(0x08, (u32) irq19_handler, 0x8E);

	entries[20] = IDT_create_entry(0x08, (u32) irq20_handler, 0x8E);
	entries[21] = IDT_create_entry(0x08, (u32) irq21_handler, 0x8E);
	entries[22] = IDT_create_entry(0x08, (u32) irq22_handler, 0x8E);
	entries[23] = IDT_create_entry(0x08, (u32) irq23_handler, 0x8E);
	entries[24] = IDT_create_entry(0x08, (u32) irq24_handler, 0x8E);
	entries[25] = IDT_create_entry(0x08, (u32) irq25_handler, 0x8E);
	entries[26] = IDT_create_entry(0x08, (u32) irq26_handler, 0x8E);
	entries[27] = IDT_create_entry(0x08, (u32) irq27_handler, 0x8E);
	entries[28] = IDT_create_entry(0x08, (u32) irq28_handler, 0x8E);
	entries[29] = IDT_create_entry(0x08, (u32) irq29_handler, 0x8E);

	entries[30] = IDT_create_entry(0x08, (u32) irq30_handler, 0x8E);
	entries[31] = IDT_create_entry(0x08, (u32) irq31_handler, 0x8E);
	entries[32] = IDT_create_entry(0x08, (u32) irq32_handler, 0x8E);

	descriptor.address = &entries[0];
	descriptor.size = NB_IDT_ENTRIES * sizeof(IDT_Entry);

	asm volatile("lidt (%0)" : : "r" (&descriptor));
}