#include "Adc.h"

U16 readAdc(void){
	ADC0CN0 |= ADC0CN0_ADBUSY__SET;
	while(ADC0CN0 & ADC0CN0_ADBUSY__SET );
	return ADC0;
}