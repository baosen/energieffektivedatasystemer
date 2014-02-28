#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

void setup_sound();
void generate_sawtooth_samples(int frequency, int volume);
void generate_square_samples(int frequency, int volume);
void generate_sinus_samples(int frequency, int volume);

#endif
