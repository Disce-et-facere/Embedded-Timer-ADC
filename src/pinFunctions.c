#include "avr/io.h"
#include "macros.h"

void pinInit(){
    // pin 3(PD3) OUTPUT LED 
    DDRD |= (1 << PD3); 
    // Pin A0(PC0) INPUT ADC
    DDRC &= ~(1 << PC0);
}

void ADCInit() {
    // Set reference voltage to AVCC with external capacitor at AREF pin
    ADMUX |= (1 << REFS0);
    // Set ADC prescaler to 128 (ADC clock = 16MHz / 128 = 125kHz)
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    // Enable ADC
    ADCSRA |= (1 << ADEN);
}

uint8_t digitalRead(uint8_t pinReg, uint8_t pin){
    return (pinReg & (1 << pin)) ? 1 : 0; // checks (AND) if bit on pin register is set to either 1 or 0
}

uint16_t analogRead(){
    return ADC;
}

void togglePinBit(volatile uint8_t *portReg, uint8_t pin){
    *portReg ^= (1 << pin); // toggle bit (XOR) on port register
}

void setPinBit(volatile uint8_t *portReg, uint8_t pin){
    *portReg |= (1 << pin); // set bit (OR) on port register
}

void clearPinBit(volatile uint8_t *portReg, uint8_t pin){
    *portReg &= ~(1 << pin); // clear bit (NOT) on port register
}