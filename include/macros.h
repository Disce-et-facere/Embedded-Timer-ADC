#ifndef MACROS_H
#define MACROS_H

// MAIN
#define LED_BLINK_INTERVAL 200
#define TICKS_TO_10MS 2499
#define TICKS1_TO_200MS 20
#define MAX_INTERVAL_VALUE 10
#define MIN_INTERVAL_VALUE 0
#define MIN_VOLTAGE_VALUE 0.0
#define MAX_VOLTAGE_VALUE 5.0
#define MIN_RAMP_TIME 200
#define MAX_RAMP_TIME 1500
#define LED_BLINK_ON 0
#define LED_BLINK_OFF 1
#define LED_ADC_ON 2
#define LED_ADC_OFF 3
#define LED_POWER_FREQ 4
#define LED_POWER_FREQ_OFF 5
#define BUTTON_COUNTER_ON 6
#define BUTTON_COUNTER_OFF 7
#define LED_RAMP_TIME 8
#define HELP 9
#define INVALID_COMMAND 10
#define NUMBER_OF_COMMANDS 10
#define RAMP_VALUE1 150
//#define RAMP_VALUE1 170
//#define RAMP_VALUE1 510
//#define RAMP_VALUE1 850

// PINS
#define LED_PIN PD3
#define LED_DDR DDRD
#define LED_PORT PORTD
#define BUTTON_PIN PD5
#define BUTTON_PIN_DDR DDRD
#define BUTTON_PIN_PORT PORTD
#define BUTTON_PIN8 PB0
#define BUTTON_PIN8_DDR DDRB
#define BUTTON_PIN8_PORT PORTB
#define ADC_PIN PC0
#define ADC_DDR DDRC
#define ADC_PORT PORTC

// TIMER
#define CPU_SPEED 16000000UL
#define S_TO_MS 1000UL
#define MAX_16B_TICKS 65535
#define MIN_16B_TICKS 1000 // 0
#define PS_64_VALUE 6
#define PRESCALER_1 1
#define PRESCALER_8 8
#define PRESCALER_64 64
#define PRESCALER_256 256
#define PRESCALER_1024 1024
#define MAX_PS8_MS 30
#define MIN_PS8_MS 1
#define MAX_PS64_MS 250
#define MIN_PS64_MS 31
#define MAX_PS256_MS 1000
#define MIN_PS256_MS 251
#define MAX_PS1024_MS 1001
#define MIN_PS1024_MS 4000
#define TIMER_CLOCK_FREQ (CPU_SPEED / PS_64_VALUE)
#define TIMER_FLAG_SET 1
#define TIMER_FLAG_UNSET 0
#define TICKUP_MODE 10
#define CTC_MODE 1
#define LONG_MODE 2
#define BTN_COUNT_MODE 3
#define RAMP_MODE 4
#define NORMAL_MODE 5
#define false 0
#define true 1
#define MAX_PWM_VALUE 255


// TIMER 1
#define TIMER1_PRESCALER 1024
#define TIMER1_COUNTER1_INTERRUPT_MASK_REGISTER_1 TIMSK1
#define TIMER1_COUNTER1_OUTPUT_COMPARE_A_MATCH_INTERRUPT_ENABLE OCIE1A
#define TIMER1_COUNTER1_INPUT_CAPTURE_INTERRUPT_ENABLE ICIE1
#define TIMER1_OVERFLOW_INTERRUPT_ENABLE TOIE1
#define COUNTER_REGISTER_BYTE TCNT1
#define TIMER1_COUNTER1_CONTROL_REGISTER_B TCCR1B
#define TIMER1_COUNTER1_CONTROL_REGISTER_A TCCR1A
#define WAVEFORM_GENERATION_MODE_BIT_10 WGM10
#define WAVEFORM_GENERATION_MODE_BIT_11 WGM11
#define WAVEFORM_GENERATION_MODE_BIT_12 WGM12
#define WAVEFORM_GENERATION_MODE_BIT_13 WGM13
#define CLOCK_SELECT_BIT_12 CS12
#define CLOCK_SELECT_BIT_11 CS11
#define CLOCK_SELECT_BIT_10 CS10
#define INPUT_CAPTURE_REGISTER_1 ICR1
#define OUTPUT_COMPARE_REGISTER_1_A OCR1A
#define OUTPUT_COMPARE_REGISTER_1_B OCR1B
#define INPUT_CAPTURE_EDGE_BIT ICES1
#define COMPARE_OUTPUT_MODE_B COM1B1


// TIMER2
#define TIMER2_COUNTER2_INTERRUPT_MASK_REGISTER_2 TIMSK2
#define TIMER2_COUNTER2_CONTROL_REGISTER_B TCCR2B
#define TIMER2_COUNTER2_CONTROL_REGISTER_A TCCR2A
#define TIMER2_OVERFLOW_INTERRUPT_ENABLE TOIE2
#define OUTPUT_COMPARE_REGISTER_2_B OCR2B
#define OUTPUT_COMPARE_REGISTER_2_A OCR2A
#define WAVEFORM_GENERATION_MODE_BIT_20 WGM20
#define WAVEFORM_GENERATION_MODE_BIT_21 WGM21
#define WAVEFORM_GENERATION_MODE_BIT_22 WGM22
#define CLOCK_SELECT_BIT_20 CS20
#define CLOCK_SELECT_BIT_21 CS21
#define CLOCK_SELECT_BIT_22 CS22
#define COMPARE_MATCH_OUTPUT_B_1 COM2B1
#define COMPARE_MATCH_OUTPUT_B_0 COM2B0
#define COMPARE_MATCH_OUTPUT_A_1 COM2A1
#define RAMP_INTERVAL 10


// ADC
#define ADC_REFERENCE_VOLTAGE 5.0
#define ADC_RESOLUTION 1023.0
#define ANALOG_DIGITAL_CONVERTER ADC
#define ADC_MULTIPLEXER_SELECTION_REGISTER ADMUX
#define REFERENCE_SELECTION_BIT_1 REFS1
#define REFERENCE_SELECTION_BIT_0 REFS0
#define ADC_CONTROL_AND_STATUS_REGISTER_A ADCSRA
#define ADC_CONTROL_AND_STATUS_REGISTER_B ADCSRB
#define ADC_PRESCALER_SOURCE_BIT_2 ADPS2
#define ADC_PRESCALER_SOURCE_BIT_1 ADPS1
#define ADC_PRESCALER_SOURCE_BIT_0 ADPS0
#define ADC_AUTO_TRIGGER_ENABLE_BIT ADATE
#define ADC_AUTO_TRIGGER_SOURCE_BIT_0 ADTS0
#define ADC_AUTO_TRIGGER_SOURCE_BIT_1 ADTS1
#define ADC_AUTO_TRIGGER_SOURCE_BIT_2 ADTS2
#define ADC_ENABLE_BIT ADEN
#define ADC_INTERRUPT_ENABLE_BIT ADIE 
#define ADC_INTERRUPT_FLAG ADIF
#define ADC_START_CONVERSION ADSC
#define ADC_LOW_BYTE_VALUE ADCL
#define ADC_HIGH_BYTE_VALUE ADCH

// SERIAL
#define CPU_SPEED 16000000UL // Cpu clock speed
#define BAUD 9600 // baud rate
#define UBRR_VALUE (CPU_SPEED / (16UL * BAUD)) - 1 // USART BAUD RATE REGISTER VALUE
#define USART_BAUD_RATE_REGISTER_HIGH UBRR0H
#define USART_BAUD_RATE_REGISTER_LOW UBRR0L
#define USART_CONTROL_AND_STATUS_REGISTER_A UCSR0A
#define USART_CONTROL_AND_STATUS_REGISTER_B UCSR0B
#define USART_CONTROL_AND_STATUS_REGISTER_C UCSR0C
#define USART_DATA_REGISTER_EMPTY UDRE0
#define USART_IO_DATA_REGISTER UDR0
#define RECEIVER_ENABLE RXEN0
#define USART_RECEIVE_COMPLETE RXC0
#define TRANSMITTER_ENABLE TXEN0
#define USART_CHARACTER_SIZE_0 UCSZ00

#endif // MACROS_H