#include "stm32f10x.h"                  // Device header
#include "ad.h"
//扫描模式实现多通道需要配合DMA来实现

uint16_t advalue;
float dianya;
uint16_t ad0,ad1,ad2,ad3;

int main(void)
{
	
	adInit();
	while(1)
	{
		
		dianya = (float)advalue / 4095 * 3.3;
		ad0=ad_Getvalue(ADC_Channel_0);
		ad1=ad_Getvalue(ADC_Channel_1);
		ad2=ad_Getvalue(ADC_Channel_2);
		ad3=ad_Getvalue(ADC_Channel_3);
    }
}

