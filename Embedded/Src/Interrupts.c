//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Interrupts.c
// Brief:	ISR routines
//-----------------------------------------------------------------------------

#include "main.h"

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
extern volatile 		U8 uart_out[UART_SIZE_OUT];
extern volatile 		U8 head;
extern volatile 		U8 tail;
extern int 				integral;
extern U16 				target_mV;

//-----------------------------------------------------------------------------
// Interrupts
//-----------------------------------------------------------------------------
INTERRUPT (TIMER1_ISR, TIMER1_IRQn){}				// Needed for UART timing

INTERRUPT (TIMER2_ISR, TIMER2_IRQn){	
	int out;
	int error;
	U32 adc;										// Need room for multiplication so 32 bits
	TEST1 = 1;	
	ADC0MX = ADC3;									// WARNING: sel can go out of range for used ADCs
	ADC0CN0 |= ADC0CN0_ADBUSY__SET;
	while(ADC0CN0 & ADC0CN0_ADBUSY__SET);			// Wait for sample to complete
	adc = ADC0;										// Scale
	adc *= SCALE_MUL;
	adc /= SCALE_DIV;								// Timing debug
	error = (int)target_mV - (int)adc;				// PID controller
	integral += error;
	out = error*P;
	out += integral*I;	
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

	