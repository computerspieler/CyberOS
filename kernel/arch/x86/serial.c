#include <stddef.h>

#include "kernel/asm.h"
#include "kernel/serial.h"

#define SERIAL_PORT 0x3F8

void serial_init()
{
	uint16_t divisor = 3;

	outb(SERIAL_PORT + 1, 0x00);
	outb(SERIAL_PORT + 3, 0x80);

	outb(SERIAL_PORT + 0, (divisor      & 0xFF));
	outb(SERIAL_PORT + 1, (divisor >> 8 & 0xFF));

	outb(SERIAL_PORT + 3, 0x03);
	outb(SERIAL_PORT + 2, 0xC7);
	outb(SERIAL_PORT + 4, 0x0B);
}

void serial_send_value(uint8_t base, uint32_t value)
{
	int nb_characters = 0;
	char number_to_print;
	long reversed_value = 0;

	do {
		nb_characters ++;
		reversed_value *= base;
		reversed_value += (value % base);
		value /= base;
	} while(value != 0);

	while(nb_characters > 0) {
		number_to_print = reversed_value % base;
		reversed_value /= base;

		serial_send_char(number_to_print + (number_to_print < 10 ? '0' : 'A' - 10));
		nb_characters --;
	}
}

void serial_send_string(char* str)
{
	while(*str != '\0') {
		serial_send_char(*str);
		str ++;
	}
}

void serial_send_char(char c)
{	
	while((inb(SERIAL_PORT + 5) & 0x20) == 0);

	outb(SERIAL_PORT, c);
}
