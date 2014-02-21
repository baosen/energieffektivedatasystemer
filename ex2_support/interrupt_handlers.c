#ifndef INTERRUPT_HANDLERS_C_INCLUDED_908928323
#define INTERRUPT_HANDLERS_C_INCLUDED_908928323

#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
static int counter = 0;
static int asd = 0;

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
  /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
  */  
	*TIMER1_IFC =1;
	asd += 10;
	if(asd > 3830){
		asd = 0;
	}
	
	*DAC0_CH0DATA = asd;	
	*DAC0_CH1DATA = asd;	
	
	counter++;
	if (counter == 10000){
		counter = 0;
		*GPIO_PA_DOUT = ~*GPIO_PA_DOUT;
	}
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
