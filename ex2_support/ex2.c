#include "efm32gg.h" // given code.

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

// The .c files is included directly to help the compiler do hardcore super uber optimisation tricks (inlining, function unrolling etc...).
#include "gpio.c"
#include "nvic.c"
#include "timer.c"
#include "dac.c"
#include "interrupt_handlers.c"

/* 
    TODO: calculate the appropriate sample period for the sound wave(s) 
    you want to generate. 
*/

/* The waiting period between each interrupt in clock cycles */
#define CLOCK_SPEED 14000000 // The core clock (which the timer clock is derived from) runs at 14 MHz by default. */

//static const uint16_t SAMPLE_PERIOD = CLOCK_SPEED / (NOTE_E6 - 1); 
#define SAMPLING_RATE 44100

static const uint16_t SAMPLE_PERIOD = CLOCK_SPEED / (SAMPLING_RATE - 1); // Also remember that the timer counter registers are 16 bits. Data type has been set to uint16_t to let the compiler do type checking for me :).


void setupPeripheral(void)
{
    /* Call the peripheral setup functions */
    setupGPIO();
    setupDAC();
    //setupTimer(SAMPLE_PERIOD); 
    setupTimer(SAMPLE_PERIOD); 
    setupNVIC(); /* Enable interrupt handling */
}

void wait_for_interrupt()
{
    *SCR = 6; // deep sleep i think.
    __asm__("wfi"); // wait for interrupt in asm.
}

/* Your code will start executing here */
int main(void) 
{ 
    setupPeripheral();

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
