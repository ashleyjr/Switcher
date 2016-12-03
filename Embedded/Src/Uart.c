//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Uart.c
// Brief:	Block calls to UART
//-----------------------------------------------------------------------------

#include "Uart.h"

void uartSend(U8 toSend){
	SCON0_TI = 1; 
	SBUF0 = toSend;
	SCON0_TI = 0;
}

U8 uartGet(void){
	while(SCON0_RI != 1);
	SCON0_RI = 0;
	return SBUF0;
}