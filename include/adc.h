#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "macros.h"
#include "bitManipulation.h"
#include "SerialCommunication.h"

uint8_t read_adc_flag();
void reset_adc_flag();
void set_reference_voltage();
void set_adc_prescaler();
void set_adc_channel(uint8_t adc_channel);
void enable_adc();
void enable_adc_interupt();
void enable_adc_auto_trigger_mode();
uint16_t read_adc_value();
void start_adc_conversion();
float read_adc_voltage(uint16_t adc_value);
void init_adc();

#endif // ADC_H