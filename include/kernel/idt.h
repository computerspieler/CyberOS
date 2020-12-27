#ifndef _IDT_H_
#define _IDT_H_

#include <stddef.h>

#define NB_IDT_ENTRIES 256

typedef struct IDT_Entry IDT_Entry;
typedef struct IDT_Descriptor IDT_Descriptor;

struct IDT_Entry
{
	uint16_t offset_low;
	uint16_t selector;
	uint8_t empty;
	uint8_t flags;
	uint16_t offset_high;
} __attribute__ ((packed));

struct IDT_Descriptor
{
	uint16_t size;
	IDT_Entry* address;
} __attribute__ ((packed));

#define IDT_PUSH_DESCRIPTOR(descriptor) \
	asm volatile("lidt (%0)" : : "r" (descriptor))

IDT_Entry IDT_create_entry(uint16_t selector, uint32_t offset, uint8_t flags);

#endif