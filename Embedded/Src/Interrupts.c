//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Interrupts.c
// Brief:	ISR routines
//-----------------------------------------------------------------------------

// USER INCLUDES			
#include <SI_C8051F850_Register_Enums.h>

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
extern 	U8 	pwm_0;   	// Holds current PCA compare value (from main)
extern 	U8 	pwm_1;   	// Holds current PCA compare value (from main)

//-----------------------------------------------------------------------------
// PCA0_ISR
//-----------------------------------------------------------------------------
INTERRUPT (PCA0_ISR, PCA0_IRQn){
	PCA0CPH0 = pwm_0;	// Assign to pwm control register
	PCA0CPH1 = pwm_1;	// Assign to pwm control register
	PCA0CN_CCF0 = 0; 	// Clear module 0 interrupt flag.
	PCA0CN_CCF1 = 0; 	// Clear module 1 interrupt flag.
}


