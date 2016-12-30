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
extern volatile bool bounce;
extern volatile U8 soft_timer;
extern volatile U8 uart_in[UART_IN_SIZE];

SBIT(TEST2, SFR_P1, 3);                 // DS5 P1.0 LED
SBIT(TEST1, SFR_P1, 4);                 // DS5 P1.0 LED

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------

void main (void){
	bool enabled = true;
	U16 target_mV = 5000;
	
	U16 p,i,d,c;
	
	U8 pwm_buck;
	U8 pwm_boost;
	
	U16 adc1;
	U16 adc2;
	U16 adc3;
	
	int integral_buck = 0;
	int integral_boost = 0;
	
	
	
	initDevice();
	uartInit();
	TEST1 = 1;
	TEST2 = 1;

	SCON0_RI = 0;
	soft_timer = 0;	
	
	
	setPwm(0x00,PWM1);
	setPwm(0xFF,PWM2);
	// Stall for in rush
	soft_timer = 0;
	while(soft_timer < 200);

	
	
	while (1){
		TEST1 = 1;
		
		// Capture
		adc1 = readAdc(ADC1);
		adc2 = readAdc(ADC2);
		adc3 = readAdc(ADC3);
		
		// Run control loop
		pwm_buck = 0x00;
		pwm_boost = 0xFF;
		if(enabled){
			//pwm_buck += (U16)(-pidUpdate(adc3,target_mV,&integral_buck,1,0,30000));
			pwm_boost -= (U8)pidUpdate(adc3,target_mV,&integral_boost,3000);
			uartSendNum(pwm_boost);
		}
		setPwm(pwm_buck,PWM1);
		setPwm(pwm_boost,PWM2);
		
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
							p = uartGetNum();
							uartSendNum(p);
							break;
				case 'i':	// Write integral setting
							i = uartGetNum();
							uartSendNum(i);
							break;
				case 'd':	// Write derivative setting
							d = uartGetNum();
							uartSendNum(d);
							break;
				case 'v':	// Write desired voltage output in mV
							target_mV = uartGetNum();
							uartSendNum(target_mV);
							break;
				case 'c':	// Write desired current output in mA
							c = uartGetNum();
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
		while(soft_timer < 14);		// 100Hz
		soft_timer = 0;
	}
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
