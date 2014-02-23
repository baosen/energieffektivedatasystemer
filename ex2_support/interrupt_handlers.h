#ifndef INTERRUPT_HANDLERS_H_INCLUDED_908928323
#define INTERRUPT_HANDLERS_H_INCLUDED_908928323

#include <stdint.h>
#include <stdbool.h>

#include <math.h>
#define PI 3.14159265

#include "efm32gg.h"

#include "led.h"

void __attribute__ ((interrupt)) TIMER1_IRQHandler();
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler();  // TODO: Fix this. Does not work.
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler();   // TODO: Fix this. Does not work.

#endif
