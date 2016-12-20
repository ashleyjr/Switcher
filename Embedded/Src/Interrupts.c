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
volatile bool bounce;
volatile U8 soft_timer;

extern volatile U8 uart_out[UART_SIZE_OUT];
extern volatile U8 uart_in[UART_IN_SIZE];
extern volatile U8 head;
extern volatile U8 tail;
extern volatile U8 uart_in_ptr;

//-----------------------------------------------------------------------------
// Interrupts
//-----------------------------------------------------------------------------

INTERRUPT (TIMER2_ISR, TIMER2_IRQn){	
	soft_timer++;
	if(head != tail){
		SBUF0 = uart_out[tail];				// Timer tuned so no need to check
		tail++;
		if(tail == UART_SIZE_OUT){
			tail = 0;
		}
	}
	TMR2H = 250;							// Tx every 1 ms
	TMR2CN_TF2H = 0;						// Enable interrupt again
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
		bounce = true;
	}
}
	


