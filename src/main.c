#include <avr/io.h>
#include "timer.h"
#include "interupt.h"

#define blinkEnabled 0

int main(void){
    initTimer1();
    
    while(1){
        if(blinkEnabled){
            if(timer1 == %200){
                
            }
        }
    }
}