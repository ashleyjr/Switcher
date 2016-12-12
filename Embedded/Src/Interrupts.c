//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Interrupts.c
// Brief:	ISR routines
//-----------------------------------------------------------------------------

// USER INCLUDES			
#include <SI_C8051F850_Register_Enums.h>
#include "Uart.h"
#include "Pid.h"

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
extern volatile U32 soft_timer;

extern volatile U8 uart_out[UART_SIZE_OUT];
extern volatile U8 uart_in[UART_SIZE_IN];
extern volatile U8 head;
extern volatile U8 tail;

U32 j;

//-----------------------------------------------------------------------------
// PCA0_ISR
//-----------------------------------------------------------------------------
// Interrupt every 115.1KHz
INTERRUPT (TIMER1_ISR, TIMER1_IRQn){
	soft_timer++;
}

INTERRUPT (TIMER2_ISR, TIMER2_IRQn){
	j++;
	if(j == 2){
		if(head != tail){
			SBUF0 = uart_out[tail];				// Timer tuned so no need to check
			tail++;
			if(tail == UART_SIZE_OUT){
				tail = 0;
			}
		}
		j = 0;
	}
	TMR2CN_TF2H = 0;
	TMR2CN_TF2L = 0;
}

// Interrups for both RX and TX
INTERRUPT (UART0_ISR, UART0_IRQn){
	U8 i;
	if(SCON0_RI){
		for(i=0;i<(UART_SIZE_IN-1);i++){
			uart_in[i] = uart_in[i+1];
		}
		uart_in[UART_SIZE_IN-1] = SBUF0;
		SCON0_RI = 0;
	}
}
	


