/*stm32f3xx_it.c*/
#include "stm32f3xx_it.h"
#include "systickms.h"
/*            Cortex-M4 Processor Exceptions Handlers                         */
void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
	while (1)
	{
	}
}

void MemManage_Handler(void)
{
	while (1)
	{
	}
}

void BusFault_Handler(void)
{
	while (1)
	{
	}
}

void UsageFault_Handler(void)
{
	while (1)
	{
	}
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void USER_BUTTON_IRQHANDLER(void)
{
  /* Manage Flags */
  
}



void SysTick_Handler(void)
{
	systickms.cnt1ms();
}

void TIM2_IRQHandler(void)
{
  /* Check whether CC1 interrupt is pending */
  
}

void USART2_IRQHandler(void)
{
}
