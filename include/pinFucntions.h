#ifndef PINFUNCTIONS_H
#define PINFUNCTIONS_H

#include "avr/io.h"

void pinInit();
uint8_t digitalRead(uint8_t pinReg, uint8_t pin);
void togglePinBit(volatile uint8_t *portReg, uint8_t pin);
void setPinBit(volatile uint8_t *portReg, uint8_t pin);
void clearPinBit(volatile uint8_t *portReg, uint8_t pin);

#endif  // PINFUNCTIONS_H