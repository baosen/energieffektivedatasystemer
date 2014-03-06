#include "timer1.h"
#include "gpio.h"
#include "nvic.h"
#include "led.h"
#include "dac.h"
#include "prs.h"
#include "interrupt_handlers.h"
#include "sound.h"

#include "efm32gg.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/* 
    TODO: calculate the appropriate sample period for the sound wave(s) 
    you want to generate. 
*/


/* Call the peripheral setup functions */
static void setup_peripheral(void)
{
    setup_gpio();
    setup_sound();
    //setup_prs();
    setup_nvic(); 
}

/*
static void wait_for_interrupt()  // Go to deep sleep. Does not work :(.
{
    *SCR = 6;       // Make device go into deep sleep mode.
    __asm__("wfi"); // Wait for interrupt in asm.
}*/

int main(void) 
{ 
    setup_peripheral();
    turn_off_all_leds();

    /* TODO for higher energy efficiency, sleep while waiting for interrupts
        instead of infinite loop for busy-waiting. */
    return EXIT_SUCCESS;
}
