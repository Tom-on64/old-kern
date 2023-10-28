#ifndef TIMER_H
#define TIMER_H

#include "stdint.h"

#define INPUTCLK 1193180

void timerPhase(uint32_t hz);
void setupTimer();
void sleep(int ticks);

#endif
