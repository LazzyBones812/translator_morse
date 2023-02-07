/*main.c*/
#include "main.h"
#include <stdio.h>
#include "systickms.h" 
#include "display.h"
#include "keypad.h"
#include "AlphabetMorse.h"
 
void SystemClock_Config(void);

int main(void)
{
	SystemClock_Config();
	Init_keypad();
	Init_systickms();
	Init_display();
	speaker_init();
	morse_start();
	morse_init_buttons();
	
	while (1)
	{
		if(systickms.readflag25ms())
		{
			uint32_t keycode;
			keycode=keypad_poll();
			if(keycode) 
				for(uint16_t i=0;i<16;i++)
					if(keycode&(1<<i))
						morse_input(i + 1);
		}
	}
}

void SystemClock_Config(void)
{
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_2); 
	LL_RCC_HSE_Enable(); 
	while(LL_RCC_HSE_IsReady() != 1) 
	{
	};
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);
	LL_RCC_PLL_Enable();
	while(LL_RCC_PLL_IsReady() != 1)
	{
	};
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
	{
	};
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1); 
	LL_Init1msTick(72000000);
	LL_SetSystemCoreClock(72000000);
}
