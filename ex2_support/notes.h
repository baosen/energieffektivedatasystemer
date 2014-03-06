#ifndef NOTES_H_INCLUDED
#define NOTES_H_INCLUDED
//
// Tones for 4th octave.
enum {
    NOTE_C4 = 262,
    NOTE_CSHARP4_DFLAT4 = 277,
    NOTE_D4 = 294,
    NOTE_DSHARP4_EFLAT4 = 311,
    NOTE_E4 = 330,
    NOTE_F4 = 349,
    NOTE_FSHARP4_GFLAT4 = 370,
    NOTE_G4 = 392,
    NOTE_GSHARP4_AFLAT4 = 415,
    NOTE_A4 = 440,
    NOTE_ASHARP4_BSHARP6 = 466,
    NOTE_B4 = 494
};

// Sound frequencies for different notes in the 6th octave.
enum {
    NOTE_C6   = 1046,
    NOTE_C6D6 = 1108,
    NOTE_D6   = 1174,
    NOTE_D6E6 = 1244,
    NOTE_E6   = 1318,
    NOTE_F6   = 1396,
    NOTE_F6G6 = 1479,
    NOTE_G6   = 1567,
    NOTE_G6A6 = 1661,
    NOTE_A6   = 1760,
    NOTE_A6B6 = 1864,
    NOTE_B6   = 1975
};

const int number_of_notes = 12;

#endif
