#ifndef _MULTIBOOT_H_
#define _MULTIBOOT_H_

#include "typedef.h"

typedef struct Multiboot_Header Multiboot_Header;
typedef struct Multiboot_VBE_Header Multiboot_VBE_Header;
typedef struct Multiboot_Video_Header Multiboot_Video_Header;

struct Multiboot_VBE_Header
{
	u32 control_info;
	u32 mode_info;
	u16 mode;
	u16 interface_seg;
	u16 interface_off;
	u16 interface_len;
};

struct Multiboot_Video_Header
{
	u64 addr;
	u32 pitch;
	u32 width;
	u32 height;
	u8 bpp;
	u8 type;
	u8 color_info[5];
};

struct Multiboot_Header
{
	u32 flags;

	u32 mem_lower;
	u32 mem_upper;

	u32 boot_device;

	u32 cmdline;

	u32 mods_count;
	u32 mods_addr;

	u8 syms[12];

	u32 mmap_length;
	u32 mmap_addr;
	
	u32 drives_length;
	u32 drives_addr;

	u32 config_table;

	u32 boot_loader_name;
	u32 apm_table;
	
	Multiboot_VBE_Header vbe;
	Multiboot_Video_Header video;
};

#endif