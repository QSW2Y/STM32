

#include "delay.h"

//微秒
void delay_us(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=10;   
      while(i--) ;    
   }
}


//毫秒
void delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  
      while(i--) ;    
   }
}



