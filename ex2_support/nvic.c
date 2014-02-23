#include "nvic.h"

/* Enable interrupt handling */
void setup_nvic(void)
{
  /* TODO use the NVIC ISERx registers to enable handling of interrupt(s)
     remember two things are necessary for interrupt handling:
      - the peripheral must generate an interrupt signal
      - the NVIC must be configured to make the CPU handle the signal
     You will need TIMER1, GPIO odd and GPIO even interrupt handling for this
     assignment.
  */
	*ISER0 = 0x1802;
}
