//=========================================================
// src/Interrupts.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

         
// USER INCLUDES			
#include <SI_C8051F850_Register_Enums.h>

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
extern 	U8 	pwm;   	// Holds current PCA compare value (from main)

//-----------------------------------------------------------------------------
// PCA0_ISR
//-----------------------------------------------------------------------------
//
// PCA0 ISR Content goes here. Remember to clear flag bits:
// PCA0CN::CCF0 (PCA Module 0 Capture/Compare Flag)
// PCA0CN::CCF1 (PCA Module 1 Capture/Compare Flag)
// PCA0CN::CCF2 (PCA Module 2 Capture/Compare Flag)
// PCA0CN::CF (PCA Counter/Timer Overflow Flag)
// PCA0PWM::COVF (Cycle Overflow Flag)
//
// This is the ISR for the PCA.  It handles the case when a match occurs on
// channel 0, and updates the PCA0CPn compare register with the value held in
// the global variable "CEX0_Compare_Value".
//
//-----------------------------------------------------------------------------
INTERRUPT (PCA0_ISR, PCA0_IRQn){
	PCA0CN_CCF0 = 0; 	// Clear module 0 interrupt flag.
	PCA0CPH0 = pwm;		// Assign to pwm control register
}


