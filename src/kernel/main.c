#include "screen.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "timer.h"

void main() {
    clear(0x00);
    print("kern.\n\n", 0x0f);
    setupIdt();
    setupIsrs();
    setupIrqs();
    asm volatile("sti");

    setupTimer();

    while(1);
}
