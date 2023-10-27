#include "stdint.h"
#include "idt.h"
#include "screen.h"

char* exceptionMessages[] = {
    "Divide By Zero Error",
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

struct idtEntry idt[256];

void exc0() { exceptionHandler(0); }
void exc1() { exceptionHandler(1); }
void exc2() { exceptionHandler(2); }
void exc3() { exceptionHandler(3); }
void exc4() { exceptionHandler(4); }
void exc5() { exceptionHandler(5); }
void exc6() { exceptionHandler(6); }
void exc7() { exceptionHandler(7); }
void exc8() { exceptionHandler(8); }
void exc9() { exceptionHandler(9); }
void exc10() { exceptionHandler(10); }
void exc11() { exceptionHandler(11); }
void exc12() { exceptionHandler(12); }
void exc13() { exceptionHandler(13); }
void exc14() { exceptionHandler(14); }
void exc15() { exceptionHandler(15); }
void exc16() { exceptionHandler(16); }
void exc17() { exceptionHandler(17); }
void exc18() { exceptionHandler(18); }
void exc19() { exceptionHandler(19); }
void exc20() { exceptionHandler(20); }
void exc21() { exceptionHandler(21); }
void exc22() { exceptionHandler(22); }
void exc23() { exceptionHandler(23); }
void exc24() { exceptionHandler(24); }
void exc25() { exceptionHandler(25); }
void exc26() { exceptionHandler(26); }
void exc27() { exceptionHandler(27); }
void exc28() { exceptionHandler(28); }
void exc29() { exceptionHandler(29); }
void exc30() { exceptionHandler(30); }
void exc31() { exceptionHandler(31); }

void addEntry(uint8_t index, uint32_t offset, uint16_t selector, uint8_t typeAttr) {
    idt[index].offsetLow = (uint16_t)offset;
    idt[index].selector = selector;
    idt[index].zero = 0;
    idt[index].typeAttr = typeAttr;
    idt[index].offsetHigh = (uint16_t)(offset >> 16);
}

void exceptionHandler(uint8_t errCode) {
    char* message;
    if (errCode < sizeof(exceptionMessages) / sizeof(exceptionMessages[0])) message = exceptionMessages[errCode];
    else message = "Unknown Exception";
    
    print(message, 0x04);

    // while (1); // halt
}

void setupIdt() {
    addEntry(0, (uint32_t)&exc0, 0x08, 0x8E);
    addEntry(1, (uint32_t)&exc1, 0x08, 0x8E);
    addEntry(2, (uint32_t)&exc2, 0x08, 0x8E);
    addEntry(3, (uint32_t)&exc3, 0x08, 0x8E);
    addEntry(4, (uint32_t)&exc4, 0x08, 0x8E);
    addEntry(5, (uint32_t)&exc5, 0x08, 0x8E);
    addEntry(6, (uint32_t)&exc6, 0x08, 0x8E);
    addEntry(7, (uint32_t)&exc7, 0x08, 0x8E);
    addEntry(8, (uint32_t)&exc8, 0x08, 0x8E);
    addEntry(9, (uint32_t)&exc9, 0x08, 0x8E);
    addEntry(10, (uint32_t)&exc10, 0x08, 0x8E);
    addEntry(11, (uint32_t)&exc11, 0x08, 0x8E);
    addEntry(12, (uint32_t)&exc12, 0x08, 0x8E);
    addEntry(13, (uint32_t)&exc13, 0x08, 0x8E);
    addEntry(14, (uint32_t)&exc14, 0x08, 0x8E);
    addEntry(15, (uint32_t)&exc15, 0x08, 0x8E);
    addEntry(16, (uint32_t)&exc16, 0x08, 0x8E);
    addEntry(17, (uint32_t)&exc17, 0x08, 0x8E);
    addEntry(18, (uint32_t)&exc18, 0x08, 0x8E);
    addEntry(19, (uint32_t)&exc19, 0x08, 0x8E);
    addEntry(20, (uint32_t)&exc20, 0x08, 0x8E);
    addEntry(21, (uint32_t)&exc21, 0x08, 0x8E);
    addEntry(22, (uint32_t)&exc22, 0x08, 0x8E);
    addEntry(23, (uint32_t)&exc23, 0x08, 0x8E);
    addEntry(24, (uint32_t)&exc24, 0x08, 0x8E);
    addEntry(25, (uint32_t)&exc25, 0x08, 0x8E);
    addEntry(26, (uint32_t)&exc26, 0x08, 0x8E);
    addEntry(27, (uint32_t)&exc27, 0x08, 0x8E);
    addEntry(28, (uint32_t)&exc28, 0x08, 0x8E);
    addEntry(29, (uint32_t)&exc29, 0x08, 0x8E);
    addEntry(30, (uint32_t)&exc30, 0x08, 0x8E);
    addEntry(31, (uint32_t)&exc31, 0x08, 0x8E);

    // Load IDT
    uint16_t idt_size = sizeof(idt) - 1;
    uint32_t idt_address = (uint32_t)&idt;
    asm volatile("lidt (%0)" ::"r"(&idt_size), "r"(idt_address));

    // Enable interrupts
    asm volatile("sti");

    print("Setup IDT\n", 0x0a);
}
