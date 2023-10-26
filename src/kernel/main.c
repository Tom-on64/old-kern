#include "idt.h"
#include "output.h"

extern void main()
{
    setupVideo();
    setupIdt();

    puts("Hello, World!", 0b00100100);

    return;
}
