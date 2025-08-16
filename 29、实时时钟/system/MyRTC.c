#include "stm32f10x.h"                  // Device header
#include <time.h>            //内置库一般用<>，用引号也行

uint16_t MYRTC_Time[]={2023,1,1,23,59,55};
void MyRTC_Settime(void);

void MYRTC_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);

    PWR_BackupAccessCmd(ENABLE);
	//在备用电源没断电的情况下不会重新初始化
	if(BKP_ReadBackupRegister(BKP_DR1)!=0xA5A5){
		RCC_LSEConfig(RCC_LSE_ON);
	    while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)!=SET);//若不起震可用LSI
	
	    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	    RCC_RTCCLKCmd(ENABLE);
	
	    RTC_WaitForSynchro();
	    RTC_WaitForLastTask();
	
	    RTC_SetPrescaler(32768-1);//LSI为4000
	    RTC_WaitForLastTask();
	
	    //RTC_SetCounter(1672588795);//不设置就是默认时间（时间戳）
        MyRTC_Settime();
		
		BKP_WriteBackupRegister(BKP_DR1,0xA5A5);
	}
	else{
		RTC_WaitForSynchro();
        RTC_WaitForLastTask();
	}		
}

void MyRTC_Settime(void){
	time_t time_cnt;
	struct tm time_date;
	
	time_date.tm_year=MYRTC_Time[0]-1900;
	time_date.tm_mon=MYRTC_Time[1]-1;
	time_date.tm_mday=MYRTC_Time[2];
	time_date.tm_hour=MYRTC_Time[3];
	time_date.tm_min=MYRTC_Time[4];
	time_date.tm_sec=MYRTC_Time[5];
	
	time_cnt=mktime(&time_date)-8*60*60;
	
	RTC_SetCounter(time_cnt);
	RTC_WaitForLastTask();
}
	
void MyRTC_Readtime(void){
	time_t time_cnt;
	struct tm time_date;
	
	time_cnt=RTC_GetCounter()+8*60*60;//加上时区偏移的秒数
	
	time_date=*localtime(&time_cnt);
	
	MYRTC_Time[0]=time_date.tm_year+1900;//可使用结构体完成
	MYRTC_Time[1]=time_date.tm_mon+1;
	MYRTC_Time[2]=time_date.tm_mday;
	MYRTC_Time[3]=time_date.tm_hour;
	MYRTC_Time[4]=time_date.tm_min;
	MYRTC_Time[5]=time_date.tm_sec;
}













