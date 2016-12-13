//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Uart.c
// Brief:	Block calls to UART
//-----------------------------------------------------------------------------

#include "SI_C8051F850_Register_Enums.h"
#include "SI_C8051F850_Defs.h"

#ifndef __UART_H__
#define __UART_H__

#define UART_SIZE_OUT 16

#define UART_IN_SIZE	5
#define UART_IN_0		0
#define UART_IN_1		1
#define UART_IN_2		2
#define UART_IN_3		3
#define UART_IN_4		4


void uartInit(void);
void uartClear(void);
void uartLoadOut(U8 tx);
bool uartIsNum(U8 toCheck);
void uartSendNum(U16 toSend);
#endif
