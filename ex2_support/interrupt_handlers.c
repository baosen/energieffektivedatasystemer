#ifndef INTERRUPT_HANDLERS_C_INCLUDED_908928323
#define INTERRUPT_HANDLERS_C_INCLUDED_908928323

#include <stdint.h>
#include <stdbool.h>

#include <math.h>
#define PI 3.14159265

#include "efm32gg.h"

#include "led.c"
#include "notes.c"

static int counter = 0;
static double increment = 0;

// TODO:  Er dette riktig? Nei, det er ikke. Tror ikke det er mulig å generere en sinus-kurve programmatisk pga for mye overhead.
void generate_sinus_sound_wave(int amplitude) 
{
    *DAC0_CH0DATA = amplitude * sin(increment);
    *DAC0_CH1DATA = amplitude * sin(increment);

    //increment += ((2 * PI) / (14000000 / 1046));
    increment += (2 * PI) / (44100 / NOTE_C6);

    if (increment >= 1) { // to make sure the int does not overflow.
        increment -= 1;
    }
}

void generate_sawtooth_sound_wave()
{
	increment += 1000;
	if (increment > 3830){
		increment = 0;
	}
	*DAC0_CH0DATA = increment;	
	*DAC0_CH1DATA = increment;	
}

void make_leds_blink()
{
	counter++;
	if (counter == 50000){
		counter = 0;
		//*GPIO_PA_DOUT = ~*GPIO_PA_DOUT;
        if (PTR_TO_LEDS->d1 == ON) {
            PTR_TO_LEDS->d1 = OFF;
        } else {
            PTR_TO_LEDS->d1 = ON;
        }
	}
}

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
  /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
  */  
	*TIMER1_IFC = 1; // Reset timers interrupt flag.

    //generate_sawtooth_sound_wave();
    //generate_sinus_sound_wave(1000);
    //make_leds_blink();
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()  // TODO: Fix this. Does not work.
{
    /* TODO handle button pressed event, remember to clear pending interrupt */
	//*GPIO_IFC = *GPIO_IF;
    //*GPIO_PA_DOUT <<= 1;
	*GPIO_IFC = 0xff;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()  // TODO: Fix this. Does not work.
{
    /* TODO handle button pressed event, remember to clear pending interrupt */
	//*GPIO_IFC = *GPIO_IF;
	*GPIO_IFC = 0xff;
    //*GPIO_PA_DOUT >>= 1;
}

#endif
