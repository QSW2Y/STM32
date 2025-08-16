#include "stm32f10x.h"                  // Device header

uint16_t countsensor_count;
void countsensor_lnit(void)  
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	在STM32中，GPIO外部中断（External Interrupt，通常简称为EXTI）的功能是通过寄存器直接控制的，
//而不是通过外设时钟来控制的。因此，在配置和使用GPIO外部中断时，并不需要像某些外设一样需要先开启外设时钟。
//GPIO外部中断的工作原理是通过配置GPIO引脚的工作模式和中断触发条件，
//然后通过EXTI寄存器来使能或禁止相应的中断线。这些配置和控制都是直接针对处理器内部的寄存器进行的，而不涉及外设时钟。
//因此，当你在STM32中使用GPIO外部中断时，只需要正确配置相关的GPIO引脚和对应的中断触发条件，而不需要单独开启外设时钟。
//NVIC是内核外设不需要开启时钟	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//可放到主模块，这是模块里分组，要确保每个模块分组相同
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//响应优先级
	NVIC_Init(&NVIC_InitStruct);
	
}

uint16_t countsensor_get(void)
{
	return countsensor_count;
}


void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line13)==SET)
	{
		countsensor_count++;
		EXTI_ClearITPendingBit(EXTI_Line13);
	}
}

//虽然在中断进出时，会用保护现场和恢复现场，但这只能保证CPU程序正常返回，对外部硬件
//的话，并没有在进入中断时进行现场保护，最好不要再主程序和中断程序里，操作可能产生冲突
//的硬件，在实现功能时，可以在中断里操作变量或者标志位，当中断返回时，再对这个变量进行显示和操作
//这样既能保证中断函数的简短快速，又能保证不产生冲突的硬件操作
//在其他地方也可以多用变量或者标志位，来减少代码间的耦合性，让各部分代码相互独立






