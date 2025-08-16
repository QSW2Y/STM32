#include "stm32f10x.h"                  // Device header
#include "serial.h"
#include "LED.h"
#include <string.h>


int main(void)
{
	serial_Init();

	
	while(1)
	{
		if(serial_RXFlag==1)
	{		
		if(strcmp(serial_RxPacket,"LED ON")==0)
		{
			LED1_ON();
			serial_SendString("LED_ON_OK\r\n");
		}
		else if(strcmp(serial_RxPacket,"LED OFF")==0)
		{
			LED1_OFF();
			serial_SendString("LED_OFF_OK\r\n");
		}
		else 
		{
			serial_SendString("ERROR_COMAND\r\n");
		}
		serial_RXFlag=0;
	}
    }
}

