ENTRY(start)

SECTIONS
{
	. = 1M;
	KERNEL_BASE_ADDRESS = .;
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.Multiboot_Header)
		*(.text)
	}

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
	KERNEL_PAGE_SIZE = (. - KERNEL_BASE_ADDRESS) / 4K;
}

