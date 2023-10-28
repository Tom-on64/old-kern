#include "idt.h"
#include "stdint.h"
#include "screen.h"
#include "lowend.h"

struct idtEntry {
    uint16_t offsetLow;
    uint16_t selector;
    uint8_t zero;
    uint8_t typeAttr;
    uint16_t offsetHigh;
} __attribute__((packed));

struct idtPtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct idtEntry idt[256];
struct idtPtr idtp;

extern void idtLoad();

void idtSetGate(uint8_t index, uint32_t base, uint16_t sel, uint8_t typeAttr) {
    idt[index].offsetLow = (uint16_t)base;
    idt[index].selector = sel;
    idt[index].zero = 0;
    idt[index].typeAttr = typeAttr;
    idt[index].offsetHigh = (uint16_t)(base >> 16);
}

void setupIdt() {
    idtp.limit = (sizeof(struct idtEntry) * 256);
    idtp.base = (uint32_t)&idt;

    memset((char*)&idt, 0, sizeof(struct idtEntry) * 256); // clear the idt
    idtLoad();
}
