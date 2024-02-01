/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

__IO uint32_t uwTick;
uint32_t bkpt_counter = 0;
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  /* Configure Flash prefetch, Instruction cache, Data cache */
#if (INSTRUCTION_CACHE_ENABLE != 0U)
	FLASH->ACR |= FLASH_ACR_ICEN;
#endif /* INSTRUCTION_CACHE_ENABLE */

#if (DATA_CACHE_ENABLE != 0U)
	FLASH->ACR |= FLASH_ACR_DCEN;
#endif /* DATA_CACHE_ENABLE */

#if (PREFETCH_ENABLE != 0U)
	FLASH->ACR |= FLASH_ACR_PRFTEN;
#endif /* PREFETCH_ENABLE */

  /* Set Interrupt Group Priority */
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* Use systick as time base source and configure 1ms tick (default clock after Reset is HSI) */
  InitTick(TICK_INT_PRIORITY);

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  Dummy_GPIO_Init();

  /*SysTick Configuration*/
  SystemCoreClockUpdate();

  /*Generate interrupt for each 10ms*/
  SysTick_Config(SystemCoreClock/100);
  SysTick ->CTRL = 0;
  SysTick ->VAL = 0;
  SysTick ->CTRL = (SysTick_CTRL_TICKINT_Msk
  	     			|SysTick_CTRL_ENABLE_Msk
    				|SysTick_CTRL_CLKSOURCE_Msk);

  while (1)
  {
	  //Infinite loop
  }
}

void SysTick_Handler(void)
{
  uwTick++;
  /*Toggle LEDs for every one second*/
  if(uwTick >= 100){
	  GPIOD->BSRR = (((GPIOD->ODR)&(1<<12))&&(1<<13)) ? 1<<(13+16) : 1<<13;
	  GPIOD->BSRR = (((GPIOD->ODR)&(1<<12))&&(1<<12)) ? 1<<(12+16) : 1<<12;
	  uwTick=0;
	  bkpt_counter++;
	  if (bkpt_counter == 11){
		  bkpt_counter = 0;
	  }
  }
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
	  //Infinite error loop
  }
}




