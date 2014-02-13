	

            .syntax unified
           
                  .include "efm32gg.s"
     
            /////////////////////////////////////////////////////////////////////////////
            //
      // Exception vector table
      // This table contains addresses for all exception handlers
            //
            /////////////////////////////////////////////////////////////////////////////
           
            .section .vectors
           
                  .long   stack_top               /* Top of Stack                 */
                  .long   _reset                  /* Reset Handler                */
                  .long   dummy_handler           /* NMI Handler                  */
                  .long   dummy_handler           /* Hard Fault Handler           */
                  .long   dummy_handler           /* MPU Fault Handler            */
                  .long   dummy_handler           /* Bus Fault Handler            */
                  .long   dummy_handler           /* Usage Fault Handler          */
                  .long   dummy_handler           /* Reserved                     */
                  .long   dummy_handler           /* Reserved                     */
                  .long   dummy_handler           /* Reserved                     */
                  .long   dummy_handler           /* Reserved                     */
                  .long   dummy_handler           /* SVCall Handler               */
                  .long   dummy_handler           /* Debug Monitor Handler        */
                  .long   dummy_handler           /* Reserved                     */
                  .long   dummy_handler           /* PendSV Handler               */
                  .long   dummy_handler           /* SysTick Handler              */
     
                  /* External Interrupts */
                  .long   dummy_handler
                  .long   gpio_handler          /* GPIO even handler */
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   gpio_handler            /* GPIO odd handler */
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
                  .long   dummy_handler
     
                  .section .text
     
            /////////////////////////////////////////////////////////////////////////////
            //
            // Reset handler
      // The CPU will start executing here after a reset
            //
            /////////////////////////////////////////////////////////////////////////////
     
                  .globl  _reset
                  .type   _reset, %function
            .thumb_func
    _reset:
		    // Enable clock.
                    ldr r1, cmu_base_address
                    ldr r2, [r1, #CMU_HFPERCLKEN0]
                    mov r3, #1
                    lsl r3, r3, #CMU_HFPERCLKEN0_GPIO
                    orr r2, r2, r3
                    str r2, [r1, #CMU_HFPERCLKEN0]
     
		    // Enable GPIO-controller.
                    ldr r1, gpio_pa_base_address
                    mov r2, #0x2
                    str r2, [r1, #GPIO_CTRL]
     
	            // Enable GPIOs to give the program the ability to output current.
                    mov r2, #0x55555555
                    str r2, [r1, #GPIO_MODEH]

		    // Enable.
                    ldr r1, gpio_pc_base_address           
                    mov r2, #0x33333333
                    str r2, [r1, GPIO_MODEL]
     
                    mov r2, #0xff
                    str r2, [r1, GPIO_DOUT]
                   
                    ldr r1, gpio_extipsell
                    mov r2, #0x22222222
                    str r2, [r1]
                   
                    ldr r1, gpio_extifall
                    mov r2, #0xff
                    str r2, [r1]

                    ldr r1, gpio_extirise
                    mov r2, #0xff
                    str r2, [r1]

                    ldr r1, gpio_ien
                    mov r2, #0xff
                    str r2, [r1]
                   
                    ldr r1, scr // Throws an interrupt.
                    mov r2, #6
                    str r2, [r1]
                   
                    ldr r1, =GPIO_BASE
                    mov r2, #0xff
                    str r2, [r1, #GPIO_IFC]
                    ldr r1, isero
     
                    ldr r2, =0x802
                   
                    str r2, [r1]
                   
    loop:
                    ldr r1, scr // The value in scr has to be set everytime an interrupt happens, because it gets reset when an interrupts is thrown.
                    mov r2, #6
                    str r2, [r1]
                   
                    wfi
                    b loop
                                   

     
    scr:
                    .long SCR
    isero:
            .long ISER0
     
    cmu_base_address:
                    .long CMU_BASE
    gpio_pa_base_address:
                    .long GPIO_PA_BASE
    gpio_pc_base_address:
                    .long GPIO_PC_BASE
    gpio_extipsell:
                    .long GPIO_BASE+GPIO_EXTIPSELL
    gpio_extifall:
                    .long GPIO_BASE+GPIO_EXTIFALL
    gpio_extirise:
                    .long GPIO_BASE+GPIO_EXTIRISE
    gpio_ien:
                    .long GPIO_BASE+GPIO_IEN
    gpio_if:
                    .long GPIO_BASE+GPIO_IF
    gpio_ifc:
                    .long GPIO_BASE+GPIO_IFC
            /////////////////////////////////////////////////////////////////////////////
            //
      // GPIO handler
      // The CPU will jump here when there is a GPIO interrupt
            //
            /////////////////////////////////////////////////////////////////////////////
           
            .thumb_func
    gpio_handler:  
		    // Copy the button state bits to the "GPIO output to LED"-bits.
                    ldr r1, gpio_pc_base_address
                    ldr r2, [r1, #GPIO_DIN]
                    lsl r2, r2, #8
                    ldr r1, gpio_pa_base_address
                    str r2, [r1, #GPIO_DOUT]
		    // Clear interrupt flag.
		    ldr r1, gpio_if
                    ldr r2, [r1]
                    str r2, [r1, 8]
                    bx lr


  
            /////////////////////////////////////////////////////////////////////////////
           
            .thumb_func
    dummy_handler:  
            b .  // do nothing
