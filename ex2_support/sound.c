#include "sound.h"
#include "dac.h"

#include "efm32gg.h"

static int volume_ = DEFAULT_VOLUME_VALUE; 

void generate_sawtooth_tone(int frequency)
{
    for (int number = 0; number < frequency; number += 2) {
        write_data_to_dac0_ch0data(number * volume_);
    }
}
static int counter = 0;
void generate_note(int volume, int freq){
    
    counter ++;
    if(counter > 100000 / freq) counter = 0;
    write_data_to_dac0_ch0data((counter*100)/(100000/freq)*(400*volume)/100);

}

void set_volume(int volume) 
{
    volume_ = volume;
}
