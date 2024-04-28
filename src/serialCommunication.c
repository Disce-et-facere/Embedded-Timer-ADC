#include "SerialCommunication.h"

// Initiates serial communication settings
void init_serial(){
    USART_BAUD_RATE_REGISTER_HIGH = (unsigned char)((UBRR_VALUE) >> 8); // baud configuration, sets the UBRR high byte
    USART_BAUD_RATE_REGISTER_LOW = (unsigned char)UBRR_VALUE;          // baud configuration, sets the UBRR LOW byte
    USART_CONTROL_AND_STATUS_REGISTER_B = (1 << RECEIVER_ENABLE) | (1 << TRANSMITTER_ENABLE); // enables reciever and transmitter
    USART_CONTROL_AND_STATUS_REGISTER_C = (3 << USART_CHARACTER_SIZE_0); // sets the char size to 8 byte
}

// checks ifs reveiver buffer is containing byte(s)
uint8_t serialAvaliable(){
    return read_register_bit(USART_CONTROL_AND_STATUS_REGISTER_A, USART_RECEIVE_COMPLETE);
}

// transmit single char
void serialWrite(uint8_t data){
    while (!(read_register_bit(USART_CONTROL_AND_STATUS_REGISTER_A, USART_DATA_REGISTER_EMPTY)))
        ;        // checks if transmition is avaliable
    USART_IO_DATA_REGISTER = data; // moves data to be transmitted to data buffer register
}

// receive single char
uint8_t serialRead(){
        
    while (!(read_register_bit(USART_CONTROL_AND_STATUS_REGISTER_A, USART_RECEIVE_COMPLETE)))
        ;        // checks ifs buffer is containing byte(s)
    return USART_IO_DATA_REGISTER; // returns received data from data buffer register
}

// transmit formatted line
void serialWriteLine(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    for (int i = 0; buffer[i] != '\0'; ++i) {
        serialWrite(buffer[i]);
    }
    serialWrite('\n');
}

// receive string
void serialReadString(char *destination, uint8_t size){
    uint8_t index = 0;
    char receivedChar;
    do{
        receivedChar = serialRead();
        if (index < size - 1){
            destination[index] = receivedChar;
            index++;
        }
    } while (receivedChar != '\n' && index < size - 1);
    destination[index] = '\0';
    // FLUSH BUFFER - No error message here... since the message will return as invalid input.
    while (receivedChar != '\n'){
        receivedChar = serialRead();
    }
}