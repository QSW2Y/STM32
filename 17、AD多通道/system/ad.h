#ifndef __AD_H
#define __AD_H
#include "stm32f10x.h"                  // Device header


uint16_t ad_Getvalue(uint8_t ADC_Channel);
void adInit(void);


#endif
