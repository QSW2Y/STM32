#ifndef __MYRTC_H
#define __MYRTC_H

#include "stm32f10x.h"                  // Device header


extern uint16_t MYRTC_Time[];

void MYRTC_Init(void);
void MyRTC_Settime(void);
void MyRTC_Readtime(void);

#endif

