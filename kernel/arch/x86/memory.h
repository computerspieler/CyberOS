#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "multiboot.h"

#define MEMORY_PAGE_SIZE	4096

void memory_init();
void* memory_find_available_page(Multiboot_Info* info);

#endif
