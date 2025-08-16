#include "stm32f10x.h"                  // Device header

int main(void)
{
	RCC->APB2ENR=0x00000010;
	GPIOC->CRH=0x00300000;
	GPIOC->ODR=0x00002000;//全零状态相反
	//其他端口配置为0影响原有配置，想要不影响其他位。还需与等于（&=）和或等于（|=）的操作
	
    while(1)
        {
	
        }
}
