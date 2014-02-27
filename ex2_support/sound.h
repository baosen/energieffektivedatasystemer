#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#define DEFAULT_VOLUME_VALUE 1

void generate_sawtooth_tone(int frequency);
void set_volume(int volume);
void generate_note(int volume, int freq);
#endif
