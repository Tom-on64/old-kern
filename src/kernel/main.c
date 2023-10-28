#include "screen.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"

void main() {
    clear(0x00);
    print("kern.\n\n", 0x0f);
    setupIdt();
    setupIsrs();
    setupIrqs();
    asm volatile("sti");

    print("Hello, World!", 0x0f);

    while(1);
}
