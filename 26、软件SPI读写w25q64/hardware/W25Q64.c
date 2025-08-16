#include "stm32f10x.h"                  // Device header
#include "MySPI.h"


void W25Q64_Init(void){
	MySPI_Init();
}

//参考手册指令集，拼接完整时序

void W25Q64_ReadID(uint8_t *MID,uint16_t *DID){
	MYSPI_START();
	MYSPI_SWAPBYTE0(0x9F);
	*MID=MYSPI_SWAPBYTE0(0xFF);
	*DID=MYSPI_SWAPBYTE0(0xFF);
	*DID<<=8;
	*DID |= MYSPI_SWAPBYTE0(0xFF);
	MYSPI_STOP();
}
	
void W25Q64_WriteENABLE(void){
	MYSPI_START();
	MYSPI_SWAPBYTE0(0x06);
	MYSPI_STOP();
}

void W25Q64_WaitBusy(void){
	uint32_t Timeout;
	
	MYSPI_START();
	MYSPI_SWAPBYTE0(0x05);
	Timeout=100000;
	while((MYSPI_SWAPBYTE0(0xFF)&0x01)==0x01){
		Timeout --;
		if(Timeout==0){
			break;
		}
	}
	MYSPI_STOP();
}
//页编程（写）不超过256
void W25Q64_PageProgram(uint32_t Address,uint8_t *DataArray,uint16_t Count){
	uint16_t i;
	
	W25Q64_WriteENABLE();
	
	MYSPI_START();
	MYSPI_SWAPBYTE0(0x02);
	MYSPI_SWAPBYTE0(Address>>16);
	MYSPI_SWAPBYTE0(Address>>8);
	MYSPI_SWAPBYTE0(Address);
	for (i=0;i<Count;i++){
		MYSPI_SWAPBYTE0(DataArray[i]);
	}
	MYSPI_STOP();
	W25Q64_WaitBusy();
}
//扇区擦除
void W25Q64_SectorErase(uint32_t Address){
	W25Q64_WriteENABLE();
	
	MYSPI_START();
	MYSPI_SWAPBYTE0(0x20);
	MYSPI_SWAPBYTE0(Address>>16);
	MYSPI_SWAPBYTE0(Address>>8);
	MYSPI_SWAPBYTE0(Address);
	MYSPI_STOP();
	W25Q64_WaitBusy();//事后等待
}

void W25Q64_ReadData(uint32_t Address,uint8_t *DataArray,uint32_t Count){
	uint32_t i;
	
	MYSPI_START();
	MYSPI_SWAPBYTE0(0x03);
	MYSPI_SWAPBYTE0(Address>>16);
	MYSPI_SWAPBYTE0(Address>>8);
	MYSPI_SWAPBYTE0(Address);
	for(i=0;i<Count;i++){
		DataArray[i]= MYSPI_SWAPBYTE0(0xFF);
	}
	MYSPI_STOP();
}

//事前等待，读写都要等待。事后等待只有写需要。



