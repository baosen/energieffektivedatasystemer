#include "sound.h"
#include "dac.h"

#include "efm32gg.h"

static int volume_ = DEFAULT_VOLUME_VALUE; 

void generate_sawtooth_wave_sound()
{
    for (int number = 0; number < 2048; number++) {
        write_data_to_dac0_ch0data(number * volume_);
    }
}

void set_volume(int volume) 
{
    volume_ = volume;
}
