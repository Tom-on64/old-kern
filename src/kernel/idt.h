#ifndef IDT_H
#define IDT_H

#include "stdint.h"

void idtSetGate(uint8_t index, uint32_t base, uint16_t sel, uint8_t typeAttr);
void setupIdt();

#endif
