#include "stm32f10x.h"                  // Device header
#include "KEY.h"
#include "MyRTC.h"

	

int main(void)
{
	MYRTC_Init();
	
	while(1)
	{
		RTC_GetDivider();
		//通过对DIV的调整能为比秒还小的计数单位，例如：（32767-RTC_GetDivider()）/32767.0*999变为毫秒
		
    }
}

