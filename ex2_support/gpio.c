#ifndef GPIO_H_INCLUDED_92389283
#define GPIO_H_INCLUDED_92389283

#include "efm32gg.h"

#include <stdint.h>
#include <stdbool.h>

/* TODO set input and output pins for the joystick */
/* enable joystick/gamepad one the device for use */
static void enable_joystick(void)
{
    *GPIO_PC_MODEL  = 0x33333333;
    *GPIO_EXTIPSELL = 0x22222222;
    *GPIO_EXTIFALL  = 0xff;
    *GPIO_EXTIRISE  = 0xff;
    *GPIO_IEN       = 0xff;
	*GPIO_IFC       = 0xff;
}

// Enable GPIO clock to drive the GPIO outputs.
static void enable_gpio_clock() 
{ 
    *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO; 
}

// Enable GPIO output to output current to the LEDs.
static void enable_gpio_outputs()
{
    *GPIO_PA_CTRL = 2;                         /* set high drive strength */
    *GPIO_PA_MODEH = 0x55555555;               /* set pins A8-15 as output */
}

// Function to set up GPIO mode and interrupts.
void setup_gpio()
{
    enable_gpio_clock();
    enable_gpio_outputs();
    enable_joystick();
}

#endif
