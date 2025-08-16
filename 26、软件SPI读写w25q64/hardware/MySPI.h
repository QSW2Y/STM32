#ifndef __MYSPI_H
#define __MYSPI_H

#include "stm32f10x.h"                  // Device header

void MySPI_Init(void);
void MYSPI_START(void);
void MYSPI_STOP(void);
uint8_t MYSPI_SWAPBYTE0(uint8_t BYTESEND);

#endif
