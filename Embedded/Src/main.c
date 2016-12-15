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
	bool enabled = true;
	int target_mV = 5800;
	
	U16 p,i,d,c;
	U16 pwm;
	
	U16 adc1;
	U16 adc2;
	U16 adc3;
	
	
	
	initDevice();
	uartInit();
	TEST1 = 1;
	TEST2 = 1;
	setPwm(0x0000,PWM1);

	SCON0_RI = 0;
	soft_timer = 0;	
	while (1){
		TEST1 = 1;
		
		// Capture
		adc1 = readAdc(ADC1);
		adc2 = readAdc(ADC2);
		adc3 = readAdc(ADC3);
		
		// Run control loop
		pwm = 0xFFFF;
		if(enabled){
			pwm -= (U16)pidUpdate(adc3,target_mV,10,5,30000);
		}
		setPwm(pwm,PWM2);
		
		// Handle bounce back - Safe time to load buffer
		if(bounce){
			uartLoadOut(uart_in[0]);
			bounce = false;				// Is it safe after this?
		}
		
		// MENU
		
		// 1 byte commands
		switch(uart_in[0]){
			case 'x':	// Return ADC1 in mV
						uartSendNum(adc1);
						break;
			case 'y':	// Return ADC2 in mV
						uartSendNum(adc2);
						break;
			case 'z':	// Return ADC3 in mV
						uartSendNum(adc3);
						break;
			case 'j':	// Return output current in mA
						uartSendNum(11);
						break;
			case 'g':	// Enable the power supply
						enabled = true;
						break;
			case 's':	// Disable the power supply
						enabled = false;
						break;
		}
		
		// 5 byte commands
		if(	uartIsNum(uart_in[0]) & 
			uartIsNum(uart_in[1]) & 
			uartIsNum(uart_in[2]) &
			uartIsNum(uart_in[3]) 
			){
			switch(uart_in[4]){
				case 'p':	// Write proportional setting
							p = uartGetNum(&uart_in[3]);
							uartSendNum(p);
							break;
				case 'i':	// Write integral setting
							i = uartGetNum(&uart_in[3]);
							uartSendNum(i);
							break;
				case 'd':	// Write derivative setting
							d = uartGetNum(&uart_in[3]);
							uartSendNum(d);
							break;
				case 'v':	// Write desired voltage output in mV
							target_mV = uartGetNum(&uart_in[3]);
							uartSendNum(target_mV);
							break;
				case 'c':	// Write desired current output in mA
							c = uartGetNum(&uart_in[3]);
							uartSendNum(c);
							break;
				case 'u':	// Set upper limit to input operation in mV
							uartSendNum(6);
							break;
				case 'l':	// Set lower limit to input operation in mV
							uartSendNum(7);
							break;
			}
		}
		TEST1 = 0;
		
		// Stall until timer reaches set point
		while(soft_timer < 300);
		soft_timer = 0;
	}
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
