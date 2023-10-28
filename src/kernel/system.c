#include "system.h"

uint8_t inb(uint16_t port) {
    uint8_t result;
    asm volatile("in %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void outb(uint16_t port, uint8_t value) {
    asm volatile("out %0, %1" :: "a"(value), "Nd"(port));
}

char* memoryCopy(char* src, char* dst, uint16_t amount) {
    for (int i = 0; i < amount; i++) *(dst + i) = *(src + i);
    return dst;
}

char* memset(char* dst, uint8_t val, uint16_t amount) {
    for (int i = 0; i < amount; i++) *(dst + i) = val;
    return dst;
}
