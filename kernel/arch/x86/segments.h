#ifndef __SEGMENTS_H__
#define __SEGMENTS_H__

#define KERNEL_CODE_SEGMENT 0x08
#define KERNEL_DATA_SEGMENT 0x10

#include "multiboot.h"

void segments_init(Multiboot_Info* info);

#endif
