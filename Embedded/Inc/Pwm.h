#ifndef PWM_H
#define PWM_H

#include "SI_C8051F850_Register_Enums.h"
#include "SI_C8051F850_Defs.h"

#define PWM1	false
#define PWM2	true

void setPwm(U8 duty, bool channel);

#endif