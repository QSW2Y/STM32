#include "stm32f10x.h"                  // Device header
#include "motor.h" 
#include "delay.h"
#include "KEY.h"

uint8_t KeyNum;
int8_t Speed;

int main(void)
{
	Motor_Init();
	KEY_Init();
	
	while(1)
	{
		KeyNum=Key_getnum();
		if(KeyNum==1)
		{
			Speed+=20;
			if(Speed>100)
			{
				Speed=-100;
			}
			Motor_SetSpeed(Speed);
		}
    }
}

