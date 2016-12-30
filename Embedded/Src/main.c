//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Pid.h	
// Brief:	Header file for PID controller 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define SYSCLK      	24500000   				// SYSCLK frequency in Hz
#define BAUDRATE   		115200					// Baud rate of UART in bps


#define P			5
#define I			2



//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "SI_C8051F850_Register_Enums.h"
#include "SI_C8051F850_Defs.h"
#include "InitDevice.h"
#include "Uart.h"
#include "Adc.h"

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
//extern volatile bool bounce;
extern volatile U8 soft_timer;
extern volatile U8 uart_in[UART_IN_SIZE];

//SBIT(TEST2, SFR_P1, 3);                 // DS5 P1.0 LED
//SBIT(TEST1, SFR_P1, 4);                 // DS5 P1.0 LED

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------

void main (void){
	bool enabled = true;
	U16 target_mV = 5000;
	
	//U8 pwm_buck;
	//U8 pwm_boost;
	
	U16 adc3;
	
	int integral_buck = 0;
	int integral_boost = 0;
	int out;
	int error;
	
	
	initDevice();
	//uartInit();
	//TEST1 = 1;
	//TEST2 = 1;

	SCON0_RI = 0;
	
	while (1){
		soft_timer = 0;
		
		// Measure
		adc3 = readAdc(ADC3);

		// Calc error
		error = (int)target_mV - (int)adc3;

		// Buck
		integral_buck += error;
		out = error*P;
		out += integral_buck*I;	
		out /= 1000;
		if(out < 0){
			out = 0;
		}
		PCA0CPH0 = 0x00 - (U8)out;

		// Boost
		integral_boost += error;
		out = error*P;
		out += integral_boost*I;
		out /= 1000;
		if(out < 0){
			out = 0;
		}
		PCA0CPH1 = 0xFF - (U8)out;
		
		// Stall until timer reaches set point
		while(soft_timer < 2);
		
		
		
		
		
		
		
		//}
		
//		// Handle bounce back - Safe time to load buffer
//		if(bounce){
//			uartLoadOut(uart_in[0]);
//			bounce = false;				// Is it safe after this?
//		}
//		
//		// MENU
//		
//		// 1 byte commands
//		switch(uart_in[0]){
//			case 'x':	// Return ADC1 in mV
//						uartSendNum(adc1);
//						break;
//			case 'y':	// Return ADC2 in mV
//						uartSendNum(adc2);
//						break;
//			case 'z':	// Return ADC3 in mV
//						uartSendNum(adc3);
//						break;
//			case 'j':	// Return output current in mA
//						uartSendNum(11);
//						break;
//			case 'g':	// Enable the power supply
//						enabled = true;
//						break;
//			case 's':	// Disable the power supply
//						enabled = false;
//						break;
//		}
//		
//		// 5 byte commands
//		if(	uartIsNum(uart_in[0]) & 
//			uartIsNum(uart_in[1]) & 
//			uartIsNum(uart_in[2]) &
//			uartIsNum(uart_in[3]) 
//			){
//			switch(uart_in[4]){
//				case 'p':	// Write proportional setting
//							p = uartGetNum();
//							uartSendNum(p);
//							break;
//				case 'i':	// Write integral setting
//							i = uartGetNum();
//							uartSendNum(i);
//							break;
//				case 'd':	// Write derivative setting
//							d = uartGetNum();
//							uartSendNum(d);
//							break;
//				case 'v':	// Write desired voltage output in mV
//							target_mV = uartGetNum();
//							uartSendNum(target_mV);
//							break;
//				case 'c':	// Write desired current output in mA
//							c = uartGetNum();
//							uartSendNum(c);
//							break;
//				case 'u':	// Set upper limit to input operation in mV
//							uartSendNum(6);
//							break;
//				case 'l':	// Set lower limit to input operation in mV
//							uartSendNum(7);
//							break;
//			}
//		}
		
		// Stall until timer reaches set point
		while(soft_timer < 2);
	}
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
