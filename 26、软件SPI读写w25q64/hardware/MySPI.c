#include "stm32f10x.h"                  // Device header

void MYSPI_W_SS(uint8_t Bitvalue){
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)Bitvalue);
}
void MYSPI_W_SCK(uint8_t Bitvalue){
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)Bitvalue);
}
void MYSPI_W_MOSI(uint8_t Bitvalue){
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)Bitvalue);
}

uint8_t MYSPI_R_MISO(void){
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
}

void MySPI_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	MYSPI_W_SS(1);
	MYSPI_W_SCK(0);
}

void MYSPI_START(void){
	MYSPI_W_SS(0);
}

void MYSPI_STOP(void){
	MYSPI_W_SS(1);
}
//模式0
uint8_t MYSPI_SWAPBYTE0(uint8_t BYTESEND){
	uint8_t i,BYTERECEIVE=0x00;
	for(i=0;i<8;i++){
		MYSPI_W_MOSI(BYTESEND & (0x80>>i));//掩码
		MYSPI_W_SCK(1);
		if(MYSPI_R_MISO()==1){BYTERECEIVE |=(0x80>>i);}
		MYSPI_W_SCK(0);
	}
	return BYTERECEIVE;
}
//模式1
uint8_t MYSPI_SWAPBYTE1(uint8_t BYTESEND){
	uint8_t i,BYTERECEIVE=0x00;
	for(i=0;i<8;i++){
		MYSPI_W_SCK(1);
		MYSPI_W_MOSI(BYTESEND & (0x80>>i));//掩码
		MYSPI_W_SCK(0);
		if(MYSPI_R_MISO()==1){BYTERECEIVE |=(0x80>>i);}
	}
	return BYTERECEIVE;
}
//模式2，将模式1所有的SCK反转
//模式3，将模式0所有的SCK反转

//uint8_t MYSPI_SWAPBYTE0(uint8_t BYTESEND){
//	uint8_t i;
//	for(i=0;i<8;i++){
//		MYSPI_W_MOSI(BYTESEND & 0x80);//数据移位，效率高。但改变了BYTESEND
//		BYTESEND<<=i;
//		MYSPI_W_SCK(1);
//		if(MYSPI_R_MISO()==1){BYTESEND |=(0x80>>i);}
//		MYSPI_W_SCK(0);
//	}
//	return BYTESEND;
//}






