#include <avr/io.h>

void enableGlobalInterupt(){
    SREG |= (1 << 7);
}

void disableGlobalInterupt(){
     SREG &= ~(1 << 7);
}