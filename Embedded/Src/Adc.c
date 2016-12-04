#include "Adc.h"


// Warning: sel can go out of range for used ADCs
U16 readAdc(U8 sel){
	ADC0MX = sel;
	ADC0CN0 |= ADC0CN0_ADBUSY__SET;
	while(ADC0CN0 & ADC0CN0_ADBUSY__SET );
	return ADC0;
}