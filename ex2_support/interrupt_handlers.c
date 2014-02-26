#include "interrupt_handlers.h"
#include "notes.h"
#include "led.h"

/*
static int counter = 0;
static double increment = 0;

// TODO:  Er dette riktig? Nei, det er ikke. Tror ikke det er mulig å generere en sinus-kurve programmatisk pga for mye overhead.
static void generate_sinus_sound_wave(int amplitude) 
{
    *DAC0_CH0DATA = amplitude * sin(increment);
    *DAC0_CH1DATA = amplitude * sin(increment);

    increment += ((2 * PI) / (14000000 / 1046));

    if (increment >= 1) { // to make sure the int does not overflow.
        increment -= 1;
    }
}

static void generate_sawtooth_sound_wave()
{
	increment += 1000;
	if (increment > 3830){
		increment = 0;
	}
	*DAC0_CH0DATA = increment;	
	*DAC0_CH1DATA = increment;	
}

static void make_leds_blink()
{
	counter++;
	if (counter == 50000){
		counter = 0;
		*GPIO_PA_DOUT = ~*GPIO_PA_DOUT;
	}
}

*/

   
/* TIMER0 interrupt handler */
void __attribute__ ((interrupt)) TIMER0_IRQHandler() 
{
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
	*GPIO_IFC = *GPIO_IF;
    set_d1_led_state(ON);
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()  // TODO: Fix this. Does not work.
{
    /* TODO handle button pressed event, remember to clear pending interrupt */
	*GPIO_IFC = *GPIO_IF;
    set_d1_led_state(OFF);
}
