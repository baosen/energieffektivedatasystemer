#include "interrupt_handlers.h"
#include "notes.h"
#include "led.h"
#include "sound.h"


static int counter_2 = 0;
static int counter_3 = 0;
static bool lights_on = 0;
static int level = 1;
void dim_lights()
{
    counter_2++;
    if (counter_2 > 100) counter_2 = 0;
    if (counter_3 > 100){
        counter_3 = 0;
        level ++;
    }
    if (level >= 100) level = 1;
    if (counter_2 < level){
        if (lights_on){
            //do nothing
        }
        else {
            turn_on_all_leds();
            lights_on = 1;
            counter_3++;
        }
    }
    else {
        if (lights_on){
            turn_off_all_leds();
            lights_on = 0;
        }
        else {
            //do nothing
        }
    }

}

/*
static int counter = 0;
static int current_led = 0;
static int backwards = 0;

static void make_leds_blink()
{
	counter++;
	if (counter >= 1){
		counter = 0;
        switch (current_led % 8) {
        case 0:
            set_d8_led_state(OFF);
            set_d1_led_state(ON);
            set_d2_led_state(OFF);
            break;
        case 1:
            set_d1_led_state(OFF);
            set_d2_led_state(ON);
            set_d3_led_state(OFF);
            break;
        case 2:
            set_d2_led_state(OFF);
            set_d3_led_state(ON);
            set_d4_led_state(OFF);
            break;
        case 3:
            set_d3_led_state(OFF);
            set_d4_led_state(ON);
            set_d5_led_state(OFF);
            break;
        case 4:
            set_d4_led_state(OFF);
            set_d5_led_state(ON);
            set_d6_led_state(OFF);
            break;
        case 5:
            set_d5_led_state(OFF);
            set_d6_led_state(ON);
            set_d7_led_state(OFF);
            break;
        case 6:
            set_d6_led_state(OFF);
            set_d7_led_state(ON);
            set_d8_led_state(OFF);
            break;
        case 7:
            set_d7_led_state(OFF);
            set_d8_led_state(ON);
            set_d1_led_state(OFF);
            break;
        }
        if (current_led == 7) {
            backwards = 1;
        } else if (current_led == 0) {
            backwards = 0;
        }
        if (backwards) {
            current_led--;
        }
        else {
            current_led++;
        }
	}
}*/

   
/* TIMER0 interrupt handler */
void __attribute__ ((interrupt)) TIMER0_IRQHandler() 
{
}

static int note = NOTE_D4;
static int wave_choice = 2;
static int DEFAULT_VOLUME = 250;

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
    switch (wave_choice % 3) {
    case 0:
        generate_square_samples(note, DEFAULT_VOLUME);
        break;
    case 1:
        generate_sawtooth_samples(note, DEFAULT_VOLUME);
        break;
    case 2:
        generate_sinus_samples(note, DEFAULT_VOLUME);
        break;
    }

	*TIMER1_IFC = 1; // Reset timers interrupt flag.
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()  // TODO: Fix this. Does not work.
{
    wave_choice++;
	*GPIO_IFC = *GPIO_IF;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()  // TODO: Fix this. Does not work.
{
	*GPIO_IFC = *GPIO_IF;
}
