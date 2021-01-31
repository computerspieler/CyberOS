.set HEADER_FLAG_PAGE_ALIGNED,	1 << 0
.set HEADER_FLAG_MEMORY_INFO,	1 << 1
.set HEADER_FLAG_VIDEO,			0 << 2

.set HEADER_MAGIC, 0x1BADB002
.set HEADER_FLAGS, HEADER_FLAG_PAGE_ALIGNED | HEADER_FLAG_MEMORY_INFO | HEADER_FLAG_VIDEO

.set HEADER_CHECKSUM, -(HEADER_MAGIC + HEADER_FLAGS)

.set STACK_SIZE, 16*1024		# 16 KiO

.set VIDEO_MODE_TYPE,	0
.set VIDEO_WIDTH,		1024
.set VIDEO_HEIGHT,		1080
.set VIDEO_DEPTH,		8

.section .Multiboot_Header
	.align 4
	.long HEADER_MAGIC
	.long HEADER_FLAGS
	.long HEADER_CHECKSUM

	.skip 4*5

	.long VIDEO_MODE_TYPE
	.long VIDEO_WIDTH
	.long VIDEO_HEIGHT
	.long VIDEO_DEPTH


.section .bss
.align 16
stack_bottom:
	.skip STACK_SIZE
stack_top:

.section .text
.global start
.type start, @function
start:
	mov $stack_top, %EBP
	mov %EBP, %ESP

	push %EAX
	push %EBX

	call kmain

# This part is just a security
	cli
the_end:
	hlt
	jmp the_end

.size start, . - start
