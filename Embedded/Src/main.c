//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Pid.h	
// Brief:	Header file for PID controller 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define SYSCLK      	24500000   				// SYSCLK frequency in Hz
#define BAUDRATE   		115200		// Baud rate of UART in bps


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
volatile U32 soft_timer;

SBIT(LED1, SFR_P1, 4);                 // DS5 P1.0 LED

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------

void main (void){
	U16 adc;
	initDevice();
	uartInit();
	soft_timer = 0;
	while (1){
		
		// Update the loop
		LED1 = 1;
		adc = readAdc(ADC1);
		PCA0CPH0 = pidUpdate(adc,300,10);
		PCA0CPH1 = pidUpdate(adc,300,-10);	
		LED1 = 0;
		
		
		// If uart has recived do somethng
		LED1 = 1;
		if(SCON0_RI){
			SCON0_RI = 0;
			switch(SBUF0){
				case 'a': 	uartSendNum(PCA0CPH0);
							uartLoadBuffer('\n');
							uartLoadBuffer('\r');
							break;
				case 'b': 	uartSendNum(PCA0CPH1);
							uartLoadBuffer('\n');
							uartLoadBuffer('\r');
							break;
			}
		}
		LED1 = 0;
		
	
		// Stall until timer reaches set point
		while(soft_timer < 200);
		soft_timer = 0;
	}
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
