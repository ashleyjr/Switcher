//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Pid.h	
// Brief:	Header file for PID controller 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define DEBUG			1						// Set to 1 to remove debug output
#define SYSCLK      	24500000   				// SYSCLK frequency in Hz
#ifdef DEBUG
	#define BAUDRATE   	115200    				// Baud rate of UART in bps
#endif

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "SI_C8051F850_Register_Enums.h"
#include "SI_C8051F850_Defs.h"
#include "InitDevice.h"
#include "Pid.h"
#include "Uart.h"
#ifdef DEBUG
	#include "stdio.h"
#endif

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
U8 	pwm_0;       								// Holds current PCA compare value
U8 	pwm_1;       								// Holds current PCA compare value

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------

void main (void){
	pwm_0 = 0;
	pwm_1 = 0;
	initDevice();
	pidInit();
	while (1){
		pwm_0 = ADC0 >> 2;
		pwm_1 = pwm_0;
		//pwm = pidUpdate(pwm);
		//uartSend(uartGet());
		#if DEBUG
			SCON0_TI = 1;                 		// This STDIO library requres TI to be set for prints to occur
			printf("%hu,%hu\n",pwm_0,pwm_1);
		#endif
	}
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
