#ifndef IDT_H
#define IDT_H
#include "stdint.h"

// IDT array with 256 entries (adjust for the number of interrupts)
struct IDTEntry idt[256];

// Structure of an IDT entry
struct IDTEntry
{
    uint16_t offset_low;  // Low 16 bits of the offset
    uint16_t selector;    // 16 bit Selector
    uint8_t zero;         // This is alwazs a NULL byte
    uint8_t type_attr;    // 8 bit Flags
    uint16_t offset_high; // Hight 16 bits of the offset
};

// A list of exception messages
const char *exceptionMessages[] = {
    "Divide Error",
    "Debug Exception",
    "NMI Interrupt",
    "Breakpoint",
    "Overflow",
    "BOUND Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 FPU Floating-Point Error",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

// Adds an entry to the IDT
void addEntry(uint8_t index, uint32_t offset, uint16_t selector, uint8_t type_attr);

// Function to set up the IDT
void setupIdt();

#endif