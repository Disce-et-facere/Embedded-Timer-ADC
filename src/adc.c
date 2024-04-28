#include "adc.h"

#define ADC_FLAG_SET 1
#define ADC_FLAG_UNSET 0

volatile uint8_t adc_flag = ADC_FLAG_UNSET;

ISR(ADC_vect){
    adc_flag = ADC_FLAG_SET;
}

uint8_t read_adc_flag(){
    return adc_flag;
}

void reset_adc_flag(){
    adc_flag = ADC_FLAG_UNSET;
}

void set_reference_voltage(){
    // ADC voltage reference set to internal 5v.
    set_register_bit(&ADC_MULTIPLEXER_SELECTION_REGISTER, REFERENCE_SELECTION_BIT_0);
    clear_register_bit(&ADC_MULTIPLEXER_SELECTION_REGISTER, REFERENCE_SELECTION_BIT_1);
}

void set_adc_prescaler(){
    // prescaler set to 4 to get a conversion time(8125ms) as close to 1 sec as possible.
    clear_register_bit(&ADC_CONTROL_AND_STATUS_REGISTER_A, ADC_PRESCALER_SOURCE_BIT_2);
    set_register_bit(&ADC_CONTROL_AND_STATUS_REGISTER_A, ADC_PRESCALER_SOURCE_BIT_1);
    clear_register_bit(&ADC_CONTROL_AND_STATUS_REGISTER_A, ADC_PRESCALER_SOURCE_BIT_0);
}

void set_adc_channel(uint8_t adc_channel){
    ADMUX &= 0xF0;
    // Set new channel selection
    ADMUX |= (adc_channel & 0x0F);
    //clear_register_bit(&ADC_MULTIPLEXER_SELECTION_REGISTER, ADC_PIN);
}

void set_adc_auto_trigger_mode(){
    // Mode set to free running.
    clear_register_bit(&ADC_CONTROL_AND_STATUS_REGISTER_B, ADC_AUTO_TRIGGER_SOURCE_BIT_2);
    clear_register_bit(&ADC_CONTROL_AND_STATUS_REGISTER_B, ADC_AUTO_TRIGGER_SOURCE_BIT_1);
    clear_register_bit(&ADC_CONTROL_AND_STATUS_REGISTER_B, ADC_AUTO_TRIGGER_SOURCE_BIT_0);
}

void enable_adc(){
    set_register_bit(&ADC_CONTROL_AND_STATUS_REGISTER_A, ADC_ENABLE_BIT);
}

void enable_adc_interupt(){
    set_register_bit(&ADC_CONTROL_AND_STATUS_REGISTER_A, ADC_INTERRUPT_ENABLE_BIT);
}

void enable_adc_auto_trigger_mode(){
    clear_register_bit(&ADC_CONTROL_AND_STATUS_REGISTER_A, ADC_AUTO_TRIGGER_ENABLE_BIT);
}

uint16_t combine_adc_values(uint8_t low_byte, uint8_t high_byte) {
    return low_byte | (high_byte << 8);
}

uint16_t read_adc_value() {
    uint16_t adc_result = combine_adc_values(ADC_LOW_BYTE_VALUE, ADC_HIGH_BYTE_VALUE);
    ADCSRA |= (1 << ADIF);
    reset_adc_flag();
    set_register_bit(&ADC_CONTROL_AND_STATUS_REGISTER_A, ADC_START_CONVERSION);
    return adc_result;
}

float read_adc_voltage(uint16_t adc_value) {
    return (adc_value * ADC_REFERENCE_VOLTAGE) / ADC_RESOLUTION;
}

void start_adc_conversion(){
    set_register_bit(&ADC_CONTROL_AND_STATUS_REGISTER_A, ADC_START_CONVERSION);
}

void init_adc(){
    set_reference_voltage();
    set_adc_channel(ADC_PIN);
    enable_adc();
    enable_adc_interupt();
    set_adc_auto_trigger_mode();
    set_adc_prescaler();
    start_adc_conversion();
}