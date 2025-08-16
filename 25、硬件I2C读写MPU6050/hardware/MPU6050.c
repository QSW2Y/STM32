#include "stm32f10x.h"                  // Device header
#include "MPU6050_Reg.h"

#define MPU6050_Address   0xD0

void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
	uint32_t Timeout=10000;
	
	while(I2C_CheckEvent(I2Cx,I2C_EVENT)!=SUCCESS)
	{
		Timeout--;
		if(Timeout==0)
		{
			break;//超时，可加入超时处理方案
		}
	}
}

void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data)//指定地址写寄存器
{
	I2C_GenerateSTART(I2C2,ENABLE);
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);

	I2C_Send7bitAddress(I2C2,MPU6050_Address,I2C_Direction_Transmitter);
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

	I2C_SendData(I2C2,RegAddress);
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING);
	
	I2C_SendData(I2C2,Data);
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED);
	
	I2C_GenerateSTOP(I2C2,ENABLE);
}

uint8_t Mpu6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	
	I2C_GenerateSTART(I2C2,ENABLE);
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);
	
	I2C_Send7bitAddress(I2C2,MPU6050_Address,I2C_Direction_Transmitter);
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

	I2C_SendData(I2C2,RegAddress);
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING);

    I2C_GenerateSTART(I2C2,ENABLE);
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);
	
	I2C_Send7bitAddress(I2C2,MPU6050_Address,I2C_Direction_Receiver);
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);
	    //for循环套下4个实现多字节
	   I2C_AcknowledgeConfig(I2C2,DISABLE);//应答位
	   I2C_GenerateSTOP(I2C2,ENABLE);//要提前一个数据设置应答位和停止位，不会影响当前数据的传输
	
	   MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED);
	   Data=I2C_ReceiveData(I2C2);
	
	I2C_AcknowledgeConfig(I2C2,ENABLE);
	
	return Data;
}

void MPU6050_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Mode=I2C_Mode_I2C;
	I2C_InitStructure.I2C_ClockSpeed=50000;
	I2C_InitStructure.I2C_DutyCycle=I2C_DutyCycle_2 ;//快速传输时，增加低电平占空比，给数据变化提供足够的时间
	I2C_InitStructure.I2C_Ack=I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_OwnAddress1=0x00;//不做从机时，可写不与从机地址重复的任何地址，否则与上一项有关
	I2C_Init(I2C2,&I2C_InitStructure);
	
	I2C_Cmd(I2C2,ENABLE);
	
	MPU6050_WriteReg(MPU6050_PER_MGMT_1,0x01);
	MPU6050_WriteReg(MPU6050_PER_MGMT_2,0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);
	MPU6050_WriteReg(Mpu6050_CONFIG,0x06);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);
}

void MPU6050_GetData(int16_t *AccX,int16_t *AccY,int16_t *AccZ,
	                 int16_t *GyroX,int16_t *GyroY,int16_t *GyroZ)//最好使用结构体
{
	uint16_t Data_H,Data_L;
	
	Data_H=Mpu6050_ReadReg(MPU6050_ACCEL_XOUT_H);//地址是连续的可以使用连续读取字节，减少代码量
	Data_L=Mpu6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX=(Data_H<<8)|Data_L;
	
	Data_H=Mpu6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	Data_L=Mpu6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY=(Data_H<<8)|Data_L;
	
	Data_H=Mpu6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	Data_L=Mpu6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ=(Data_H<<8)|Data_L;
	
	Data_H=Mpu6050_ReadReg(MPU6050_GYRO_XOUT_H);
	Data_L=Mpu6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX=(Data_H<<8)|Data_L;
	
	Data_H=Mpu6050_ReadReg(MPU6050_GYRO_YOUT_H);
	Data_L=Mpu6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY=(Data_H<<8)|Data_L;
	
	Data_H=Mpu6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	Data_L=Mpu6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ=(Data_H<<8)|Data_L;
}






