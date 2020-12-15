/*
 * Serial.h
 *
 *  Created on: 10-Dec-2020
 *      Author: mahendra
 */

#ifndef WIRINGSERIAL_SERIAL_H_
#define WIRINGSERIAL_SERIAL_H_

#ifdef __cplusplus
    extern "C" {
#endif

#include <main.h>

// Define constants and variables for buffering incoming serial data.  We're
// using a ring buffer (I think), in which rx_buffer_head is the index of the
// location to which to write the next incoming character and rx_buffer_tail
// is the index of the location from which to read.
#define RX_BUFFER_SIZE_1 512
#define RX_BUFFER_SIZE_2 512
#define SERIAL_DEFAULT_TIMEOUT 100

long baudrate;
uint8_t portNum;


/*
 * Serial handler functions for WiringSerial
 */
typedef struct __WiringSerial
{
	 void (*begin)(long baud, uint8_t portNum);
	 void (*close)(uint8_t portNum);
	 void (*Write)(unsigned char c, uint8_t portNum);
	 int  (*Available)(uint8_t portNum);
	 int  (*Read)(uint8_t portNum);
	 void (*Flush)(uint8_t portNum);
	 void (*PrintMode)(int mode, uint8_t portNum);
	 void (*PrintString)(const char *s, uint8_t portNum);
	 void (*PrintIntegerInBase)(unsigned long n, unsigned long base, uint8_t portNum);
	 void (*Puthex)(char ch, uint8_t portNum);
	 void (*PrintInteger)(long n, uint8_t portNum);
	 void (*PrintHexlong)(unsigned long n, uint8_t portNum);
	 void (*PrintOctal)(unsigned long n, uint8_t portNum);
	 void (*PrintBinary)(unsigned long n, uint8_t portNum);
}Wiring_Serial_t;

extern Wiring_Serial_t Serial;


void Serialbegin(long baud, uint8_t portNum);
void Serialclose(uint8_t portNum);
void SerialWrite(unsigned char c, uint8_t portNum);
int  SerialRead(uint8_t portNum);
int  SerialAvailable(uint8_t portNum);
void SerialFlush(uint8_t portNum);
void SerialprintByte(unsigned char c, uint8_t portNum);
void SerialprintString(const char *s, uint8_t portNum);
void SerialprintIntegerInBase(unsigned long n, unsigned long base, uint8_t portNum);
void Serialputhex(char ch, uint8_t portNum);
void SerialprintInteger(long n, uint8_t portNum);
void SerialprintMode(int mode, uint8_t portNum);
void SerialprintHexlong(unsigned long n, uint8_t portNum);
void SerialprintOctal(unsigned long n, uint8_t portNum);
void SerialprintBinary(unsigned long n, uint8_t portNum);

#ifdef __cplusplus
    }
#endif

#endif /* WIRINGSERIAL_SERIAL_H_ */
