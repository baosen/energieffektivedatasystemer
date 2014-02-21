#ifndef SOUND_H_INCLUDED_9839283
#define SOUND_H_INCLUDED_9839283

#include "efm32gg.h"

void generate_sound()
{
    for (int i = 0; i < 4096; i++) {
        *DAC0_CH0DATA = i;
    }
    for (int i = 2048; i > 0; i = i-2) {
        *DAC0_CH0DATA = i;
    }
}

#endif
