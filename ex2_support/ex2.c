#include "efm32gg.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

// The .c files is included directly to help the compiler do hardcore super uber optimisation tricks (inlining, function unrolling etc...).
#include "nvic.c"
#include "gpio.c"
#include "led.c"
#include "timer1.c"
#include "dac.c"
#include "prs.c"
#include "interrupt_handlers.c"

/* 
    TODO: calculate the appropriate sample period for the sound wave(s) 
    you want to generate. 
*/

#define SAMPLING_RATE 44100        // The number of samples played each seconds.

//static const uint16_t SAMPLE_PERIOD = TIMER_CLOCK_SPEED / (NOTE_E6 - 1); 

/* The waiting period between each interrupt in clock cycles */
static const uint16_t SAMPLE_PERIOD = TIMER1_CLOCK_SPEED / (SAMPLING_RATE - 1); // Also remember that the timer counter registers are 16 bits. Data type has been set to uint16_t to let the compiler do type checking for me :).


/* Call the peripheral setup functions */
void setup_peripheral(void)
{
    setup_gpio();
    setup_dac();
    setup_timer1(SAMPLE_PERIOD); 
    setup_prs();
    setup_nvic(); 
}

// Not currently used.
void wait_for_interrupt()
{
    *SCR = 6; // deep sleep i think.
    __asm__("wfi"); // wait for interrupt in asm.
    // __WFI(); // The "official" way.
}

// Your code will start executing here.
int main(void) 
{ 
    setup_peripheral();

    turn_on_all_leds();
    turn_off_all_leds();

    set_d1_led_state(ON);
    set_d2_led_state(OFF);
    set_d3_led_state(OFF);
    set_d4_led_state(OFF);
    set_d5_led_state(OFF);

    /* TODO for higher energy efficiency, sleep while waiting for interrupts
        instead of infinite loop for busy-waiting. */
    return EXIT_SUCCESS;
}

/* if other interrupt handlers are needed, use the following names: 
   NMI_Handler
   HardFault_Handler
   MemManage_Handler
   BusFault_Handler
   UsageFault_Handler
   Reserved7_Handler
   Reserved8_Handler
   Reserved9_Handler
   Reserved10_Handler
   SVC_Handler
   DebugMon_Handler
   Reserved13_Handler
   PendSV_Handler
   SysTick_Handler
   DMA_IRQHandler
   GPIO_EVEN_IRQHandler
   TIMER0_IRQHandler
   USART0_RX_IRQHandler
   USART0_TX_IRQHandler
   USB_IRQHandler
   ACMP0_IRQHandler
   ADC0_IRQHandler
   DAC0_IRQHandler
   I2C0_IRQHandler
   I2C1_IRQHandler
   GPIO_ODD_IRQHandler
   TIMER1_IRQHandler
   TIMER2_IRQHandler
   TIMER3_IRQHandler
   USART1_RX_IRQHandler
   USART1_TX_IRQHandler
   LESENSE_IRQHandler
   USART2_RX_IRQHandler
   USART2_TX_IRQHandler
   UART0_RX_IRQHandler
   UART0_TX_IRQHandler
   UART1_RX_IRQHandler
   UART1_TX_IRQHandler
   LEUART0_IRQHandler
   LEUART1_IRQHandler
   LETIMER0_IRQHandler
   PCNT0_IRQHandler
   PCNT1_IRQHandler
   PCNT2_IRQHandler
   RTC_IRQHandler
   BURTC_IRQHandler
   CMU_IRQHandler
   VCMP_IRQHandler
   LCD_IRQHandler
   MSC_IRQHandler
   AES_IRQHandler
   EBI_IRQHandler
   EMU_IRQHandler
*/
