//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Pid.h	
// Brief:	Header file for PID controller 
//-----------------------------------------------------------------------------
#ifndef PID_H
#define PID_H

#define P 			10
#define I 			1
#define D 			1
#define ADC_TARGET	100

unsigned short pidUpdate(unsigned short adc);

#endif // PID