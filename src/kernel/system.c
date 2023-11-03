#include "system.h"
#include "stdbool.h"
#include "stdint.h"

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

char hexBuffer[4];

char* toHex(uint8_t num) { // 0b1111 1111
    char chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
    uint8_t lowBits = num >> 4;
    uint8_t highBits = num & 0x0f;

    hexBuffer[0] = chars[lowBits];
    hexBuffer[1] = chars[highBits];
    hexBuffer[2] = '\0';

    return hexBuffer;
}

char* strtok(char* str, char delimiter) {
    static char* next = NULL; 

    if (str != NULL) next = str;
    if (next == NULL || *next == '\0') return NULL;

    char* token = next;
    while (*next != '\0' && *next != delimiter) next++;
    if (*next != '\0') {
        *next = '\0'; 
        next++;
    }

    return token;
}

int strcmp(char* str1, char* str2) {
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}
