#ifndef GPIO_H_INCLUDED_92389283
#define GPIO_H_INCLUDED_92389283

#include "efm32gg.h"

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    unsigned int sw1 : 1;
    unsigned int sw2 : 1;
    unsigned int sw3 : 1;
    unsigned int sw4 : 1;
    unsigned int sw5 : 1;
    unsigned int sw6 : 1;
    unsigned int sw7 : 1;
    unsigned int sw8 : 1;
} gamepad_bits;

enum {
    PUSHED = 0,
    NOT_PUSHED = 1
};

void setup_gpio();

#endif
