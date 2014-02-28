#include "sound.h"
#include "dac.h"
#include "timer1.h"

#include "efm32gg.h"

#include "math.h"

// The number of samples played each seconds.
#define SAMPLING_RATE 44100

// The waiting period between each interrupt in clock cycles.
static const uint16_t SAMPLE_PERIOD = TIMER1_CLOCK_SPEED / (SAMPLING_RATE - 1);

static int volume_ = DEFAULT_VOLUME_VALUE; 

void setup_sound()
{
    setup_timer1(SAMPLE_PERIOD); 
    setup_dac();
}

int linear_function(int x, int frequency)
{
    return (volume_ / frequency) * x;
}

static int sample_for_sawtooth = 0;

void generate_sawtooth_samples(int frequency)
{
    int number_of_samples_to_generate = SAMPLING_RATE / frequency;
    if (sample_for_sawtooth < number_of_samples_to_generate) {
        write_data_to_dac0_ch0data(sample_for_sawtooth * linear_function(sample_for_sawtooth, frequency));
    } else {
        sample_for_sawtooth = 0;
    }
    sample_for_sawtooth++;
}

int square_function(int x, int frequency)
{
    if (x < (SAMPLING_RATE / (frequency * 2))) {
        return volume_;
    } else {
        return 0;
    }
}

static int sample_for_square = 0;

void generate_square_samples(int frequency)
{
    int number_of_samples_to_generate = SAMPLING_RATE / frequency;
    if (sample_for_square < number_of_samples_to_generate) {
        write_data_to_dac0_ch0data(sample_for_square * square_function(sample_for_square, frequency));
    } else {
        sample_for_square = 0;
    }
    sample_for_square++;
}

void set_volume(int volume) 
{
    volume_ = volume;
}
