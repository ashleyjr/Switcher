//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Uart.c
// Brief:	Block calls to UART
//-----------------------------------------------------------------------------

#include "Uart.h"

volatile U8 uart_in[UART_IN_SIZE];
volatile U8 uart_out[UART_SIZE_OUT];
volatile U8 head;
volatile U8 tail;

void uartInit(void){
	SCON0_TI = 1; 
	head = 0;
	tail = 0;
}

void uartLoadOut(U8 tx){
	uart_out[head] = tx;
	head++;
	if(head == UART_SIZE_OUT){
		head = 0;
	}
}

bool uartIsNum(U8 toCheck){
	if(toCheck > 57){
		return false;
	}
	if(toCheck < 48){
		return false;
	}
	return true;
}

void uartSendNum(U16 toSend){		// Send up to 16-bit number over UART
	U16 send = toSend;
	U16 temp;
	U16 divider = 10000;
	while(divider){
		temp = send / divider;
		send -= (temp*divider);
		uartLoadOut(temp + 48);
		divider = divider / 10;
	}
	uartLoadOut('\n');
	uartLoadOut('\r');
	uart_in[0] = 0;					// Stop UART menu from running
}

U16 uartGetNum(U8 * numStr){		// Send up to 16-bit number over UART
	U8 i;
	U16 multi = 1000;
	U16 total = 0;
	for(i=0;i<4;i++){
		total += ((*numStr--) - 48)*multi;
		multi = multi/10;
	}
	uart_in[0] = 0;					// Stop UART menu from running
	return total;
}