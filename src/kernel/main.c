#include "screen.h"
#include "idt.h"
#include "isrs.h"

void main() {
    clear(0x00);
    print("kern.\n\n", 0x0f);
    setupIdt();
    setupIsrs();

    while(1);
}
