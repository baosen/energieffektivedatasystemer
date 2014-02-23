#include "dac.h"

void setup_dac()
{
    // Enable and set up the Digital-Analog Converter.
    *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_DAC0;    // 1. Enable the DAC clock by setting bit 17 in CMU_HFPERCLKEN0.
    //*DAC0_CTRL = 0x50010;                       // 2. Prescale DAC clock by writing 0x50010 to DAC0_CTRL.
    
    *DAC0_CTRL    = 0x50012;                      //  0000 0000 0000 0001 0010 8 + 4 + 2
    *DAC0_CH0CTRL = 0x05;                         // 3. Enable left and right audio channels by writing 1 to DAC0_CH0CTRL and DAC0_CH1CTRL.
    *DAC0_CH1CTRL = 0x05;                            
    
    // 4. Write a continuous stream of samples to the DAC data registers, DAC0_CH0DATA and DAC0_CH1DATA, for example from a timer interrupt.
}

