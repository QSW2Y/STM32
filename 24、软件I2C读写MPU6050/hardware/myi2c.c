#include "stm32f10x.h"                  // Device header
#include "delay.h"

void MyI2C_W_SCL(uint8_t BitValue)//写SCL
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
	delay_us(10);
}

void MyI2C_W_SDA(uint8_t BitValue)//写SDA
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
	delay_us(10);
}

uint8_t MyI2C_R_SDA(void)//读SDA
{
	uint8_t BitValue;
	BitValue=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	delay_us(10);
	return BitValue;
}

void MyI2C_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);
}

void MyI2C_start(void)
{
	MyI2C_W_SDA(1);//兼容重复起始条件，所以先释放SDA
	MyI2C_W_SCL(1);
	
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}

void MyI2C_stop(void)
{
	MyI2C_W_SDA(0);
	
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
	  MyI2C_W_SDA(Byte &(0x80>>i));
	  MyI2C_W_SCL(1);
	  MyI2C_W_SCL(0);
	}
}

uint8_t MyI2C_ReceiveByte(void)
{
	uint8_t Byte=0x00,i;
	MyI2C_W_SDA(1);//释放SDA，相当于切换为输入模式，防止主机干扰从机写入数据
	for(i=0;i<8;i++)
	{
		MyI2C_W_SCL(1);
	    if(MyI2C_R_SDA()==1){Byte|=(0x80>>i);}
	    MyI2C_W_SCL(0);
	}
	return Byte;
}

void MyI2C_SendAck(uint8_t AckBit)
{
	  MyI2C_W_SDA(AckBit);
	  MyI2C_W_SCL(1);
	  MyI2C_W_SCL(0);
}

uint8_t MyI2C_ReceiveAck(void)
{
	uint8_t AckBit;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	AckBit=MyI2C_R_SDA();
    MyI2C_W_SCL(0);
	return AckBit;
}







