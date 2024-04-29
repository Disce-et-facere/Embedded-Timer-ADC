#include "pinFunctions.h"

void toggle_led(){
    toggle_register_bit(&LED_PORT, LED_PIN);
}

void led_off(){
    clear_register_bit(&LED_PORT, LED_PIN);
}

void led_on(){
    set_register_bit(&LED_PORT, LED_PIN);
}

void init_pins(){
    // pin 3(PD3) OUTPUT LED 
    set_register_bit(&LED_DDR, LED_PIN);
    // Pin A0(PC0) INPUT ADC
    clear_register_bit(&ADC_DDR, ADC_PIN);
    // Pin 5(PD5) INPUT
    //clear_register_bit(&BUTTON_PIN_PORT, BUTTON_PIN);
    // Pin 8(PB0) INPUT
    set_register_bit(&BUTTON_PIN8_PORT, BUTTON_PIN8);
}   // Pin 5 doesnt work for input capture!!!