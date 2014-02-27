#ifndef LED_H_INCLUDED_29839283
#define LED_H_INCLUDED_29839283

#include "efm32gg.h"

// The state of an LED.
typedef enum {
    ON  = 0,    // The LED is lit.
    OFF = 1     // The LED is not lit.
} led_state;

// Turn off LEDs D4-D8 (LEDs are active low). Also makes sure the bits in GPIO_PA_DOUT is kept by using an OR mask.
void turn_off_all_leds();
// Turn on LEDs D4-D8 (LEDs are active low). Also makes sure the bits in GPIO_PA_DOUT is kept by using an AND mask.
void turn_on_all_leds();

// Turn a led off and on by setting its state.
void set_d1_led_state(led_state led_state);
void set_d2_led_state(led_state led_state);
void set_d3_led_state(led_state led_state); 
void set_d4_led_state(led_state led_state);
void set_d5_led_state(led_state led_state);
void set_d6_led_state(led_state led_state);
void set_d7_led_state(led_state led_state);
void set_d8_led_state(led_state led_state);

// Check if a LED is on or off.
int is_d1_on(); 
int is_d2_on();
int is_d3_on();
int is_d4_on();
int is_d5_on();
int is_d6_on();
int is_d7_on();
int is_d8_on();

#endif
