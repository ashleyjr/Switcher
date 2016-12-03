//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Pid.c	
// Brief:	PID controller 
//-----------------------------------------------------------------------------
#include "Pid.h"

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
unsigned short integral;
unsigned short last_error;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

U8 pidUpdate(U16 adc, U16 target, int p){
	int error;
	int pwm;
	error = target - adc;		// Feedback
	pwm = p*error;				// Proportional error
	if(pwm > PWM_TOP)			// Constrain the PWM output
		return PWM_TOP;
	if(pwm < PWM_BOTTOM)		
		return PWM_BOTTOM;
	return (U8)pwm;				// Cast as unsigned byte
}