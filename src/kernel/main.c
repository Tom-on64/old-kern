#include "screen.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "timer.h"
#include "keyboard.h"

void main() {
    clear(0x00);
    print("kern.\n\n", 0x0f);
    setupIdt();
    setupIsrs();
    setupIrqs();
    asm volatile("sti");

    setupTimer();
    setupKeyboard();

    changeCursor('_', 0x07);

    while(1) {
        print("> ", 0x0e);
        char* userInput = read('\n');
        print(userInput, 0x0b);
    }
}
