#include "screen.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "timer.h"
#include "keyboard.h"
#include "system.h"

void main() {
    clear(0x00);
    // print("kern.\n", 0x0f);
    // kern. ascii art
    print("\xdb\n", 0x0f);
    print("\xdb\n", 0x0f);
    print("\xdb  \xdb   \xdb\xdb   \xdb \xdb\xdb   \xdb \xdb\xdb\n", 0x0f);
    print("\xdb \xdb   \xdb  \xdb  \xdb\xdb  \xdb  \xdb\xdb  \xdb\n", 0x0f);
    print("\xdb\xdb    \xdb\xdb\xdb\xdb  \xdb      \xdb   \xdb\n", 0x0f);
    print("\xdb \xdb   \xdb     \xdb      \xdb   \xdb\n", 0x0f);
    print("\xdb  \xdb   \xdb\xdb\xdb  \xdb      \xdb   \xdb  \xdb\n\n", 0x0f);
    print("(c) 2023 - 2023 Tom-on\n\n", 0x07);
    setupIdt();
    setupIsrs();
    setupIrqs();
    asm volatile("sti");

    setupTimer();
    setupKeyboard();

    changeCursor('_', 0x07);

    while(1) {
        print("> ", 0x0e);
        char* userInput = read('\n', 0x0f);
        print(userInput, 0x0b);
    }
}
