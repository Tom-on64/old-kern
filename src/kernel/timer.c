#include "timer.h"
#include "stdint.h"
#include "system.h"
#include "screen.h"
#include "irq.h"

int timerTicks = 0;

void timerPhase(uint32_t hz) {
    uint16_t divisor = INPUTCLK / hz;
    outb(0x43, 0x36);
    outb(0x43, divisor & 0xff);
    outb(0x43, divisor >> 8);
}

void timerHandler(struct regs* r) { timerTicks++; }

void sleep(int ticks) {
    uint32_t eticks;

    eticks = timerTicks + ticks;
    while (timerTicks < eticks);
}

void setupTimer() { installIrqHandler(0, timerHandler); }
