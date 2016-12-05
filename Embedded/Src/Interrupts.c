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
		uartUnloadBuffer();
		j = 0;
	}
	TMR2CN_TF2H = 0;
	TMR2CN_TF2L = 0;
}

