#include "stm32f10x.h"                  // Device header
#include "PWM.h" 
#include "delay.h"
#include "IC.h"

uint8_t i;

int main(void)
{
	PWM_Init();
	IC_Init ();
	
	PWM_SetPrescaler(720-1);//Freq=72M/(psc+1)/100
	PWM_SetCompare1(50);//Duty=CCR/100
	
	while(1)
	{
		
    }
}

