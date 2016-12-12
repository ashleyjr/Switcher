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
#include "Pwm.h"

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
volatile U32 soft_timer;
extern volatile U8 uart_in[UART_SIZE_IN];

SBIT(TEST2, SFR_P1, 3);                 // DS5 P1.0 LED
SBIT(TEST1, SFR_P1, 4);                 // DS5 P1.0 LED

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------

void main (void){
	U8 i;
	initDevice();
	uartInit();
	TEST1 = 1;
	TEST2 = 1;
	soft_timer = 0;
	setPwm(0x80FF,0);
	setPwm(0x88FF,1);
	SCON0_RI = 0;
	while (1){
		for(i=0;i<UART_SIZE_IN;i++){
			uartLoadOut(uart_in[i]);
		}
		uartLoadOut('\n');
		uartLoadOut('\r');
	
		// Stall until timer reaches set point
		while(soft_timer < 50000);
		soft_timer = 0;
	}
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
