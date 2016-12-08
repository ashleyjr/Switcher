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

SBIT(TEST2, SFR_P1, 3);                 // DS5 P1.0 LED
SBIT(TEST1, SFR_P1, 4);                 // DS5 P1.0 LED

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------

void main (void){
	U16 adc;
	initDevice();
	uartInit();
	TEST1 = 1;
	TEST2 = 1;
	soft_timer = 0;
	PCA0CPH0 = 255;
	PCA0CPH1 = 255;
	while (1){
		
		// If uart has recived do somethng
		if(SCON0_RI){
			TEST1 = !TEST1;
			TEST2 = !TEST2;
			SCON0_RI = 0;
			switch(SBUF0){
				case '1': 	if(PCA0CPH0 < 255){
								PCA0CPH0++;
							}
							break;
				case '2': 	PCA0CPH0--;
							break;
				case '3': 	if(PCA0CPH1 < 255){
								PCA0CPH1++;
							}
							break;
				case '4': 	PCA0CPH1--;
							break;
				case '5':	readAdc(ADC1);
							uartSendNum(readAdc(ADC1));
							uartLoadBuffer(',');
							break;
				case '6':	readAdc(ADC2);
							uartSendNum(readAdc(ADC2));
							uartLoadBuffer(',');
							break;
				case '7':	readAdc(ADC3);
							uartSendNum(readAdc(ADC3));
							uartLoadBuffer(',');
							break;
							
			}
			uartSendNum(PCA0CPH0);
			uartLoadBuffer(',');
			uartSendNum(PCA0CPH1);
			uartLoadBuffer('\n');
			uartLoadBuffer('\r');
		}
	
		// Stall until timer reaches set point
		while(soft_timer < 200);
		soft_timer = 0;
	}
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
