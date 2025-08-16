#include "stm32f10x.h"                  // Device header

extern uint16_t Num;//声明跨文件调用的变量

void timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启时钟
	
	TIM_InternalClockConfig(TIM2);
	//选择时基单元的时钟，上电后默认使用内部时钟，可不写，这里为保证过程完整所以写
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=10000-1;
	//周期，就是ARR自动重装器的值在0~65535间取值，有一个数的偏差，所以减1。取值不唯一
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;
	//PSC预分频器的值在0~65535间取值，7200和10000说明所定时间为1秒（定时频率为1Hz）
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	//重复计数器的值（高级定时器才有）
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//清除中断标志位，使的复位后计数从0开始，而不是1开始
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能中断，开启了更新中断到NVIC的通路
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//NVIC优先级分组
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;//中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2,ENABLE);//启动定时器
}


void TIM2_IRQHandler(void)//可以复制放到主函数文件，就可以使用主函数文件定义的变量
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		
		Num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}



















