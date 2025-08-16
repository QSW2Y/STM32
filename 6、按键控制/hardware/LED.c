#include "stm32f10x.h"                  // Device header
//存放驱动程序主题代码
void LED_Init(void)//初始化
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_1);
}
void LED1_ON(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
}
void LED1_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
}
void LED1_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_0)==0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_0);
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	}
}
void LED2_ON(void)//LED的打开和关闭
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
}
void LED2_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
}
void LED2_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_1)==0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
	}
}


void LED3_ON(void)//也可以定义一个LED_SET函数，然后定义两个一个参数选择操作哪个灯
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);//另一个参数选择开还是关
}
void LED3_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
}
void LED3_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5)==0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	}
}

