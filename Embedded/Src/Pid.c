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
void pidInit(void){
	integral 	= 0;
	last_error	= 0;
}

unsigned short pidUpdate(unsigned short adc){
	unsigned short error;
	unsigned short pwm;
	unsigned short p;
	unsigned short i;
	unsigned short d;
	unsigned short integral;
	unsigned short derivative;
	
	// Feedback
	error = ADC_TARGET - adc;

	// Proportional
	p = P*error;
	
	// Integral
	integral += error;
	i = I*integral;
	
	// Derivative
	derivative = error - last_error;
	last_error = error;
	d = D*derivative;
	
	// Summing node
	pwm = 	p; 
	pwm += 	i;
	pwm +=	d;
	return pwm;
}