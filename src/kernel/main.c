#include "screen.h"
#include "idt.h"

void main() {
    clear(0x00);
    print("kern.\n\n", 0x0f);
    print("Booting...\n", 0x0f);
    setupIdt();
    print("\nDone!\n", 0x0f);

    int i = 99999999;
    while (i != 0) i--;
    print("\ntest", 0x0f);

    return;
}
