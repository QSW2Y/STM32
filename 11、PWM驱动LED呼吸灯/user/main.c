#include "stm32f10x.h"                  // Device header
#include "PWM.h" 
#include "delay.h"

uint8_t i;

int main(void)
{
	PWM_Init();
	
	while(1)
	{
		for(i=0;i<=100;i++)//变亮
		{
			PWM_SetCompare1(i);
			delay_ms(10);
		}
		for(i=0;i<=100;i++)//变暗
		{
			PWM_SetCompare1(100-i);
			delay_ms(10);
		}
    }
}

