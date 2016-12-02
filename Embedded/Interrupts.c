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
extern 	U8 	pwm;   	// Holds current PCA compare value (from main)

//-----------------------------------------------------------------------------
// PCA0_ISR
//-----------------------------------------------------------------------------
INTERRUPT (PCA0_ISR, PCA0_IRQn){
	PCA0CN_CCF0 = 0; 	// Clear module 0 interrupt flag.
	PCA0CPH0 = pwm;		// Assign to pwm control register
}


