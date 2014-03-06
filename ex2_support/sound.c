#include "sound.h"
#include "dac.h"
#include "timer1.h"

#include "efm32gg.h"

#include "math.h"

// The number of samples played each seconds.
#define SAMPLING_RATE 44100

// The waiting period between each interrupt in clock cycles.
static const uint16_t SAMPLE_PERIOD = (TIMER1_CLOCK_SPEED / SAMPLING_RATE) - 1;

void setup_sound()
{
    setup_timer1(SAMPLE_PERIOD); 
    setup_dac();
}

static int triangle_function(int sample, int number_of_samples, int volume)
{
    (volume * sample) / 2;
}

static int sample_for_triangle = 0;
int generate_triangle_samples(int sample, int number_of_samples, int volume)
{
}

static int linear_function(int sample, int number_of_samples, int volume)
{
    return (volume * sample) / number_of_samples;
}

static int sample_for_sawtooth = 0;
void generate_sawtooth_samples(int frequency, int volume)
{
    int number_of_samples_to_generate = SAMPLING_RATE / frequency;

    if (sample_for_sawtooth <= number_of_samples_to_generate) {
        int data = linear_function(sample_for_sawtooth, number_of_samples_to_generate, volume);
        write_data_to_dac0_ch0data(data);
        write_data_to_dac0_ch1data(data);
    } else {
        sample_for_sawtooth = 0;
    }
    sample_for_sawtooth++;
}

static int square_function(int sample, int number_of_samples, int volume)
{
    if (sample < (number_of_samples / 2)) {
        return volume;
    } else {
        return 0;
    }
}

static int sample_for_square = 1;
void generate_square_samples(int frequency, int volume)
{
    int number_of_samples_to_generate = SAMPLING_RATE / frequency;

    if (sample_for_square <= number_of_samples_to_generate) {
        int data = square_function(sample_for_square, number_of_samples_to_generate, volume);
        write_data_to_dac0_ch0data(data);
        write_data_to_dac0_ch1data(data);
    } else {
        sample_for_square = 1;
    }
    sample_for_square++;
}

#define MAXIMUM_NUMBER_OF_SAMPLES 256
static int sine_wave_table[MAXIMUM_NUMBER_OF_SAMPLES];

#define PI 3.14159265358979323846

// Generates a sinus wave table for a single wave.
void generate_sinus_wave_table(int number_of_samples, int volume) 
{
    double delta = (2 * PI) / number_of_samples;
    for (int sample = 0; sample < number_of_samples; sample++) {
        sine_wave_table[sample] = floor(volume + (volume * sin(sample * delta))); // Add volume to moved into the unsigned numbers.
    }
}

static int current_frequency = -1, // -1 is start frequency, just to make sample function generate a table the first it is called.
           current_volume = -1,    // same here.
           sample_for_sinus = 0;
void generate_sinus_samples(int frequency, int volume)
{
    int number_of_samples_to_generate = SAMPLING_RATE / frequency;

    // Check for change of frequency or volume. If yes, generate a new sinus wave table.
    if (current_frequency != frequency || current_volume != volume) { 
        generate_sinus_wave_table(number_of_samples_to_generate, volume); // because always generating sinus values is toooooo sloooooooow.
    }
    current_frequency = frequency;
    current_volume = volume;

    if (sample_for_sinus < number_of_samples_to_generate) {
        int data = sine_wave_table[sample_for_sinus];
        write_data_to_dac0_ch0data(data);
        write_data_to_dac0_ch1data(data);
    } else {
        sample_for_sinus = 0;
    }
    sample_for_sinus++;
}
