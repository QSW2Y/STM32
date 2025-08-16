#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);//重映射引脚（更改复用的引脚）
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//解除调试端口。这三句把定时器的通道从PA0挪到PA15
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用的情况下引脚控制权由数据寄存器转到外设
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);//选择时基单元的时钟，上电后默认使用内部时钟，可不写，这里为保证过程完整所以写
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=100-1;//周期，就是ARR自动重装器的值在0~65535间取值，有一个数的偏差，所以减1。取值不唯一
	TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;//PSC预分频器的值在0~65535间取值，7200和10000说明所定时间为1秒（定时频率为1Hz）
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//重复计数器的值（高级定时器才有）
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	//没用到构体内的所有成员，使用高级定时器时会出问题，所以在这给结构体赋初始值再修改需要使用的成员
	//或者用到的、没用到的全配置一遍。或者把初始化函数放到程序的第一行
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;//就是CCR的值
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	
	
	
	TIM_Cmd(TIM2,ENABLE);//启动定时器

}

void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare);
}
void PWM_SetPrescaler(uint16_t Prescaler)//改变psc
{
	TIM_PrescalerConfig(TIM2,Prescaler,TIM_PSCReloadMode_Update);
}



