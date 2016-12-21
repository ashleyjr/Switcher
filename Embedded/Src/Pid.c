//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Pid.c	
// Brief:	PID controller 
//-----------------------------------------------------------------------------
#include "Pid.h"

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------



int pidUpdate(int in, int target, int * integral, int p, int i, int stop){
	int out;
	int error;
	error = target - in;
	out = p*error;
	*integral += error/i;
	out += *integral;	
	if((out < 0)|(out > stop)){
		out = 0;
		integral = 0;
	}
	return out;
}