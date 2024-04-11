#include <avr/io.h>
#include "timer.h"
#include "interupt.h"
#include "pinFunctions.h"

#define blinkEnabled 0

int main(void){
    initTimer1();
    enableGlobalInterupt();
    
    while(1){
        if(blinkEnabled){
            /*if(timer1 == %200){
                
            }*/
        }
    }
    return 0;
}