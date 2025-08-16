#include "stm32f10x.h"                  // Device header
#include "delay.h"
void KEY_Init(void)//初始化
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

uint8_t Key_getnum(void)
{
	uint8_t keynum=0;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)
	{
		delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1);
		delay_ms(20);
		keynum=1;
	}
	
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==1)
	{
		delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==1);
		delay_ms(20);
		keynum=2;
	}
	return keynum;
}

//uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
//{			
//	
//	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1 )  
//	{	 
//		
//		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1);   
//		return 	1;	 
//	}
//	else
//		return 0;
//}
