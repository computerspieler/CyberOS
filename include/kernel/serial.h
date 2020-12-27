#ifndef _SERIAL_H_
#define _SERIAL_H_

void serial_init();
void serial_send_value (uint8_t base, uint32_t value);
void serial_send_string (char* str);
void serial_send_char (char c);

#endif