//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Uart.c
// Brief:	Block calls to UART
//-----------------------------------------------------------------------------

#include "Uart.h"

void uartSend(U8 toSend){
	SCON0_TI = 0; 
	SBUF0 = toSend;
	while(SCON0_TI == 0);		// Stall until sent
}

U8 uartGet(void){
	while(SCON0_RI != 1);
	SCON0_RI = 0;
	return SBUF0;
}

void uartSendNum(U16 toSend){
	U16 send = toSend;
	U16 temp;

	temp = send / 10000;
	send -= (temp*10000);
	temp += 48;
	uartSend(temp);
	
		temp = send / 1000;
	send -= (temp*1000);
	temp += 48;
	uartSend(temp);
	
		temp = send / 100;
	send -= (temp*100);
	temp += 48;
	uartSend(temp);
	
		temp = send / 10;
	send -= (temp*10);
	temp += 48;
	uartSend(temp);

	uartSend(send + 48);
	
	uartSend('\r');
	uartSend('\n');
	
}