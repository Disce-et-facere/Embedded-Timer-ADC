#include <avr/io.h>

#define F_CPU 16000000UL
#define TIMER1_PRESCALER 1
#define TIMER1_TOP_VALUE ((F_CPU / (TIMER1_PRESCALER * 10)) - 1)

void initTimer1(){ // timer set to interupt on 1ms.
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS10);
    OCR1A = TIMER1_TOP_VALUE;
    TIMSK1 |= (1 << OCIE1A);
}

void millis(uint16_t ms){

}