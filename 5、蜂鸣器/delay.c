#include "delay.h"

//Œ¢√ÅE
void delay_us(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=10;   
      while(i--) ;    
   }
}


//∫¡√ÅE
void delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  
      while(i--) ;    
   }
}
