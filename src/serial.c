#include "macros.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "pinFunctions.h"

#define CPU_SPEED 16000000UL // Cpu clock speed
#define BAUD 9600   // baud rate
#define UBRR_VALUE (CPU_SPEED / (16UL * BAUD)) - 1 // USART BAUD RATE REGISTER VALUE

// Initiates serial communication settings
void serialInit() {
    UBRR0H = (unsigned char)((UBRR_VALUE) >> 8); // baud configuration, sets the UBRR high byte
    UBRR0L = (unsigned char)UBRR_VALUE; // baud configuration, sets the UBRR LOW byte
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); // enables reciever and transmitter
    UCSR0C = (3 << UCSZ00); // sets the char size to 8 byte
}

// checks ifs buffer is containing byte(s)
uint8_t serialAvaliable(){
    return UCSR0A & (1 << RXC0); 
}

// transmit single char
void serialWrite(uint8_t data) {
    while (!(UCSR0A & (1 << UDRE0))); // checks if tramsition is avaliable
    UDR0 = data; // moves data to be transmitted to data buffer register
}

// receive single char
uint8_t serialRead() {
    while (!(UCSR0A & (1 << RXC0))); // checks ifs buffer is containing byte(s)
    return UDR0; // returns received data from data buffer register
}

// transmit String
void serialWriteString(const char* str) {
    while (*str != '\0') {
        serialWrite(*str);
        str++;
    }
}

// receive string
char* serialReadString() {
    uint8_t index = 0;
    char receivedChar;
    uint8_t bufferSize = 1;
    char* buffer = NULL; // set as NULL to make realloc act as malloc at start
    do {
        while (!(UCSR0A & (1 << RXC0))); // runs until buffer is empty
        receivedChar = serialRead();
        buffer = (char*)realloc(buffer, bufferSize * sizeof(char)); //dynamically changes size of char array
        if (buffer == NULL) {
            return NULL; // allocation error
        }
        buffer[index] = receivedChar;
        index++;
        bufferSize++;
    } while (receivedChar != '\n'); // do's until new line char
    buffer[index] = '\0'; // null termination
    return buffer; 
}

// 
void serialParser(){
    char ledpower[10] = "ledpower ";
    char invalid[16] = "Invalid Input!\n";
    char power[8] = "Power: ";
    char number[5];
    char* buffPointer = serialReadString();
    if(strncmp(buffPointer, ledpower, 9) == 0){
        int value;
        if(sscanf(buffPointer, "%*s %d", &value) == 1) {
            sprintf(number, "%d", value);
            uint8_t numLenght = strlen(number);
            number[numLenght] = '\n';
            number[numLenght + 1] = '\0';
            if(value > 127 && value < 256){
                serialWriteString(power);
                serialWriteString(number);
                setPinBit(&PORTB, PB0);
            }else if(value <= 127 && value >= 0){
                serialWriteString(power);
                serialWriteString(number);
                clearPinBit(&PORTB, PB0);
            }else{
                char badValue[44] = "Power value is either too high or too low!\n";
                serialWriteString(badValue);
            }
        }else{
            serialWriteString(invalid);
        }
    }else{
        serialWriteString(invalid);
    }
    free(buffPointer);
}

