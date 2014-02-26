#ifndef DAC_H_INCLUDED
#define DAC_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

void setup_dac();
void write_data_to_dac0_ch0data(unsigned int data_to_write);

#endif
