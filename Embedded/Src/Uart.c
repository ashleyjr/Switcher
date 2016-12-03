//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Uart.c
// Brief:	Block calls to UART
//-----------------------------------------------------------------------------

#include "Uart.h"

void uartSend(U8 toSend){
	SCON0_TI = 0; 
	SBUF0 = toSend;
	while(SCON0_TI == 0);			// Stall until sent
}

U8 uartGet(void){
	while(SCON0_RI != 1);
	SCON0_RI = 0;
	return SBUF0;
}

void uartSendNum(U16 toSend){		// Send up to 16-bit number over UART
	U16 send = toSend;
	U16 temp;
	U16 divider = 10000;
	while(divider){
		temp = send / divider;
		send -= (temp*divider);
		uartSend(temp + 48);
		divider = divider / 10;
	}
}