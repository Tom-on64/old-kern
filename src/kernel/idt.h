#include "stdint.h"

struct idtEntry {
    uint16_t offsetLow;
    uint16_t selector;
    uint8_t zero;
    uint8_t typeAttr;
    uint16_t offsetHigh;
} __attribute__((packed));

void exceptionHandler(uint8_t errCode);
void addEntry(uint8_t index, uint32_t offset, uint16_t selector, uint8_t typeAttr);
void setupIdt();
