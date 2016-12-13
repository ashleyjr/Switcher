//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Uart.c
// Brief:	Block calls to UART
//-----------------------------------------------------------------------------

#include "Uart.h"

volatile U8 uart_out[UART_SIZE_OUT];
volatile U8 head;
volatile U8 tail;

volatile U8 uart_in[UART_IN_SIZE];


void uartInit(void){
	SCON0_TI = 1; 
	head = 0;
	tail = 0;
	uartClear();
}

void uartClear(void){
	uart_in[UART_IN_0] = 0;
	uart_in[UART_IN_1] = 0;
	uart_in[UART_IN_2] = 0;
	uart_in[UART_IN_3] = 0;
	uart_in[UART_IN_4] = 0;
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
	uartClear();
}