#ifndef _SERIAL_H_
#define _SERIAL_H_

void serial_init();
void serial_send_value  (int port, int base, int value);
void serial_send_string (int port, char* str);
void serial_send_char   (int port, char c);

#endif