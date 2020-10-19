#include "kernel/asm.h"
#include "kernel/serial.h"
#include "math.h"
#include "typedef.h"

#define NB_SERIAL_PORTS 2
int serial_io_ports[] = {
	[0] = 0x3F8,
	[1] = 0x2F8,
};

void serial_init()
{
	int i;
	u16 divisor = 3;
	for(i = 0; i < NB_SERIAL_PORTS; i++) {
		outb(serial_io_ports[i] + 1, 0x00);
		outb(serial_io_ports[i] + 3, 0x80);

		outb(serial_io_ports[i] + 0, (divisor >> 0 & 0xFF));
		outb(serial_io_ports[i] + 1, (divisor >> 8 & 0xFF));

		outb(serial_io_ports[i] + 3, 0x03);
		outb(serial_io_ports[i] + 2, 0xC7);
		outb(serial_io_ports[i] + 4, 0x0B);
	}
}

void serial_send_value(int port, int base, int value)
{
	int value_backup;
	int nb_characters;
	char number_to_print;

	value_backup = value;
	do {
		nb_characters ++;
		value /= base;
	} while(value != 0);

	value = value_backup;

	while(nb_characters > 0) {
		nb_characters --;
		number_to_print = value / pow(base, nb_characters) % base;

		serial_send_char(port, number_to_print + (number_to_print < 10 ? '0' : 'A' - 10));
	}
}

void serial_send_string(int port, char* str)
{
	while(*str != '\0') {
		serial_send_char(port, *str);
		str ++;
	}
}

void serial_send_char(int port, char c)
{
	if(port >= NB_SERIAL_PORTS || port < 0)
		return;
	
	outb(serial_io_ports[port], c);
}