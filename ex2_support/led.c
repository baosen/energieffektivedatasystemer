#ifndef LED_C_INCLUDED_29839283
#define LED_C_INCLUDED_29839283

#include "efm32gg.h"

// The structure for controlling the LEDs. 
// Using a bitfield simplifies enabling/disabling each LED and you also get typechecking.
typedef struct {
    unsigned int    : 8;
    unsigned int d1 : 1;
    unsigned int d2 : 1;
    unsigned int d3 : 1;
    unsigned int d4 : 1;
    unsigned int d5 : 1;
    unsigned int d6 : 1;
    unsigned int d7 : 1;
    unsigned int d8 : 1;
    unsigned int    : 16;
} leds;

// The state of an LED.
typedef enum {
    ON  = 0, // The LED is lit.
    OFF = 1 // The LED is not lit.
} led_state;

#define PTR_TO_LEDS ((volatile leds*)(GPIO_PA_BASE + 0x0c))

// Turn off LEDs D4-D8 (LEDs are active low). Also makes sure the bits in GPIO_PA_DOUT is kept by using an OR mask.
void turn_off_all_leds() { *GPIO_PA_DOUT |= 0xFF00; }
// Turn on LEDs D4-D8 (LEDs are active low). Also makes sure the bits in GPIO_PA_DOUT is kept by using an AND mask.
void turn_on_all_leds() { *GPIO_PA_DOUT &= 0x00FF; }

// Turn a led off and on by setting its state.
void set_d1_led_state(led_state led_state) { PTR_TO_LEDS->d1 = led_state; }
void set_d2_led_state(led_state led_state) { PTR_TO_LEDS->d2 = led_state; }
void set_d3_led_state(led_state led_state) { PTR_TO_LEDS->d3 = led_state; } 
void set_d4_led_state(led_state led_state) { PTR_TO_LEDS->d4 = led_state; }
void set_d5_led_state(led_state led_state) { PTR_TO_LEDS->d5 = led_state; }
void set_d6_led_state(led_state led_state) { PTR_TO_LEDS->d6 = led_state; }
void set_d7_led_state(led_state led_state) { PTR_TO_LEDS->d7 = led_state; }
void set_d8_led_state(led_state led_state) { PTR_TO_LEDS->d8 = led_state; }

#endif
