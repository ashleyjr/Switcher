//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Pid.c	
// Brief:	PID controller 
//-----------------------------------------------------------------------------
#include "Pid.h"

unsigned short pidUpdate(unsigned short adc){
	unsigned short error;
	unsigned short pwm;
	error = ADC_TARGET - adc;
	pwm = P*error;
	return pwm;
}