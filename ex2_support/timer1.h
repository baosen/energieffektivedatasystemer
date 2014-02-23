#ifndef TIMER1_C_INCLUDED_908129038901283901823
#define TIMER1_C_INCLUDED_908129038901283901823

#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

#define TIMER1_CLOCK_SPEED 14000000 // The core clock (which the timer clock is derived from) runs at 14 MHz by default.

void setup_timer1(uint16_t period);

#endif
