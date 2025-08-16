#include "stm32f10x.h"                  // Device header
#include "delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能时钟
	GPIO_InitTypeDef GPIO_InitStructure;//结构体定义
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//配置端口模式
	
	GPIO_SetBits(GPIOB,GPIO_Pin_0);//高电平
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);//低电平
	GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);//高电平
    GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);//低电平
	
    while(1)
        {
	    GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);//PP模式下高低电平都有驱动能力
		delay_ms(500);
	    GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);//开漏输出模式高电平是没有驱动能力的，低电平则有
		delay_ms(500);
			
		GPIO_WriteBit(GPIOB,GPIO_Pin_0,(BitAction)0);//一般情况下使用推挽输出模式
		delay_ms(500);
	    GPIO_WriteBit(GPIOB,GPIO_Pin_0,(BitAction)1);
		delay_ms(500);
        }
}

void Delay(__IO uint32_t nCount)	//简单延时函数
{
	for(; nCount != 0; nCount--);
}













