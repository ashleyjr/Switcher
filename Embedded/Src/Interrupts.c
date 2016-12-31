//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Interrupts.c
// Brief:	ISR routines
//-----------------------------------------------------------------------------

#include "main.h"

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
extern volatile 		U8 		uart_out[UART_SIZE_OUT];
extern volatile 		U8 		head;
extern volatile 		U8 		tail;
extern 					int 	integral;
extern 					U16 	target_mV;
extern 					bool	enabled;				
extern volatile 		U16		adc1;
extern volatile 		U16		adc2;
extern volatile 		U16		adc3;

//-----------------------------------------------------------------------------
// Interrupts
//-----------------------------------------------------------------------------
INTERRUPT (TIMER1_ISR, TIMER1_IRQn){}				// Needed for UART timing

INTERRUPT (TIMER2_ISR, TIMER2_IRQn){	
	int out;
	int error;
	TEST1 = 1;	
	

	adc1 = readAdc(ADC1);
	adc2 = readAdc(ADC2);
	adc3 = readAdc(ADC3);
	

	error = (int)target_mV - (int)adc3;				// PID controller
	integral += error;
	out = error*P;
	out += integral*I;	
	out /= 1000;
	if((out < 0) || (!enabled)){
		out = 0;
	}
	PCA0CPH0 = PCA0CPH1 = 0xFF - (U8)out;
	


	if(head != tail){
		SBUF0 = uart_out[tail];						// Timer tuned so no need to check
		tail++;										// Transmit UART
		tail %= UART_SIZE_OUT;						// Wrap around
	}
	
	
	TMR2H = 255;									// Runs at 4KHz
	TMR2CN_TF2H = 0;								// Enable interrupt again
	TEST1 = 0;										// Timing debug
}

	