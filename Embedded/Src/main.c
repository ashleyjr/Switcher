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
volatile bool bounce;
volatile U32 soft_timer;
extern volatile U8 uart_in[UART_IN_SIZE];

SBIT(TEST2, SFR_P1, 3);                 // DS5 P1.0 LED
SBIT(TEST1, SFR_P1, 4);                 // DS5 P1.0 LED

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------

void main (void){
	initDevice();
	uartInit();
	TEST1 = 1;
	TEST2 = 1;
	setPwm(0x80FF,0);
	setPwm(0x88FF,1);
	SCON0_RI = 0;
	soft_timer = 0;
	while (1){
		
		// Handle bounce back - Safe time to load buffer
		if(bounce){
			uartLoadOut(uart_in[0]);
			bounce = false;
		}
		
		// The menu
		if('x' == uart_in[0]){
			if(	uartIsNum(uart_in[1]) & 
				uartIsNum(uart_in[2]) & 
				uartIsNum(uart_in[3]) &
				uartIsNum(uart_in[4]) 
				){
				// 5 byte commands
				switch(uart_in[5]){
					case 'p':	// Write proportional setting
								uartSendNum(1);
								break;
					case 'i':	// Write integral setting
								uartSendNum(2);
								break;
					case 'd':	// Write derivative setting
								uartSendNum(3);
								break;
					case 'v':	// Write desired voltage output in mV
								uartSendNum(4);
								break;
					case 'c':	// Write desired current output in mA
								uartSendNum(5);
								break;
					case 'u':	// Set upper limit to input operation in mV
								uartSendNum(6);
								break;
					case 'l':	// Set lower limit to input operation in mV
								uartSendNum(7);
								break;
				}
			}else{
				// 2 byte commands
				switch(uart_in[1]){
					case 'x':	// Return ADC1 in mV
								uartSendNum(8);
								break;
					case 'y':	// Return ADC2 in mV
								uartSendNum(9);
								break;
					case 'z':	// Return ADC3 in mV
								uartSendNum(10);
								break;
					case 'c':	// Return output current in mA
								uartSendNum(11);
								break;
					case 'g':	// Enable the power supply
								uartSendNum(12);
								break;
					case 's':	// Disable the power supply
								uartSendNum(13);
								break;
					case 'p':	// Read proportional setting
								uartSendNum(14);
								break;
					case 'i':	// Read integral setting
								uartSendNum(15);
								break;
					case 'd':	// Read derivative setting
								uartSendNum(16);
								break;
				}
			}
		}
	
		// Stall until timer reaches set point
		while(soft_timer < 10000);
		soft_timer = 0;
	}
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
