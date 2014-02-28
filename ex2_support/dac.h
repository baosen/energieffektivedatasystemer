#ifndef DAC_H_INCLUDED
#define DAC_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

void setup_dac();
void write_data_to_dac0_ch0data(int data_to_write); // TODO: Add 12 bit typecheck for simplicity. Is it signed or unsigned?
void write_data_to_dac0_ch1data(int data_to_write); // TODO: Add 12 bit typecheck for simplicity. Is it signed or unsigned?

#endif
