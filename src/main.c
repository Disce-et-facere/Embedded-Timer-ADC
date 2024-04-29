#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "pinFunctions.h"
#include "SerialCommunication.h"
#include "commandParser.h"
#include "timer.h"
#include "adc.h"

void blink_led(){
    if(is_timer1_interrupt_flagged()){
        toggle_led();
        reset_timer1_flag();
    }
}

float value_converter(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
    return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

void set_led_interval_with_adc(){
    float V_TO_TIMER;
    uint16_t timer;
    if(get_timer1_tick1() == 100){
        reset_timer1_tick1();
        if(read_adc_flag()){
            uint16_t adc_value = read_adc_value();
            float adc_voltage = read_adc_voltage(adc_value);
            serialWriteLine("ADC value: %d", adc_value);
            serialWriteLine("ADC voltage: %d", (uint32_t)adc_voltage);
            V_TO_TIMER = value_converter(adc_voltage, MIN_VOLTAGE_VALUE, MAX_VOLTAGE_VALUE, MIN_INTERVAL_VALUE, MAX_INTERVAL_VALUE);
            timer = (uint8_t)V_TO_TIMER;
        }
    }

    if(get_timer1_tick2() == timer){
        if(timer == MIN_INTERVAL_VALUE){
            if(!(read_register_bit(LED_PORT, LED_PIN))){
               led_on(); 
            }
            reset_timer1_tick2();
        }else{
            toggle_led();
            reset_timer1_tick2();
        }
    }
}

void set_led_power_and_frequency(NumericalCommandValues *numValues, bool *is_timer_started, bool *is_led_power_freq_enabled){
    if(!(*is_timer_started)){
        start_timer1(CTC_MODE, numValues->frequence);
        *is_timer_started = true;
    }
    uint8_t power = numValues->power;
    uint16_t frequence = numValues->frequence;
    static uint16_t previous_frequence;
    static uint8_t is_led_on = false;
    if(power <= MAX_PWM_VALUE && power >= MIN_PWM_VALUE && frequence >= MIN_FREQUENCE_VALUE && frequence <= MAX_FREQUENCE_VALUE){
        if(is_timer1_interrupt_flagged()){
            reset_timer1_flag();
            if(!(frequence == previous_frequence)){
                stop_timer1();
                start_timer1(CTC_MODE,frequence);
            }
            if(is_led_on){
                stop_timer2_PWM();
                is_led_on = false;
            }else{
                start_timer2_PWM(NORMAL_MODE, power);
                is_led_on = true;
            }  
            previous_frequence = frequence; 
        }
        
    }else{
        *is_led_power_freq_enabled = false;
        serialWriteLine("Values are too high or too low, try again!");
    }
}

void print_button_count(){
    if(is_timer1_interrupt_flagged()){
        reset_timer1_flag();
        serialWriteLine("Button count: %d", get_button_count());
    }
}

void displayCommands(){
        char *Commands[] = {
        "Commands:",
        "led blink on",
        "led blink off",
        "led adc on",
        "led adc off",
        "led power freq 0-255 200-5000",
        "led pow freq off",
        "button counter on",
        "button counter off",
        "led ramp time 200 - 1500"
    }; 
    for (uint8_t index = 0; index < NUMBER_OF_COMMANDS; index++) {
        serialWriteLine(Commands[index]);
    }
}

int main(void) {
    char *serialCommands[NUMBER_OF_COMMANDS] = {
        "led blink on",
        "led blink off",
        "led adc on",
        "led adc off",
        "led power freq",
        "led pow freq off",
        "button counter on",
        "button counter off",
        "led ramp time",
        "help"
    }; 
    bool is_led_blink_enabled = false;
    bool is_led_adc_enabled = false;
    bool is_led_power_freq_enabled = false;
    bool is_button_counter_enabled = false;
    bool is_timer1_started = false;
    NumericalCommandValues numValues;
    init_pins();
    init_serial();
    init_adc();
    sei();
    serialWriteLine("Type \"help\" for commands!");
    while (1) {
        // SERIAL COMMANDS
        if(serialAvaliable()){ 
            cli();
            int command = commandParser(serialCommands, NUMBER_OF_COMMANDS, &numValues);
            switch(command){
                case LED_BLINK_ON:
                    stop_timer1();
                    start_timer1(CTC_MODE, LED_BLINK_INTERVAL);
                    is_led_blink_enabled = true;
                    break;
                case LED_BLINK_OFF:
                    stop_timer1();
                    led_off();
                    is_led_blink_enabled = false;
                    break;
                case LED_ADC_ON:
                    stop_timer1();
                    start_timer1(TICKUP_MODE, TICKUP_MODE);
                    is_led_adc_enabled = true;
                    break;
                case LED_ADC_OFF:
                    serialWriteLine("LAOFF");
                    is_led_adc_enabled = false;
                    break;
                case LED_POWER_FREQ:
                    is_led_power_freq_enabled = true;
                    break;
                case LED_POWER_FREQ_OFF:
                    serialWriteLine("Timer1 and timer2 off!");
                    stop_timer1();
                    stop_timer2_PWM();
                    is_timer1_started = false;
                    is_led_power_freq_enabled = false;
                    break;
                case BUTTON_COUNTER_ON:
                    start_timer1(BTN_COUNT_MODE, S_TO_MS);
                    is_button_counter_enabled = true;
                    break;
                case BUTTON_COUNTER_OFF:
                    stop_timer1();
                    is_button_counter_enabled = false;
                    break;
                case LED_RAMP_TIME:
                    if(numValues.power >= MIN_RAMP_TIME && numValues.power <= MAX_RAMP_TIME){
                       start_timer2_PWM(RAMP_MODE, numValues.power); 
                    }else{
                        serialWriteLine("Value too high to low, try again!");
                    }
                    break;
                case HELP:
                    displayCommands();
                    break;
                case INVALID_COMMAND:
                    serialWriteLine("Invalid input!");
                    break;
            }  
            sei();
        }// END OF SERIAL COMMANDS
        
        if(is_led_blink_enabled){
            blink_led();
        }else if(is_led_adc_enabled){
            set_led_interval_with_adc();
        }else if(is_led_power_freq_enabled){
            set_led_power_and_frequency(&numValues, &is_timer1_started, &is_led_power_freq_enabled);
        }else if(is_button_counter_enabled){
            print_button_count();
        }
    }
    return 0;
}