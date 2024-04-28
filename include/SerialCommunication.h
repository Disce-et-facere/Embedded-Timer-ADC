#ifndef SERIAL_H
#define SERIAL_H

#include <avr/io.h>
#include <stdio.h>
#include "bitManipulation.h"
#include "macros.h"
#include <string.h>
#include <stdarg.h>

void init_serial();
uint8_t serialAvaliable();
void serialWrite(uint8_t data);
uint8_t serialRead();
void serialWriteLine(const char *format, ...);
void serialReadString(char* destination, uint8_t size);

#endif  // SERIAL_H