#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#define DEFAULT_VOLUME_VALUE 0

void setup_sound();
void set_volume(int volume);
void generate_sawtooth_samples(int frequency);
void generate_square_samples(int frequency);

#endif
