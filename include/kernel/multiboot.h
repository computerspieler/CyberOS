#ifndef _MULTIBOOT_H_
#define _MULTIBOOT_H_

#include "typedef.h"

typedef enum Multiboot_Memory_Map_Entry_Type Multiboot_Memory_Map_Entry_Type;

typedef struct Multiboot_Info Multiboot_Info;
typedef struct Multiboot_Memory_Map_Entry Multiboot_Memory_Map_Entry;
typedef struct Multiboot_ELF_Header_Table Multiboot_ELF_Header_Table;
typedef struct Multiboot_A_Out_Symbol_Table Multiboot_A_Out_Symbol_Table;

enum Multiboot_Memory_Map_Entry_Type
{
	Available_Memory		 = 1,
	Memory_Holding_ACPI_Data = 3,
	Memory_To_Preserve		 = 4,
	Defective_Memory		 = 5,
};

struct Multiboot_A_Out_Symbol_Table
{
	u32 tab_size;
	u32 string_size;
	u32 address;
	u32 reserved;
};

struct Multiboot_ELF_Header_Table
{
	u32 num;
	u32 size;
	u32 address;
	u32 shndx;
};

struct Multiboot_Memory_Map_Entry
{
	u32 size;
	u32 address_high;
	u32 address_low;
	u64 length;
	u32 type;
} __attribute__((packed));

struct Multiboot_Info
{
	u32 flags;

	u32 mem_lower;
	u32 mem_upper;

	u32 boot_device;

	u32 cmdline;

	u32 mods_count;
	u32 mods_address;

	union
	{
		Multiboot_A_Out_Symbol_Table aout_symbol;
		Multiboot_ELF_Header_Table elf_header;
	} table;

	u32 mmap_length;
	u32 mmap_address;
	
	u32 drives_length;
	u32 drives_address;

	u32 config_table;

	u32 boot_loader_name;

	u32 apm_table;
	
	u32 vbe_control_info;
	u32 vbe_mode_info;
	u16 vbe_mode;
	u16 vbe_interface_seg;
	u16 vbe_interface_off;
	u16 vbe_interface_length;

	u64 video_address;
	u32 video_pitch;
	u32 video_width;
	u32 video_height;
	u8 video_bpp;
	u8 video_type;
	union
	{
		struct
		{
			u32 framebuffer_palete_address;
			u32 framebuffer_palete_nb_colors;
		};

		struct
		{
			u8 framebuffer_red_field_position;
			u8 framebuffer_red_mask_size;
			u8 framebuffer_green_field_position;
			u8 framebuffer_green_mask_size;
			u8 framebuffer_blue_field_position;
			u8 framebuffer_blue_mask_size;
		};
	} video_color_info;
};

#endif