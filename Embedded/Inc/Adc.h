#ifndef ADC_H
#define ADC_H

#include "SI_C8051F850_Register_Enums.h"
#include "SI_C8051F850_Defs.h"

#define ADC1		0x08
#define ADC2		0x09
#define ADC3		0x0A

#define SCALE_MUL	5926
#define SCALE_DIV	1000

U16 readAdc(U8 sel);

#endif