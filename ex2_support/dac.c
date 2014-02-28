#include "dac.h"

enum {
    CONTINUOUS = 0,
    SAMPLEHOLD = 1,
    SAMPLEOFF = 2
};

enum {
    SINGLE_ENDED_OUTPUT = 0,
    DIFFERENTIAL_OUTPUT = 1
};

enum {
    SINE_MODE_DISABLED = 0, // Resets sin to 0 degrees.
    SINE_MODE_ENABLE = 1 
};

enum {
    DISABLE = 0,
    PIN = 1,
    ADC = 2,
    PINADC = 3
};

enum {
    _8_CYCLES = 0,
    _16_CYCLES = 1,
    _32_CYCLES = 2
};

enum {
    DAC_OUTPUT_ENABLE_ALWAYS_ON = 0,
    DAC_OUTPUT_ENABLE_CONTROLLED_BY_PRS_SIGNAL_SELECTED_FOR_CH1 = 1
};

typedef struct {
    unsigned int diff : 1;                               // Select single-ended or differential mode.
    unsigned int sine_mode : 1;                          // Enable/disable sine mode.
    unsigned int conv_mode : 2;                          // Configure conversion mode.
    unsigned int out_mode : 2;                           // Select output mode.
    unsigned int enable_prs_controlled_output : 1;       // Enable PRS Control of DAC output enable.
    unsigned int is_preset_reset_on_channel_0_start : 1; // Select if prescaler is reset on channel 0 start.
    unsigned int reference_selection : 2;
    unsigned int : 6; // Always write bits to 0 here.
    unsigned int prescaler : 3;
    unsigned int : 1;
    unsigned int refresh_interval_select : 2;
    unsigned int : 10;
} dac_control_bits;

#define PTR_TO_DAC0_CTRL ((volatile dac_control_bits*)(DAC0_BASE2 + 0x000))

void setup_dac()
{
    // Enable and set up the Digital-Analog Converter.
    *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_DAC0;    // 1. Enable the DAC clock by setting bit 17 in CMU_HFPERCLKEN0.
    //*DAC0_CTRL = 0x50010;                       // 2. Prescale DAC clock by writing 0x50010 to DAC0_CTRL.
    
    //*DAC0_CTRL    = 0x50012;                      //  0000 0000 0000 0001 0010 8 + 4 + 2
    PTR_TO_DAC0_CTRL->diff = SINGLE_ENDED_OUTPUT;
    PTR_TO_DAC0_CTRL->sine_mode = SINE_MODE_DISABLED;
    PTR_TO_DAC0_CTRL->conv_mode = CONTINUOUS;
    PTR_TO_DAC0_CTRL->out_mode = PIN;
    PTR_TO_DAC0_CTRL->enable_prs_controlled_output = DAC_OUTPUT_ENABLE_ALWAYS_ON;
    PTR_TO_DAC0_CTRL->is_preset_reset_on_channel_0_start = 0;
    PTR_TO_DAC0_CTRL->reference_selection = 0;
    PTR_TO_DAC0_CTRL->prescaler = 0;
    PTR_TO_DAC0_CTRL->refresh_interval_select = _8_CYCLES;

    *DAC0_CH0CTRL = 1;                         // 3. Enable left and right audio channels by writing 1 to DAC0_CH0CTRL and DAC0_CH1CTRL.
    *DAC0_CH1CTRL = 1;                            
    
    // 4. Write a continuous stream of samples to the DAC data registers, DAC0_CH0DATA and DAC0_CH1DATA, for example from a timer interrupt.
}

// Write data to DAC0_CH0DATA. Only a value of 12 bits can be written to this memory cell.
void write_data_to_dac0_ch0data(int data_to_write) 
{
    *DAC0_CH0DATA = data_to_write;
}
//
// Write data to DAC0_CH1DATA. Only a value of 12 bits can be written to this memory cell.
void write_data_to_dac0_ch1data(int data_to_write) 
{
    *DAC0_CH1DATA = data_to_write;
}
