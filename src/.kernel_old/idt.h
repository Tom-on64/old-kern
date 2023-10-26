#ifndef IDT_H
#define IDT_H
#include "stdint.h"

// Structure of an IDT entry
struct IDTEntry {
    uint16_t offset_low;  // Low 16 bits of the offset
    uint16_t selector;    // 16 bit Selector
    uint8_t zero;         // This is alwazs a NULL byte
    uint8_t type_attr;    // 8 bit Flags
    uint16_t offset_high; // Hight 16 bits of the offset
};

// Adds an entry to the IDT
void addEntry(uint8_t index, uint32_t offset, uint16_t selector, uint8_t type_attr);

// Handles exceptions
void exceptionHandler(uint32_t errorCode);

// Function to set up the IDT
void setupIdt();

#endif