#ifndef GPIO_H_INCLUDED_92389283
#define GPIO_H_INCLUDED_92389283

#include "efm32gg.h"

#include <stdint.h>
#include <stdbool.h>

/* TODO set input and output pins for the joystick */
/* enable joystick/gamepad one the device for use */
void enableJoystick(void)
{
    *GPIO_PC_MODEL = 0x33333333;
    *GPIO_EXTIPSELL = 0x22222222;
    *GPIO_EXTIFALL = 0xff;
    *GPIO_EXTIRISE = 0xff;
    *GPIO_IEN = 0xff;
}

inline void turnOffAllLEDs() 
{
    *GPIO_PA_DOUT |= 0xFF00;  // Turn off LEDs D4-D8 (LEDs are active low). Also makes sure the bits in GPIO_PA_DOUT is kept by using an OR mask.
}

inline void turnOnAllLEDs()
{
    *GPIO_PA_DOUT &= 0x00FF;  // Turn on LEDs D4-D8 (LEDs are active low). Also makes sure the bits in GPIO_PA_DOUT is kept by using an AND mask.
}

/* function to set up GPIO mode and interrupts*/
void setupGPIO()
{
    /* Example of HW access from C code: turn on joystick LEDs D4-D8
       check efm32gg.h for other useful register definitions
    */
    *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO; /* enable GPIO clock*/
    *GPIO_PA_CTRL = 2;  /* set high drive strength */
    *GPIO_PA_MODEH = 0x55555555; /* set pins A8-15 as output */

    turnOnAllLEDs();
    turnOffAllLEDs();

    enableJoystick();
}

#endif
