/*systickms.c*/
#include "systickms.h"
#include "main.h"
/**
@file 
@brief структура подсчёта мсек 
*/

systickms_t systickms;
static __IO uint32_t counter1ms; /* Current Counter Value */
static __IO uint8_t flag25ms;
static __IO uint8_t flag50ms;

static void cnt1ms(void)
{
	counter1ms++;
	if( (counter1ms%25) == 0){
		flag25ms=1;
	}
	if( (counter1ms%50) == 0){
		flag50ms=1;
	}
}

static uint8_t readflag25ms(void)
{
	if(flag25ms)
	{
		flag25ms=0;
		return 1;
	}
	else
		return 0;
}

static uint8_t readflag50ms(void)
{
	if(flag50ms)
	{
		flag50ms=0;
		return 1;
	}
	else
		return 0;
}

static uint32_t readcounter(void)
{
	return counter1ms;
}

static void delayms(uint16_t delaytime)
{
	uint32_t cntwait=counter1ms;
	cntwait+=delaytime;
	uint32_t curentcnt=0;
	do 
	{
		volatile int i=0;
		for(i; i<0x200; i++)
		{
			__nop();
		}
		curentcnt=counter1ms;
	}
	while(curentcnt<cntwait);
}

void Init_systickms(void)
{
	SystemCoreClockUpdate();
	if(SystemCoreClock != 72000000) {
		while(1){} /* Initialization Error */
	}
	counter1ms=0;
	flag25ms=0;
	flag50ms=0;
	systickms.cnt1ms=cnt1ms;
	systickms.readcounter=readcounter;
	systickms.delayms = delayms;
	systickms.readflag25ms=readflag25ms;
	systickms.readflag50ms=readflag50ms;
	LL_SYSTICK_EnableIT();
}
