#ifndef ADC_H
#define ADC_H

#include "SI_C8051F850_Register_Enums.h"
#include "SI_C8051F850_Defs.h"

#define ADC1	0x08
#define ADC2	0x09
#define ADC3	0x0A

U16 readAdc(U8 sel);

#endif