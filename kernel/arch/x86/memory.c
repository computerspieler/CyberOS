#include <stddef.h>

#include "memory.h"
#include "segments.h"
#include "serial.h"

extern uint32_t KERNEL_BASE_ADDRESS;
extern uint32_t KERNEL_PAGE_SIZE;

static uint32_t nb_pages_allocated = 0;

void memory_init()
{
	nb_pages_allocated = &KERNEL_PAGE_SIZE;
}

void* memory_find_available_page(Multiboot_Info* info)
{
	void* output = NULL;
	int nb_pages_skipped = 0;
	Multiboot_Memory_Map_Entry *entry;

	for(entry = (Multiboot_Memory_Map_Entry*) info->mmap_address;
		entry < (Multiboot_Memory_Map_Entry*)(info->mmap_address + info->mmap_length);
		entry = (Multiboot_Memory_Map_Entry*) ((uint32_t)entry + entry->size + sizeof(entry->size)))
	{
		if(entry->type != Available_Memory || entry->address < &KERNEL_BASE_ADDRESS)
			continue;

		if((entry->length / MEMORY_PAGE_SIZE) < nb_pages_allocated)
		{
			nb_pages_skipped += (entry->length / MEMORY_PAGE_SIZE);
			continue;
		}

		output = (nb_pages_allocated - nb_pages_skipped) * MEMORY_PAGE_SIZE + entry->address;
		nb_pages_allocated ++;
		break;	
	}

	// TODO: Add an exception handler
	return output;
}
