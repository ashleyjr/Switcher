#include "Pwm.h"

void setPwm(U16 duty, bool channel){
	if(channel){
		PCA0CPL1 = duty;
		PCA0CPH1 = duty >> 8;
	}else{
		PCA0CPL0 = duty;
		PCA0CPH0 = duty >> 8;
	}
}