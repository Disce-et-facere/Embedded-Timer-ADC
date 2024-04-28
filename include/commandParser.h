#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include "SerialCommunication.h"
#include "bitManipulation.h"
#include "macros.h"

typedef struct {
    int power;
    int frequence;
} NumericalCommandValues;

uint8_t commandParser(char *serialCommands[], size_t numCommands, NumericalCommandValues *values);

#endif // COMMANDPARSER_H