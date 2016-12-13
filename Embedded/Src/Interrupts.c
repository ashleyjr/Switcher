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
extern volatile bool bounce;
extern volatile U32 soft_timer;

extern volatile U8 uart_out[UART_SIZE_OUT];
extern volatile U8 uart_in[UART_IN_SIZE];
extern volatile U8 head;
extern volatile U8 tail;
extern volatile U8 uart_in_ptr;

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
	if(SCON0_RI){
		SCON0_RI = 0;
		uart_in[4] = uart_in[3];	// Small buffer, less code not to use loop
		uart_in[3] = uart_in[2];	
		uart_in[2] = uart_in[1];
		uart_in[1] = uart_in[0];
		uart_in[0] = SBUF0;
		SCON0_RI = 0;
		bounce = true;
	}
}
	


