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
extern volatile bit update;
U32 i;
U32 j;
SBIT(LED1, SFR_P1, 4);

//-----------------------------------------------------------------------------
// PCA0_ISR
//-----------------------------------------------------------------------------
// Interrupt every 115.1KHz
INTERRUPT (TIMER1_ISR, TIMER1_IRQn){
	i++;
	if(i == 5000){
		update = 1;
		i = 0;
	}
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

