#include "Pwm.h"
#include "Uart.h"

void setPwm(U16 duty, U8 channel){
	if(1 == channel){
		PCA0CPL0 = duty;
		PCA0CPH0 = duty >> 8;
	}
	if(2 == channel){
		PCA0CPL1 = duty;
		PCA0CPH1 = duty >> 8;
	}
}