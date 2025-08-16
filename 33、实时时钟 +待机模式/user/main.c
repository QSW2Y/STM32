#include "stm32f10x.h"                  // Device header
#include "KEY.h"
#include "MyRTC.h"

	

int main(void)
{
	MYRTC_Init();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	
	uint32_t Alarm=RTC_GetCounter()+10;
	RTC_SetAlarm(Alarm);//设置闹钟为10s后
	
	PWR_WakeUpPinCmd(ENABLE);//有信号进入该引脚后，可唤醒
	
	while(1)
	{
		RTC_GetDivider();
		//通过对DIV的调整能为比秒还小的计数单位，例如：（32767-RTC_GetDivider()）/32767.0*999变为毫秒
		
		
		
		//把外挂模块关了再进入待机
		PWR_EnterSTANDBYMode();//在这之后的代码无法执行
    }
}

