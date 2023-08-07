#include "idt.h"

extern void main() {
    setupIdt();

    return;
}