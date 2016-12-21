//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Pid.h	
// Brief:	Header file for PID controller 
//-----------------------------------------------------------------------------
#ifndef PID_H
#define PID_H

#include "SI_C8051F850_Register_Enums.h"
#include "SI_C8051F850_Defs.h"

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

#define PWM_TOP		250
#define PWM_BOTTOM	5

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------

int pidUpdate(int , int target, int * integral, int p, int i, int stop);

#endif // PID