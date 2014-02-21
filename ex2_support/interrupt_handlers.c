#ifndef INTERRUPT_HANDLERS_C_INCLUDED_908928323
#define INTERRUPT_HANDLERS_C_INCLUDED_908928323

#include <stdint.h>
#include <stdbool.h>

#include <math.h>
#define PI 3.14159265

#include "efm32gg.h"

// Sound frequencies for different notes in the 6th octave. Use floating-point numbers or fixed-point?
enum {
    NOTE_C6   = 1046,
    NOTE_C6D6 = 1108,
    NOTE_D6   = 1174,
    NOTE_D6E6 = 1244,
    NOTE_E6   = 1318,
    NOTE_F6   = 1396,
    NOTE_F6G6 = 1479,
    NOTE_G6   = 1567,
    NOTE_G6A6 = 1661,
    NOTE_A6   = 1760,
    NOTE_A6B6 = 1864,
    NOTE_B6   = 1975
};

static int counter = 0;
double increment = 0;

// TODO:  Er dette riktig? Nei, det er ikke. Tror ikke det er mulig å generere en sinus-kurve programmatisk pga for mye overhead.
inline void generateSinusSoundWave(int amplitude) 
{
    *DAC0_CH0DATA = amplitude * sin(increment);
    *DAC0_CH1DATA = amplitude * sin(increment);

    //increment += ((2 * PI) / (14000000 / 1046));
    increment += (2 * PI) / (44100 / NOTE_C6);

    if (increment >= 1) { // to make sure the int does not overflow.
        increment -= 1;
    }
}

void generateSawtoothWave() // makes my ears bleed.
{
	increment += 1000;
	if (increment > 3830){
		increment = 0;
	}
	*DAC0_CH0DATA = increment;	
	*DAC0_CH1DATA = increment;	
}

void makeLEDsBlink()
{
	counter++;
	if (counter == 50000){
		counter = 0;
		*GPIO_PA_DOUT = ~*GPIO_PA_DOUT;
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

    //generateSawtoothWave();
    generateSinusSoundWave(1000);
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
    /* TODO handle button pressed event, remember to clear pending interrupt */
	*GPIO_IFC = 0xFF;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{
    /* TODO handle button pressed event, remember to clear pending interrupt */
	*GPIO_IFC = 0xFF;
}

#endif
