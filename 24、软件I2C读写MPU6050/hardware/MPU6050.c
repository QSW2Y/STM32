#include "stm32f10x.h"                  // Device header
#include "myi2c.h"
#include "MPU6050_Reg.h"

#define MPU6050_Address   0xD0

void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data)//指定地址写寄存器
{
	MyI2C_start();
	MyI2C_SendByte(MPU6050_Address);//从机地址+读写位
	MyI2C_ReceiveAck();//此处可以用if处理是否应答
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	
	MyI2C_SendByte(Data);//此处可以用for循环进行写多个字节,发送一个数组
	MyI2C_ReceiveAck();
	
	MyI2C_stop();
}

uint8_t Mpu6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	
	MyI2C_start();
	MyI2C_SendByte(MPU6050_Address);//从机地址+读写位
	MyI2C_ReceiveAck();//此处可以用if处理是否应答
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	
	MyI2C_start();
	MyI2C_SendByte(MPU6050_Address|0x01);
	MyI2C_ReceiveAck();
	
	Data=MyI2C_ReceiveByte();
	MyI2C_SendAck(1);//多个字节时，其他位为应答（0），最后一位为非应答（1）
	
	MyI2C_stop();
	
	return Data;
}

void MPU6050_Init(void)
{
	MyI2C_Init();
	MPU6050_WriteReg(MPU6050_PER_MGMT_1,0x01);
	MPU6050_WriteReg(MPU6050_PER_MGMT_2,0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);
	MPU6050_WriteReg(Mpu6050_CONFIG,0x06);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);
}

uint8_t MPU6050_GetID(void)
{
	return Mpu6050_ReadReg(MPU6050_WHO_AM_I);
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




