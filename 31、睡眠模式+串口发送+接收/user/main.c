#include "stm32f10x.h"                  // Device header
#include "serial.h"

uint8_t RXdata;

int main(void)
{
	serial_Init();
	
	
	
	while(1)
	{
		if(serial_GetRXFlag()==1)//串口接收的查询方法
		{
			RXdata=serial_GetRXData();
			serial_Sendbyte(RXdata);//回传到电脑
			
		}
		__WFI();//中断唤醒使用较多
		//__WFE();//事件唤醒
    }
}

