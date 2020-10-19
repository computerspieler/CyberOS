#include "typedef.h"
#include "kernel/multiboot.h"
#include "kernel/serial.h"

void main(Multiboot_Header* header, u32 magic)
{
	serial_init();

	serial_send_string(0, "Hey !\n");
	serial_send_value(0, 16, 0x2F);

	while(true);
}