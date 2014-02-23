#include "prs.h"

void setup_prs()
{
    // Enable PRS.
    // 0001 1101 0000 0000 0000 0000
    *PRS_CH0_CTRL = 0x1C0000;
}
