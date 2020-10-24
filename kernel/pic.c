#include "kernel/asm.h"
#include "kernel/pic.h"

void PIC_init()
{
	u8 mask_master = inb(MASTER_PIC_DATA);
	u8 mask_slave  = inb(SLAVE_PIC_DATA);

	outb(MASTER_PIC_DATA, ICW1_INIT | ICW1_ICW4);
	outb(SLAVE_PIC_DATA,  ICW1_INIT | ICW1_ICW4);

	outb(MASTER_PIC_DATA, MASTER_PIC_OFFSET);
	outb(SLAVE_PIC_DATA,  SLAVE_PIC_OFFSET);

	outb(MASTER_PIC_DATA, 4);
	outb(SLAVE_PIC_DATA,  2);

	outb(MASTER_PIC_DATA, ICW4_8086);
	outb(SLAVE_PIC_DATA,  ICW4_8086);

	outb(MASTER_PIC_DATA, mask_master);
	outb(SLAVE_PIC_DATA,  mask_slave);
}

void PIC_send_EOI(bool to_master, bool to_slave)
{
	if(to_slave)
		outb(SLAVE_PIC_COMMAND, PIC_COMMAND_EOI);

	if(to_master)
		outb(MASTER_PIC_COMMAND, PIC_COMMAND_EOI);
}
