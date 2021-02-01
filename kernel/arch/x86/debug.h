#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "gdt.h"
#include "multiboot.h"

int debug_init();
int debug_print_multiboot(Multiboot_Info* info);
int debug_print_gdt(GDT_Descriptor* descriptor);

#endif