//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Interrupts.c
// Brief:	ISR routines
//-----------------------------------------------------------------------------

// USER INCLUDES			
#include <SI_C8051F850_Register_Enums.h>
#include "Uart.h"
#include "Pid.h"
#include "Adc.h"

#define P			10
#define I			2

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
volatile bool bounce;

U16 target_mV = 5000;
int integral_buck = 0;
int integral_boost = 0;
int out;
int error;

extern volatile U8 uart_out[UART_SIZE_OUT];
extern volatile U8 uart_in[UART_IN_SIZE];
extern volatile U8 head;
extern volatile U8 tail;
extern volatile U8 uart_in_ptr;

SBIT(TEST1, SFR_P1, 4);                 // DS5 P1.0 LED

//-----------------------------------------------------------------------------
// Interrupts
//-----------------------------------------------------------------------------
INTERRUPT (TIMER1_ISR, TIMER1_IRQn){}				// Required for UART timing

INTERRUPT (TIMER2_ISR, TIMER2_IRQn){	
	TEST1 = 1;										// Timing debug
	error = (int)target_mV - (int)readAdc(ADC3);	// PID controller
	integral_buck += error;
	out = error*P;
	out += integral_buck*I;	
	out /= 1000;
	if(out < 0){
		out = 0;
	}
	PCA0CPH0 = PCA0CPH1 = 0xFF - (U8)out;
	if(head != tail){
		SBUF0 = uart_out[tail];						// Timer tuned so no need to check
		tail++;										// Transmit UART
		if(tail == UART_SIZE_OUT){
			tail = 0;
		}
	}
	TMR2H = 254;									// Runs at 5KHz
	TMR2L = 210;
	TMR2CN_TF2H = 0;								// Enable interrupt again
	TEST1 = 0;										// Timing debug
}

INTERRUPT (UART0_ISR, UART0_IRQn){					// Interrups for both RX and TX
	if(SCON0_RI){
		SCON0_RI = 0;
		uart_in[4] = uart_in[3];					// Small buffer, less code not to use loop
		uart_in[3] = uart_in[2];
		uart_in[2] = uart_in[1];
		uart_in[1] = uart_in[0];
		uart_in[0] = SBUF0;
		bounce = true;
	}
}
	