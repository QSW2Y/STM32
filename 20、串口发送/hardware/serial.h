#ifndef __SERIAL_H
#define __SERIAL_H
#include "stm32f10x.h"                  // Device header

#include <stdio.h>

void serial_Init(void);
void serial_Sendbyte(uint8_t Byte);
void serial_SendArray(uint8_t *Array,uint16_t Length);
void serial_SendString(char *String);
uint32_t serial_pow(uint32_t x,uint32_t y);
void serial_SendNumber(uint32_t Number,uint16_t Length);
void serial_sprintf(char *format, ...);

	

#endif

