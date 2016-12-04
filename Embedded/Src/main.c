//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Pid.h	
// Brief:	Header file for PID controller 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define SYSCLK      	24500000   				// SYSCLK frequency in Hz
#ifdef DEBUG
	#define BAUDRATE   	567600  				// Baud rate of UART in bps
#endif

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "SI_C8051F850_Register_Enums.h"
#include "SI_C8051F850_Defs.h"
#include "InitDevice.h"
#include "Pid.h"
#include "Uart.h"
#include "Adc.h"

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
volatile bit update;

SBIT(LED1, SFR_P1, 4);                 // DS5 P1.0 LED

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------

void main (void){
	U16 adc;
	initDevice();
	uartInit();
	update = 0;
	while (1){
		LED1 = 0;
		if(update){
			LED1 = 1;
			update = 0;
			
			// PID update routine
			adc = readAdc();
			PCA0CPH0 = pidUpdate(adc,300,10);
			PCA0CPH1 = pidUpdate(adc,300,-10);

			// If uart has recived do somethng
			if(SCON0_RI){
				SCON0_RI = 0;
				switch(SBUF0){
					case 'a': 	uartSendNum(adc);
								uartLoadBuffer('\n');
								uartLoadBuffer('\r');
								break;
					case 'b': 	uartSendNum(PCA0CPH0);
								uartLoadBuffer('\n');
								uartLoadBuffer('\r');
								break;
					
				}
			}
		}
	}
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
