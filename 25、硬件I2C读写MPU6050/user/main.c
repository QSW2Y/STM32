#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"
#include "delay.h"


int16_t AX,AY,AZ,GX,GY,GZ;

int main(void)
{
	MPU6050_Init();
	
	while(1)
	{
		MPU6050_GetData(&AX,&AY,&AZ,&GX,&GY,&GZ);
    }
}
