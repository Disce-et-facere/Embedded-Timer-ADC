#include "timer.h"

// TIMER 1
volatile uint8_t timer1_flag = TIMER_FLAG_UNSET;
volatile uint8_t is_long_mode_enabled = false;
volatile uint8_t is_tickup_mode_enabled = false;
volatile uint8_t is_cycle_skipped = false;
volatile uint8_t is_btn_count_mode_enabled = false;
volatile uint8_t tick1 = 0;
volatile uint8_t tick2 = 0;
volatile uint16_t buttonPressCount = 0;
volatile uint8_t buttonPressed = 0;

ISR(TIMER1_COMPA_vect) {
    if(is_long_mode_enabled){
        if(is_cycle_skipped){
            timer1_flag = TIMER_FLAG_SET;
            is_cycle_skipped = false;
        }else{
            is_cycle_skipped = true;
        }
    }else if(is_tickup_mode_enabled){
        tick1++;
        tick2++;
    }else if(is_btn_count_mode_enabled){
        buttonPressed = false;
        timer1_flag = TIMER_FLAG_SET;
    }else{
        timer1_flag = TIMER_FLAG_SET;
    }
}

ISR(TIMER1_CAPT_vect) {
    if (!buttonPressed) {
        buttonPressCount = ICR1;
        buttonPressed = true;
    }
}

uint8_t get_timer1_tick1(){
    return tick1;
}

uint8_t get_timer1_tick2(){
    return tick2;
}

void reset_timer1_tick1(){
    tick1 = 0;
}

void reset_timer1_tick2(){
    tick2 = 0;
}


uint8_t is_timer1_interrupt_flagged(){
    return timer1_flag;
}

void reset_timer1_flag(){
    timer1_flag = TIMER_FLAG_UNSET;
}

uint8_t get_button_count(){
    return buttonPressCount;
}

void reset_button_count(){
    buttonPressCount = 0;
    buttonPressed = false;
    is_btn_count_mode_enabled = false;
}

void set_timer1_CTC_mode(uint8_t mode){
    set_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, WAVEFORM_GENERATION_MODE_BIT_10);
    set_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, WAVEFORM_GENERATION_MODE_BIT_11);
    set_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, WAVEFORM_GENERATION_MODE_BIT_12);
    clear_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, WAVEFORM_GENERATION_MODE_BIT_13);
    set_register_bit(&TIMER1_COUNTER1_INTERRUPT_MASK_REGISTER_1, TIMER1_COUNTER1_OUTPUT_COMPARE_A_MATCH_INTERRUPT_ENABLE);  
        
    if(mode == BTN_COUNT_MODE){
        is_btn_count_mode_enabled = true;
        set_register_bit(&TIMER1_COUNTER1_INTERRUPT_MASK_REGISTER_1, TIMER1_COUNTER1_INPUT_CAPTURE_INTERRUPT_ENABLE);
        clear_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, INPUT_CAPTURE_EDGE_BIT);
    }
}

void set_timer1_prescaler(uint16_t prescaler){
    if(prescaler == PRESCALER_8){
        clear_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_10);   
        set_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_11); 
        clear_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_12);
    }else if(prescaler == PRESCALER_64){
        set_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_10);   
        set_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_11); 
        clear_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_12);
    }else if(prescaler == PRESCALER_256){
        clear_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_10);   
        clear_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_11); 
        set_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_12);
    }else if(prescaler == PRESCALER_1024){
        set_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_10);   
        clear_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_11); 
        set_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_12);
    }
}

void set_timer1_compare_value(uint16_t milliseconds, uint16_t prescaler) {
    uint32_t scaled_numerator = (uint32_t)CPU_SPEED / S_TO_MS;
    uint32_t compare_value = (scaled_numerator * milliseconds) / prescaler - 1; 
    OUTPUT_COMPARE_REGISTER_1_A = (uint16_t)compare_value;
}

void start_timer1(uint8_t mode, uint16_t milliseconds) {
    set_timer1_CTC_mode(mode);
    if(mode == TICKUP_MODE){
        is_long_mode_enabled = false;
        is_tickup_mode_enabled = true;
        set_timer1_prescaler(PRESCALER_8);
        set_timer1_compare_value(milliseconds, PRESCALER_8);
    }else if(mode == CTC_MODE || mode == BTN_COUNT_MODE){
        if(milliseconds >= MAX_PS8_MS && milliseconds <= MIN_PS8_MS){
            is_long_mode_enabled = false;
            set_timer1_prescaler(PRESCALER_8);
            set_timer1_compare_value(milliseconds, PRESCALER_8);
        }else if(milliseconds <= MAX_PS64_MS && milliseconds >= MIN_PS64_MS){
            is_long_mode_enabled = false;
            set_timer1_prescaler(PRESCALER_64);
            set_timer1_compare_value(milliseconds, PRESCALER_64);
        }else if(milliseconds <= MAX_PS256_MS && milliseconds >= MIN_PS256_MS){
            is_long_mode_enabled = false;
            set_timer1_prescaler(PRESCALER_256);
            set_timer1_compare_value(milliseconds, PRESCALER_256);
        }else if(milliseconds <= MAX_PS1024_MS && milliseconds >= MIN_PS1024_MS){
            is_long_mode_enabled = false;
            set_timer1_prescaler(PRESCALER_1024);
            set_timer1_compare_value(milliseconds, PRESCALER_1024);
        }else if(milliseconds > MAX_PS1024_MS){
            is_long_mode_enabled = true;
            set_timer1_prescaler(PRESCALER_1024);
            uint16_t half_of_ms = (uint16_t)milliseconds/2;
            set_timer1_compare_value(half_of_ms, PRESCALER_1024);
        }
    }
}

void stop_timer1() {
    clear_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_12);
    clear_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_11);
    clear_register_bit(&TIMER1_COUNTER1_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_10);
}

// TIMER 2
volatile uint16_t cycle_time_ms;
volatile uint16_t ramp_up_time_ms;
volatile uint16_t ramp_down_time_ms;
volatile uint8_t brightness = 0;
volatile uint8_t direction = true;
volatile uint16_t ramp_interval = RAMP_INTERVAL;

ISR(TIMER2_OVF_vect) {
    static uint16_t time_counter = 0;
    time_counter += ramp_interval;
    if (time_counter >= cycle_time_ms) {
        time_counter = 0;
        if (direction) {
            brightness++;
            if (brightness >= MAX_PWM_VALUE) {
                direction = false; 
            }
        } else {
            brightness--;
            if (brightness == 0) {
                direction = true; 
            }
        }
    }
    OUTPUT_COMPARE_REGISTER_2_B = brightness;
}

void set_timer2_prescaler(uint8_t mode){
    if(mode == RAMP_MODE){
        set_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_20);
        clear_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_21);
        clear_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_22);    
    }else{
        clear_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_20);
        clear_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_21);
        set_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_22);  
    }
    
}

void set_timer2_output_pin(){
    // PIN PB3
    set_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_A, COMPARE_MATCH_OUTPUT_B_1);
    set_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_A, COMPARE_MATCH_OUTPUT_A_1);
    clear_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_A, COMPARE_MATCH_OUTPUT_B_0);
}

void set_timer2_PWM_mode(uint8_t mode){
    if(mode == RAMP_MODE){
        set_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_A, WAVEFORM_GENERATION_MODE_BIT_20);
        set_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_A, WAVEFORM_GENERATION_MODE_BIT_21);
        set_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_B, WAVEFORM_GENERATION_MODE_BIT_22);
        set_register_bit(&TIMER2_COUNTER2_INTERRUPT_MASK_REGISTER_2, TIMER2_OVERFLOW_INTERRUPT_ENABLE);
        OUTPUT_COMPARE_REGISTER_2_A = MAX_PWM_VALUE;
    } else {
        set_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_A, WAVEFORM_GENERATION_MODE_BIT_20);
        set_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_A, WAVEFORM_GENERATION_MODE_BIT_21);
        clear_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_B, WAVEFORM_GENERATION_MODE_BIT_22);
        clear_register_bit(&TIMER2_COUNTER2_INTERRUPT_MASK_REGISTER_2, TIMER2_OVERFLOW_INTERRUPT_ENABLE);
    }
}

void set_timer2_PWM_duty_cycle(uint8_t duty_cycle){
    OUTPUT_COMPARE_REGISTER_2_B = duty_cycle; 
}

void start_timer2_PWM(uint8_t mode, uint16_t brightness){
        set_timer2_PWM_mode(mode);
        set_timer2_output_pin();
        set_timer2_prescaler(mode);
        if(mode == NORMAL_MODE){
            set_timer2_PWM_duty_cycle(brightness);
        }
        OUTPUT_COMPARE_REGISTER_2_A = MAX_PWM_VALUE;
        cycle_time_ms = brightness;
}

void stop_timer2_PWM(){
    clear_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_20);
    clear_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_21);
    clear_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_B, CLOCK_SELECT_BIT_22);
    clear_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_A, WAVEFORM_GENERATION_MODE_BIT_20);
    clear_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_A, WAVEFORM_GENERATION_MODE_BIT_21);
    clear_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_B, WAVEFORM_GENERATION_MODE_BIT_22);
    clear_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_A, COMPARE_MATCH_OUTPUT_B_1);
    clear_register_bit(&TIMER2_COUNTER2_CONTROL_REGISTER_A, COMPARE_MATCH_OUTPUT_B_0);
}
