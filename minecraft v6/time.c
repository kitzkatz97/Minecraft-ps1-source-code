//#include <libmath.h>
#include <libapi.h>


#define RCntCNT0		0xf2000000   	/*display pixel*/
#define RCntCNT1		0xf2000001   	/*horizontal sync*/
#define RCntCNT2		0xf2000002   	/*one-eighth of system clock*/
#define RCntCNT3		0xf2000003   	/*vertical sync target value fixed to 1*/

#define RCntIntr		0x1000				/*Interrupt mode*/




int sysclock;
int NewValue;
int clock;
int seconds;
int minutes;
int hours;
int days;
int years;
int CounterMaxValue = 240; /*This means this counter resets every 240 HBlanks*/

void time() {
	
	sysclock = GetRCnt(RCntCNT1);
	
    if(sysclock = 240)
	{
	clock ++;
	}
	
	seconds = clock/60;
	
	if(seconds   >= 60)
	{
	 seconds = 0;
	 clock   = 0;
	 minutes ++;
	 
	}
	
	if(minutes   >= 60)
	{
	 minutes = 0;
	 hours   ++;
	}
	if(hours     >= 24)
	{
	 hours   = 0;
	 days    ++;
	}
	
	//seconds = clock/60;
	
    
	/*
    FntPrint("It took %d HBlanks to execute DoSomething", NewValue);
	FntPrint("\n'time':%d", sysclock);
	FntPrint("\nseconds:%d", seconds);
	FntPrint("\nminutes:%d", minutes);
	FntPrint("\nhours:%d",     hours);
	FntPrint("\ndays:%d",       days);
	*/
}
