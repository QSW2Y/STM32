#include "stm32f10x.h"                  // Device header
#include "delay.h"

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x02000000+((addr & 0x00FFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C   
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C   
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C   
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C   
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C   
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C      
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C      
  
#define GPIOA_IDR_Addr    (GPIOA_BASE+8)  //0x40010808   
#define GPIOB_IDR_Addr    (GPIOB_BASE+8)  //0x40010C08   
#define GPIOC_IDR_Addr    (GPIOC_BASE+8)  //0x40011008   
#define GPIOD_IDR_Addr    (GPIOD_BASE+8)  //0x40011408   
#define GPIOE_IDR_Addr    (GPIOE_BASE+8)  //0x40011808   
#define GPIOF_IDR_Addr    (GPIOF_BASE+8)  //0x40011A08   
#define GPIOG_IDR_Addr    (GPIOG_BASE+8)  //0x40011E08 


#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n) 

void LED_GPIO_Config(void)
{		
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); 									   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_1;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
		GPIO_Init(GPIOB, &GPIO_InitStructure);		  

	    GPIO_SetBits(GPIOB, GPIO_Pin_0); 
        GPIO_SetBits(GPIOB, GPIO_Pin_5); 
        GPIO_SetBits(GPIOB, GPIO_Pin_1); 
}

int main(void)
{	
	LED_GPIO_Config();
	
	while( 1 )
	{
		// PB0 = 0,µãÁÁLED
		PBout(0)= 0;		
		delay_ms(500);
		
		// PB0 = 1,Ï¨ÃðLED		
		PBout(0)= 1;
		delay_ms(500);		
    
        // PB1 = 0,µãÁÁLED
		PBout(1)= 0;		
		delay_ms(500);
		
		// PB1 = 1,Ï¨ÃðLED		
		PBout(1)= 1;
		delay_ms(500);	
    
        // PB5 = 0,µãÁÁLED
		PBout(5)= 0;		
		delay_ms(500);
		
		// PB5 = 1,Ï¨ÃðLED		
		PBout(5)= 1;
		delay_ms(500);	
	}
}

//void SOFT_Delay(__IO uint32_t nCount)	
//{
//	for(; nCount != 0; nCount--);
//}


