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
	Reserved_Memory			 = 2,
	Memory_Holding_ACPI_Data = 3,
	Memory_To_Preserve		 = 4,
	Defective_Memory		 = 5,
};

struct Multiboot_A_Out_Symbol_Table
{
	uint32_t tab_size;
	uint32_t string_size;
	uint32_t address;
	uint32_t reserved;
};

struct Multiboot_ELF_Header_Table
{
	uint32_t num;
	uint32_t size;
	uint32_t address;
	uint32_t shndx;
};

struct Multiboot_Memory_Map_Entry
{
	uint32_t size;
	uint64_t address;
	uint64_t length;
	Multiboot_Memory_Map_Entry_Type type: 32;
} __attribute__((packed));

struct Multiboot_Info
{
	uint32_t flags;

	uint32_t mem_lower;
	uint32_t mem_upper;

	uint32_t boot_device;

	uint32_t cmdline;

	uint32_t mods_count;
	uint32_t mods_address;

	union
	{
		Multiboot_A_Out_Symbol_Table aout_symbol;
		Multiboot_ELF_Header_Table elf_header;
	} table;

	uint32_t mmap_length;
	uint32_t mmap_address;
	
	uint32_t drives_length;
	uint32_t drives_address;

	uint32_t config_table;

	uint32_t boot_loader_name;

	uint32_t apm_table;
	
	uint32_t vbe_control_info;
	uint32_t vbe_mode_info;
	uint16_t vbe_mode;
	uint16_t vbe_interface_seg;
	uint16_t vbe_interface_off;
	uint16_t vbe_interface_length;

	uint64_t video_address;
	uint32_t video_pitch;
	uint32_t video_width;
	uint32_t video_height;
	uint8_t video_bpp;
	uint8_t video_type;
	union
	{
		struct
		{
			uint32_t framebuffer_palete_address;
			uint32_t framebuffer_palete_nb_colors;
		};

		struct
		{
			uint8_t framebuffer_red_field_position;
			uint8_t framebuffer_red_mask_size;
			uint8_t framebuffer_green_field_position;
			uint8_t framebuffer_green_mask_size;
			uint8_t framebuffer_blue_field_position;
			uint8_t framebuffer_blue_mask_size;
		};
	} video_color_info;
};

#endif