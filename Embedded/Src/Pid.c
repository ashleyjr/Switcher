//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Pid.c	
// Brief:	PID controller 
//-----------------------------------------------------------------------------
#include "Pid.h"

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------



int pidUpdate(U16 in, U16 target, int * integral, int p, int i){
	int out;
	int error;
	error = (int)target - (int)in;
	*integral += error;
	
	out = error*p;
	out += *integral*i;	
	
	return out >> 8;
}