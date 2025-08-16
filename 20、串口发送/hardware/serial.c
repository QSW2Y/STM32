#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

void serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_Mode=USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;//校验位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Init(USART1,&USART_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
}
void serial_Sendbyte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}

void serial_SendArray(uint8_t *Array,uint16_t Length)//数组无法判断是否结束，所以传递一个Length进来
{
	uint16_t i;
	for(i=0; i < Length; i++)
	{
		serial_Sendbyte(Array[i]);//依次取出数组的每一项发送
		
	}
}

void serial_SendString(char *String)//string自带结束位，不用传入长度。用uint8_t也可以
{
	uint8_t i;
	for(i=0; String!=0;i++)//0也可以换成'/0'
	{
		serial_Sendbyte(String[i]);
	}
}

uint32_t serial_pow(uint32_t x,uint32_t y)//快速幂算法
{
	uint32_t result=1;
	 while (y > 0)
    {
        if (y % 2 == 1)  // 如果 y 是奇数
        {
            result *= x;
        }
        x *= x;  // 底数平方
        y /= 2;  // 指数减半
    }
	return result;
}

void serial_SendNumber(uint32_t Number,uint16_t Length)//十进制
{
	uint8_t i;
	for(i=0;i<Length;i++)
	{
		serial_Sendbyte(Number/serial_pow(10,Length-i-1)%10+0x30);//0x30可以换为'0'
	}
}

int fputc(int ch,FILE *f)//printf默认输出到屏幕，这里重定向到串口,只用当前定义的串口可用，其他不行
{
	serial_Sendbyte(ch);
	return ch;
}

void serial_sprintf(char *format, ...)//封装sprintf
{
	char String[100];
	va_list arg;//定义一个参数列表变量
	va_start(arg,format);//从format开始接收参数表，放在arg里
	vsprintf(String,format,arg);//sprintf只能接收直接写的的参数，所以这里用vsprintf
	va_end(arg);//释放参数表
	serial_SendString(String);
}//可变函数





