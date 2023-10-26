#include "lowend.h"

uint8_t inb(uint16_t port) {
    uint8_t result;
    asm volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void outb(uint16_t port, uint8_t value) {
    asm volatile("outb %0, %1" :: "a"(value), "Nd"(port));
}

void memoryCopy(char* src, char* dst, uint16_t amount) {
    for (int i = 0; i < amount; i++) *(dst + i) = *(src + i);
}
