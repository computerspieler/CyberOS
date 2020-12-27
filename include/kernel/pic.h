#ifndef _PIC_H_
#define _PIC_H_

#include <stddef.h>

#define MASTER_PIC_COMMAND 0x20
#define MASTER_PIC_DATA 0x21

#define SLAVE_PIC_COMMAND 0x20
#define SLAVE_PIC_DATA 0x21

#define PIC_COMMAND_EOI 0x20

#define ICW1_ICW4 0x01
#define ICW1_SINGLE 0x02
#define ICW1_INTERVAL4 0x04
#define ICW1_LEVEL 0x08
#define ICW1_INIT 0x10

#define ICW4_8086 0x01
#define ICW4_AUTO 0x02
#define ICW4_BUF8SLAVE 0x08
#define ICW4_BUF_MASTER 0x0C
#define ICW4_SFNM 0x10

#define MASTER_PIC_OFFSET 0x20
#define SLAVE_PIC_OFFSET 0x28

void PIC_init();
void PIC_send_EOI(bool to_master, bool to_slave);

#endif
