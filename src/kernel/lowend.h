#include "stdint.h"

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t data);
char* memoryCopy(char* src, char* dst, uint16_t amount);
char* memset(char* dst, uint8_t val, uint16_t amount);
