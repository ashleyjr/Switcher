#include "Pwm.h"

void setPwm(U8 duty, bool channel){
	if(channel){
		PCA0CPH1 = duty;
	}else{
		PCA0CPH0 = duty;
	}
}