#ifndef INTERRUPT_HANDLERS_C_INCLUDED_908928323
#define INTERRUPT_HANDLERS_C_INCLUDED_908928323

#include <stdint.h>
#include <stdbool.h>

#include <math.h>
#define PI 3.14159265

#include "efm32gg.h"

static int counter = 0;
static int asd = 0;

void generateSinusSoundWave(int amplitude) 
{
    if (asd >= 2 * PI) { // to make sure the int does not overflow.
        asd = 0;
    }

    *DAC0_CH0DATA = amplitude * sin(asd);
    *DAC0_CH1DATA = amplitude * sin(asd);

    asd++;
}

void generateSawtoothWave() // makes my ears bleed.
{
	asd += 1000;
	if (asd > 3830){
		asd = 0;
	}
	*DAC0_CH0DATA = asd;	
	*DAC0_CH1DATA = asd;	
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
    generateSinusSoundWave(10000);
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
