//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Uart.c
// Brief:	Block calls to UART
//-----------------------------------------------------------------------------

#include "Uart.h"

U8 uart_buffer[UART_BUFFER_SIZE];
U8 head;
U8 tail;

void uartInit(void){
	SCON0_TI = 1; 
	head = 0;
	tail = 0;
}

void uartUnloadBuffer(void){
	if(head != tail){
		uartSend(uart_buffer[tail]);
		tail++;
		if(tail == UART_BUFFER_SIZE){
			tail = 0;
		}
	}
}

void uartLoadBuffer(U8 tx){
	head++;
	if(head == UART_BUFFER_SIZE){
		head = 0;
	}
	uart_buffer[head] = tx;
}


void uartSend(U8 toSend){
	while(SCON0_TI == 0);			// Stall if still sending
	SCON0_TI = 0; 
	SBUF0 = toSend;
}

void uartSendNum(U16 toSend){		// Send up to 16-bit number over UART
	U16 send = toSend;
	U16 temp;
	U16 divider = 10000;
	while(divider){
		temp = send / divider;
		send -= (temp*divider);
		uartLoadBuffer(temp + 48);
		divider = divider / 10;
	}
}