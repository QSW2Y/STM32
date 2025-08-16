#include "stm32f10x.h"                  // Device header
#include "KEY.h"



int main(void)
{
	KEY_Init();
	
	if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST)==SET){
		
		
		
		RCC_ClearFlag();
	}else{
		
		
		
	}
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
	
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	WWDG_SetWindowValue(21|0x40);//30ms
	WWDG_Enable(54|0x40);//50ms
	
	while(1)
	{
		WWDG_SetCounter(54|0x40);//距离上一次喂狗不能太近，防止喂狗过快
		
    }
}

