#include "stm32f10x.h"                  // Device header

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能时钟
	GPIO_InitTypeDef GPIO_InitStructure;//结构体定义
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);//配置端口模式
	
	GPIO_SetBits(GPIOC,GPIO_Pin_13);//高电平
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);//低电平
    while(1)
        {
	
        }
}
