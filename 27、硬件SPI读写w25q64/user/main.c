#include "stm32f10x.h"                  // Device header
#include "W25Q64.h"

uint8_t MID;
uint16_t DID;

uint8_t ArrayWrite[]={0x01,0x02,0x03,0x04};
uint8_t ArrayRead[4];

int main(void)
{
	W25Q64_Init();
	W25Q64_ReadID(&MID,&DID);
	//写入前必须擦除，不然数据会出错
	W25Q64_SectorErase(0x000000);//前三个一样就是同一扇区，一般使用起始地址，意义明确，擦除后全是FF
	W25Q64_PageProgram(0x000000,ArrayWrite,4);//写入数据不能跨页，读取可以
	
	W25Q64_ReadData(0x000000,ArrayRead,4);//数据掉电不丢失
	
	while(1)
	{
		
    }
}

//Flash只能1写0，不能0写1




