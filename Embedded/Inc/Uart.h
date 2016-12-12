//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Uart.c
// Brief:	Block calls to UART
//-----------------------------------------------------------------------------

#include "SI_C8051F850_Register_Enums.h"
#include "SI_C8051F850_Defs.h"

#ifndef __UART_H__
#define __UART_H__

#define UART_SIZE_IN 8
#define UART_SIZE_OUT 16

void uartInit(void);
void uartClear(void);
void uartLoadOut(U8 tx);
void uartSendNum(U16 toSend);
#endif
