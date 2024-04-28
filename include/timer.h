#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "macros.h"
#include "bitManipulation.h"
#include "SerialCommunication.h"

// TIMER 1
uint8_t get_timer1_tick1();
uint8_t get_timer1_tick2();
void reset_timer1_tick1();
void reset_timer1_tick2();
uint8_t is_timer1_interrupt_flagged();
void reset_timer1_flag();
uint8_t get_button_count();
void reset_button_count();
void set_timer1_CTC_mode(uint8_t mode);
void set_timer1_compare_value(uint16_t milliseconds, uint16_t prescaler);
void start_timer1(uint8_t mode, uint16_t milliseconds);
void stop_timer1();

// TIMER 2
void set_timer2_prescaler(uint8_t mode);
void set_timer2_output_pin();
void set_timer2_PWM_mode(uint8_t mod);
void set_timer2_PWM_duty_cycle(uint8_t duty_cycle);
void start_timer2_PWM(uint8_t mode, uint16_t brightness);
void stop_timer2_PWM();

#endif // TIMER_H