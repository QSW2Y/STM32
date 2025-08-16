#ifndef __AD_H
#define __AD_H
#include "stm32f10x.h"                  // Device header


uint16_t ad_Getvalue(void);
void adInit(void);
extern uint16_t AD_Value[4];

#endif
