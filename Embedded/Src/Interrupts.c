//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Interrupts.c
// Brief:	ISR routines
//-----------------------------------------------------------------------------

// USER INCLUDES			
#include <SI_C8051F850_Register_Enums.h>
#include "Uart.h"

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
extern 	U8 	pwm_0;   	// Holds current PCA compare value (from main)
extern 	U8 	pwm_1;   	// Holds current PCA compare value (from main)
U32 i;

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------
// Overflow rates of timer0 and timer1 are set to 1ms in Simplicity Configurator
#define LED1_TOGGLE_RATE           100 // LED1 toggle rate in milliseconds
                                       // if LED1_TOGGLE_RATE = 1, LED1 will
                                       // be on for 1 millisecond and off for
                                       // 1 millisecond
#define LED2_TOGGLE_RATE            30 // LED2 toggle rate in milliseconds
                                       // if LED2_TOGGLE_RATE = 1, LED2 will
                                       // be on for 1 millisecond and off for
                                       // 1 millisecond

//-----------------------------------------------------------------------------
// Pin Definitions
//-----------------------------------------------------------------------------
SBIT(LED1, SFR_P1, 0);                 // DS5 P1.0 LED
SBIT(LED2, SFR_P1, 1);                 // DS6 P1.1 LED


//-----------------------------------------------------------------------------
// PCA0_ISR
//-----------------------------------------------------------------------------
INTERRUPT (PCA0_ISR, PCA0_IRQn){
	PCA0CPH0 = pwm_0;	// Assign to pwm control register
	PCA0CPH1 = pwm_1;	// Assign to pwm control register
	PCA0CN_CCF0 = 0; 	// Clear module 0 interrupt flag.
	PCA0CN_CCF1 = 0; 	// Clear module 1 interrupt flag.
}

// Interrupt every 99218.75Hz
INTERRUPT (TIMER2_ISR, TIMER2_IRQn){
	i++;
	if(i == 99219){
		uartSend('a');
		i = 0;
	}
}

