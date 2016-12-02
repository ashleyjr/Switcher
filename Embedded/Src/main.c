//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Pid.h	
// Brief:	Header file for PID controller 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <SI_C8051F850_Register_Enums.h>
#include <stdio.h>
#include "InitDevice.h"
#include "Pid.h"

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------
#define DEBUG			1						// Comment out to remove debug output
#define SYSCLK      	24500000   				// SYSCLK frequency in Hz
#ifdef DEBUG
	#define BAUDRATE   	115200    				// Baud rate of UART in bps
#endif

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
U8 	pwm;       									// Holds current PCA compare value

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------

void main (void){
	enter_DefaultMode_from_RESET();
	pidInit();
	pwm = 0;
	while (1){
		pwm = ADC0 >> 2;
		pwm = pidUpdate(pwm);
		#if DEBUG
			SCON0_TI = 1;                 		// This STDIO library requres TI to be set for prints to occur
			printf("%d,%hu mV\n",ADC0,pwm);
		#endif
	}
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
