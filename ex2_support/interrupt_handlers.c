#include "interrupt_handlers.h"
#include "notes.h"
#include "led.h"
#include "sound.h"
#include "gpio.h"

// Experimenting with lights.
/*
static int counter_2 = 0;
static int counter_3 = 0;
static bool lights_on = 0;
static int level = 1;
void dim_lights()
{
    counter_2++;
    if (counter_2 > 100) counter_2 = 0;
    if (counter_3 > 100){
        counter_3 = 0;
        level ++;
    }
    if (level >= 100) level = 1;
    if (counter_2 < level){
        if (lights_on){
            //do nothing
        }
        else {
            turn_on_all_leds();
            lights_on = 1;
            counter_3++;
        }
    }
    else {
        if (lights_on){
            turn_off_all_leds();
            lights_on = 0;
        }
        else {
            //do nothing
        }
    }

}*/

/*
static int counter = 0;
static int current_led = 0;
static int backwards = 0;

static void make_leds_blink()
{
	counter++;
	if (counter >= 1){
		counter = 0;
        switch (current_led % 8) {
        case 0:
            set_d8_led_state(OFF);
            set_d1_led_state(ON);
            set_d2_led_state(OFF);
            break;
        case 1:
            set_d1_led_state(OFF);
            set_d2_led_state(ON);
            set_d3_led_state(OFF);
            break;
        case 2:
            set_d2_led_state(OFF);
            set_d3_led_state(ON);
            set_d4_led_state(OFF);
            break;
        case 3:
            set_d3_led_state(OFF);
            set_d4_led_state(ON);
            set_d5_led_state(OFF);
            break;
        case 4:
            set_d4_led_state(OFF);
            set_d5_led_state(ON);
            set_d6_led_state(OFF);
            break;
        case 5:
            set_d5_led_state(OFF);
            set_d6_led_state(ON);
            set_d7_led_state(OFF);
            break;
        case 6:
            set_d6_led_state(OFF);
            set_d7_led_state(ON);
            set_d8_led_state(OFF);
            break;
        case 7:
            set_d7_led_state(OFF);
            set_d8_led_state(ON);
            set_d1_led_state(OFF);
            break;
        }
        if (current_led == 7) {
            backwards = 1;
        } else if (current_led == 0) {
            backwards = 0;
        }
        if (backwards) {
            current_led--;
        }
        else {
            current_led++;
        }
	}
}*/

   
/* TIMER0 interrupt handler */
void __attribute__ ((interrupt)) TIMER0_IRQHandler() 
{
}

static int DEFAULT_VOLUME = 250;
static int current_note = NOTE_C4;
static int current_volume = 0;
static int wave_type = 0;

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
    // Change type of sound wave. Press button 8 to change sound wave.
    switch (wave_type % 3) { 
    case 0:
        generate_sinus_samples(current_note, current_volume);
        break;
    case 1:
        generate_square_samples(current_note, current_volume);
        break;
    case 2:
        generate_sawtooth_samples(current_note, current_volume);
        break;
    }

	*TIMER1_IFC = 1; // Reset timers interrupt flag.
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
    // Read button state and play note.
    if ((*GPIO_PC_DIN & 0x1) == 0) { // switch 1.
        current_note = NOTE_C4; 
        current_volume = DEFAULT_VOLUME;
    } 
    else if ((*GPIO_PC_DIN & 0x4) == 0) { // switch 3.
        current_note = NOTE_E4;
        current_volume = DEFAULT_VOLUME;
    } 
    else if ((*GPIO_PC_DIN & 0x10) == 0) { // switch 5.
        current_note = NOTE_G4;
        current_volume = DEFAULT_VOLUME;
    } 
    else if ((*GPIO_PC_DIN & 0x40) == 0) { // switch 7.
        current_note = NOTE_B4;
        current_volume = DEFAULT_VOLUME;
    } 
    else {
        current_volume = 0;
    }

	*GPIO_IFC = *GPIO_IF;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
    // Read button state and play note.
    if ((*GPIO_PC_DIN & 0x2) == 0) { // switch 2.
        current_note = NOTE_D4;
        current_volume = DEFAULT_VOLUME;
    } 
    else if ((*GPIO_PC_DIN & 0x8) == 0) { // switch 4.
        current_note = NOTE_F4;
        current_volume = DEFAULT_VOLUME;
    } 
    else if ((*GPIO_PC_DIN & 0x20) == 0) { // switch 6.
        current_note = NOTE_A4;
        current_volume = DEFAULT_VOLUME;
    } 
    else if ((*GPIO_PC_DIN & 0x80) == 0) { // switch 8.
        wave_type++;
    } 
    else {
        current_volume = 0;
    }

	*GPIO_IFC = *GPIO_IF;
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
