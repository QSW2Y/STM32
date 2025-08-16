#include "stm32f10x.h"                  // Device header

uint16_t AD_Value[4];

void adInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//使用软件触发
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel=4;
	ADC_InitStructure.ADC_ScanConvMode=ENABLE;
	ADC_Init(ADC1,&ADC_InitStructure);	
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)&ADC1->DR;
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//选择地址是否自增
	DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)&AD_Value;
	DMA_InitStructure.DMA_MemoryDataSize=DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
  	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize=4;
	DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;
    DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;
	DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1)==SET);
	//一直为1则校准未完成，校准完成后自动硬件清零，读到0后知校准完成，跳出循环
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1)==SET);
	//效果同上，等待校准是否完成
	//ADC_SoftwareStartConvCmd(ADC1,ENABLE);//采用连续扫描时在这触发一次即可
	
	//ADC_SoftwareStartConvCmd(ADC1,ENABLE);//ADC使用连续模式，DMA也开启循环模式直接读AD_Value可以得到对应值，后面的ad_Getvalue函数就不用要了
}

uint16_t ad_Getvalue(void)
{
	DMA_Cmd(DMA1_Channel2,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel2,4);
	DMA_Cmd(DMA1_Channel2,ENABLE);
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
	while(DMA_GetFlagStatus(DMA1_FLAG_GL2)==RESET);//等待转运完成
	DMA_ClearFlag(DMA1_FLAG_GL2);
}

//uint16_t ad_Getvalue(void)
//{
//	return ADC_GetConversionValue(ADC1);
//}
//连续模式下数据寄存器会更新值，不用读取



