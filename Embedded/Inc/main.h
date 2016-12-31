#ifndef MAIN_H
#define MAIN_H

#include "SI_C8051F850_Register_Enums.h"
#include "SI_C8051F850_Defs.h"

#define SYSCLK      	24500000   				// SYSCLK frequency in Hz
#define BAUDRATE   		115200					// Baud rate of UART in bps

#define P				5
#define I				2

#define UART_IN_SIZE	5
#define UART_SIZE_OUT 	8

#define ADC1		0x08
#define ADC2		0x09
#define ADC3		0x0A

#define SCALE_MUL	5926
#define SCALE_DIV	1000

SBIT(TEST2, SFR_P1, 3);                 // DS5 P1.0 LED
SBIT(TEST1, SFR_P1, 4);                 // DS5 P1.0 LED


U16 readAdc(U8 sel);
void uartLoadOut(U8 tx);
U16 uartNumbers(U16 toSend,bool transmit);

#endif