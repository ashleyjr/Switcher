//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Uart.c
// Brief:	Block calls to UART
//-----------------------------------------------------------------------------

#include "SI_C8051F850_Register_Enums.h"
#include "SI_C8051F850_Defs.h"

#ifndef __UART_H__
#define __UART_H__

#define UART_BUFFER_SIZE 64

void uartInit(void);
void uartUnloadBuffer(void);
void uartLoadBuffer(U8 tx);
void uartSend(U8 toSend);
void uartSendNum(U16 toSend);
#endif
