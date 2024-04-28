#include "bitManipulation.h"

uint8_t read_register_bit(uint8_t reg, uint8_t bit){
    return (reg & (1 << bit)) ? 1 : 0; // checks (AND) if bit on register is set to either 1 or 0
}

void toggle_register_bit(volatile uint8_t *reg, uint8_t bit){
    *reg ^= (1 << bit); // toggle bit (XOR) on register
}

void set_register_bit(volatile uint8_t *reg, uint8_t bit){
    *reg |= (1 << bit); // set bit (OR) on register
}

void clear_register_bit(volatile uint8_t *reg, uint8_t bit){
    *reg &= ~(1 << bit); // clear bit (NOT) on register
}