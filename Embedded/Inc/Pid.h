//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Pid.h	
// Brief:	Header file for PID controller 
//-----------------------------------------------------------------------------
#ifndef PID_H
#define PID_H

#define P 1
#define I 1
#define D 1

float pidCalcError(float input,	float target);

#endif // PID