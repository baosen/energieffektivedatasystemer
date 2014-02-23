#ifndef TIMER1_C_INCLUDED_908129038901283901823
#define TIMER1_C_INCLUDED_908129038901283901823

#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

#define TIMER1_CLOCK_SPEED 14000000 // The core clock (which the timer clock is derived from) runs at 14 MHz by default.

// Setup timer1.
void setup_timer1(uint16_t period)
{
   // Enable and set up the timer
   *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_TIMER1; // 1. Enable clock to timer by setting bit 6 in CMU_HFPERCLKEN0
   *TIMER1_TOP = period;                        // 2. Write the period to register TIMER1_TOP
   *TIMER1_IEN = 1;                             // 3. Enable timer interrupt generation by writing 1 to TIMER1_IEN
   *TIMER1_CMD = 1;                             // 4. Start the timer by writing 1 to TIMER1_CMD
   // This will cause a timer interrupt to be generated every (period) cycles. 
   // Remember to configure the NVIC as well, otherwise the interrupt handler will not be invoked.
}

#endif
