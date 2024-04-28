#include "commandParser.h"

#define BUFFER_SIZE 24 // set to longest serialCommand string.
#define COMMAND_NOT_FOUND (NUMBER_OF_COMMANDS)
#define MAX_POWER_VALUE 255 
#define MIN_POWER_VALUE 0
#define MAX_FREQUENCE_VALUE 5000
#define MIN_FREQUENCE_VALUE 200

uint8_t commandParser(char *serialCommands[], size_t numCommands, NumericalCommandValues *values) {
    char serialBuffer[BUFFER_SIZE];
    serialReadString(serialBuffer, BUFFER_SIZE);

    for (uint8_t command = 0; command < numCommands; command++) {
        if (strncmp(serialBuffer, serialCommands[command], strlen(serialCommands[command])) == 0) {
            if (sscanf(serialBuffer + strlen(serialCommands[command]), "%d %d", &values->power, &values->frequence) >= 1) {
                return command;
            } else {
                return command;
            } // end of sscanf 
                                            
        }
    }
    return COMMAND_NOT_FOUND;
}