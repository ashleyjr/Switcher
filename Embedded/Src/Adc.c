#include "Adc.h"

U16 readAdc(U8 sel){
	switch(sel){
		case 1: ADC0MX = ADC0MX_ADC0MX__ADC0P8;
				break;
		case 2: ADC0MX = ADC0MX_ADC0MX__ADC0P9;
				break;
		case 3: ADC0MX = ADC0MX_ADC0MX__ADC0P10;
				break;
	}
	ADC0CN0 |= ADC0CN0_ADBUSY__SET;
	while(ADC0CN0 & ADC0CN0_ADBUSY__SET );
	return ADC0;
}