#include "idt.h"
#include "output.h"

extern void main() {
    setupVideo();
    setupIdt();

    puts("Hello, World!\n", 0b00001111);
    puts("Test\n", 0b00001111);

    return;
}
