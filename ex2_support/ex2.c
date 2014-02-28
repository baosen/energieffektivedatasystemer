#include "timer1.h"
#include "gpio.h"
#include "nvic.h"
#include "led.h"
#include "dac.h"
#include "prs.h"
#include "interrupt_handlers.h"
#include "sound.h"

#include "efm32gg.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/* 
    TODO: calculate the appropriate sample period for the sound wave(s) 
    you want to generate. 
*/


/* Call the peripheral setup functions */
static void setup_peripheral(void)
{
    setup_gpio();
    setup_sound();
    //setup_prs();
    setup_nvic(); 
}

/*
static void wait_for_interrupt() // TODO: No worky.
{
    *SCR = 6;       // Make device go into deep sleep.
    __asm__("wfi"); // Wait for interrupt in asm.
}*/

// Your code will start executing here.
int main(void) 
{ 
    setup_peripheral();
    turn_off_all_leds();

    set_volume(1000);

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
