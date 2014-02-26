#include "prs.h"

enum {
    NONE = 0x0,
    VCMP = 0x1,
    TIMER0 = 28
};

enum {
    TIMER0_OVERFLOW = 0x1
};

enum {
    OFF = 0,
    POSITIVE_EDGE = 1,
    NEGATIVE_EDGE = 2,
    BOTH_EDGES = 3
};

typedef struct {
    unsigned int signal_select : 3;      // Select signal input to PRS channel.
    unsigned int : 13;                   // Reserved. Always write bits to 0.
    unsigned int source_select : 6;      // Select source input to PRS channel.
    unsigned int : 2;                    // Reserved. Always write bits to 0.
    unsigned int edge_detect_select : 2; // Detect edge???!?!??!
    unsigned int : 2;                    // Reserved. Always write bits to 0.
    unsigned int asynchronuous_reflex : 1;
    unsigned int : 3;                    // Reserved. Always write bits to 0.
} prs_control_bits;

#define PTR_TO_PRS_CH0_CTRL ((volatile prs_control_bits*)(PRS_BASE + 0x010))

static void enable_prs_clock()
{
    *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_PRS;
}

void setup_prs()
{
    enable_prs_clock();
    PTR_TO_PRS_CH0_CTRL->signal_select = TIMER0_OVERFLOW;
    PTR_TO_PRS_CH0_CTRL->source_select = TIMER0;
    PTR_TO_PRS_CH0_CTRL->edge_detect_select = OFF;
    PTR_TO_PRS_CH0_CTRL->asynchronuous_reflex = OFF;
}
