#ifndef SYSTEM_H
#define SYSTEM_H

#include "stdint.h"
#include "stdbool.h"

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t data);
char* memoryCopy(char* src, char* dst, uint16_t amount);
char* memset(char* dst, uint8_t val, uint16_t amount);
char* toHex(uint8_t num);

struct regs {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int intNo, errCode;
    unsigned int eip, cs, eflags, useresp, ss;
};

#endif
