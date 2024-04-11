#ifndef SERIAL_H
#define SERIAL_H

void serialInit();
uint8_t serialAvaliable();
void serialWrite(uint8_t data);
uint8_t serialRead();
void serialWriteString(const char* str);
char* serialReadString();
void serialParser();

#endif  // SERIAL_H