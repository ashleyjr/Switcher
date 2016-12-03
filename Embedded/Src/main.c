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
		if(update){
			LED1 = 1;
			adc = readAdc();
			PCA0CPH0 = pidUpdate(adc,300,10);
			PCA0CPH1 = pidUpdate(adc,300,-10);
//			uartSendNum(adc);
//			uartSend(' ');
//			uartSendNum(PCA0CPH0);
//			uartSend(' ');
//			uartSendNum(PCA0CPH1);
//			uartSend('\n');
//			uartSend('\r');
			LED1 = 0;
			update = 0;
		}
	}
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
