//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Uart.c
// Brief:	Block calls to UART
//-----------------------------------------------------------------------------

#include "SI_C8051F850_Register_Enums.h"
#include "SI_C8051F850_Defs.h"

#ifndef __UART_H__
#define __UART_H__

void uartSend(U8 toSend);
U8 uartGet(void);
void uartSendNum(U16 toSend);
#endif
