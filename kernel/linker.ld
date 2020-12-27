ENTRY(start)

SECTIONS
{
	. = 1M;
	KERNEL_CODE_START = .;
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.Multiboot_Header)
		*(.text)
	}
	KERNEL_CODE_END = .;

	KERNEL_DATA_START = .;
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
	KERNEL_DATA_END = .;
}