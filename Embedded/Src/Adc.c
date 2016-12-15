//-----------------------------------------------------------------------------
// Project: Switcher
// File: 	Adc.c	
// Brief:	ADC sampling functions 
//-----------------------------------------------------------------------------

#include "Adc.h"

// Return scaled ADC result in mV
U16 readAdc(U8 sel){
	U32 adc;									// Need room for multiplication so 32 bits
	ADC0MX = sel;								// WARNING: sel can go out of range for used ADCs
	ADC0CN0 |= ADC0CN0_ADBUSY__SET;
	while(ADC0CN0 & ADC0CN0_ADBUSY__SET);		// Wait for sample to complete
	adc = ADC0;									// Scale
	adc *= SCALE_MUL;
	adc /= SCALE_DIV;
	return adc;									// Moved back in to 16 bits
}