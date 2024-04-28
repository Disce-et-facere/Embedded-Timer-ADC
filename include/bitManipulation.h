#ifndef BITMANIPULATION_H
#define BITMANIPULATION_H

#include <avr/io.h>
#include "macros.h"

uint8_t read_register_bit(uint8_t reg, uint8_t bit);
void toggle_register_bit(volatile uint8_t *reg, uint8_t bit);
void set_register_bit(volatile uint8_t *reg, uint8_t bit);
void clear_register_bit(volatile uint8_t *reg, uint8_t bit);
void init_pins();

#endif // BITMANIPULATION_H