/*
 * rcc.c
 *
 *  Created on: Dec 20, 2023
 *      Author: Lia
 */

#include "rcc.h"

static uint32_t uwTickPrio   = (1UL << __NVIC_PRIO_BITS); /* Invalid PRIO */
static uint32_t uwTickFreq = 1U;

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* Configure the main internal regulator output voltage*/
  RCC_PWR_CLK_ENABLE();
  PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Initializes the RCC Oscillators according to the specified parameters in the RCC_OscInitTypeDef structure. */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;

  __HAL_RCC_HSE_CONFIG(RCC_OscInitStruct.HSEState);
  if((RCC_OscInitStruct.HSEState) != RCC_HSE_OFF)
  {
	  while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == RESET)
          {
          }
  	  }
  else{
      /* Wait till HSE is bypassed or disabled */
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != RESET)
      {
      }

/*-------------------------------- PLL Configuration -----------------------*/
      uint32_t pll_config;
/* Check the parameters */
if ((RCC_OscInitStruct.PLL.PLLState) != RCC_PLL_NONE)
{
  /* Check if the PLL is used as system clock or not */
  if(__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_CFGR_SWS_PLL)
  {
    if((RCC_OscInitStruct.PLL.PLLState) == RCC_PLL_ON)
    {
      /* Disable the main PLL. */
      __HAL_RCC_PLL_DISABLE();

      /* Wait till PLL is disabled */
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) != RESET)
      {
      }

      /* Configure the main PLL clock source, multiplication and division factors. */
      WRITE_REG(RCC->PLLCFGR, (RCC_OscInitStruct.PLL.PLLSource                                            | \
                               RCC_OscInitStruct.PLL.PLLM                                                 | \
                               (RCC_OscInitStruct.PLL.PLLN << RCC_PLLCFGR_PLLN_Pos)             | \
                               (((RCC_OscInitStruct.PLL.PLLP >> 1U) - 1U) << RCC_PLLCFGR_PLLP_Pos) | \
                               (RCC_OscInitStruct.PLL.PLLQ << RCC_PLLCFGR_PLLQ_Pos)));
      /* Enable the main PLL. */
      __HAL_RCC_PLL_ENABLE();

      /* Wait till PLL is ready */
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) == RESET)
      {
      }
    }
    else
    {
      /* Disable the main PLL. */
      __HAL_RCC_PLL_DISABLE();

      /* Wait till PLL is disabled */
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) != RESET)
      {
      }
    }
  }
  else
  {
    /* Check if there is a request to disable the PLL used as System clock source */
    if((RCC_OscInitStruct.PLL.PLLState) != RCC_PLL_OFF)
      /* Do not return HAL_ERROR if request repeats the current configuration */
      pll_config = RCC->PLLCFGR;
#if defined (RCC_PLLCFGR_PLLR)
      if (((RCC_OscInitStruct->PLL.PLLState) == RCC_PLL_OFF) ||
          (READ_BIT(pll_config, RCC_PLLCFGR_PLLSRC) != RCC_OscInitStruct->PLL.PLLSource) ||
          (READ_BIT(pll_config, RCC_PLLCFGR_PLLM) != (RCC_OscInitStruct->PLL.PLLM) << RCC_PLLCFGR_PLLM_Pos) ||
          (READ_BIT(pll_config, RCC_PLLCFGR_PLLN) != (RCC_OscInitStruct->PLL.PLLN) << RCC_PLLCFGR_PLLN_Pos) ||
          (READ_BIT(pll_config, RCC_PLLCFGR_PLLP) != (((RCC_OscInitStruct->PLL.PLLP >> 1U) - 1U)) << RCC_PLLCFGR_PLLP_Pos) ||
          (READ_BIT(pll_config, RCC_PLLCFGR_PLLQ) != (RCC_OscInitStruct->PLL.PLLQ << RCC_PLLCFGR_PLLQ_Pos)) ||
          (READ_BIT(pll_config, RCC_PLLCFGR_PLLR) != (RCC_OscInitStruct->PLL.PLLR << RCC_PLLCFGR_PLLR_Pos)))
#else
      if (((RCC_OscInitStruct.PLL.PLLState) == RCC_PLL_OFF) ||
          (READ_BIT(pll_config, RCC_PLLCFGR_PLLSRC) != RCC_OscInitStruct.PLL.PLLSource) ||
          (READ_BIT(pll_config, RCC_PLLCFGR_PLLM) != (RCC_OscInitStruct.PLL.PLLM) << RCC_PLLCFGR_PLLM_Pos) ||
          (READ_BIT(pll_config, RCC_PLLCFGR_PLLN) != (RCC_OscInitStruct.PLL.PLLN) << RCC_PLLCFGR_PLLN_Pos) ||
          (READ_BIT(pll_config, RCC_PLLCFGR_PLLP) != (((RCC_OscInitStruct.PLL.PLLP >> 1U) - 1U)) << RCC_PLLCFGR_PLLP_Pos) ||
          (READ_BIT(pll_config, RCC_PLLCFGR_PLLQ) != (RCC_OscInitStruct.PLL.PLLQ << RCC_PLLCFGR_PLLQ_Pos)))
#endif
      {
      }
    }
  }
}

  /* Initializes the CPU, AHB and APB buses clocks*/
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  uint32_t FLatency = FLASH_LATENCY_5;
    /* To correctly read data from FLASH memory, the number of wait states (LATENCY)
      must be correctly programmed according to the frequency of the CPU clock
      (HCLK) and the supply voltage of the device. */

    /* Increasing the number of wait states because of higher CPU frequency */
    if(FLatency > __HAL_FLASH_GET_LATENCY())
    {
      /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
      __HAL_FLASH_SET_LATENCY(FLatency);
    }

    /*-------------------------- HCLK Configuration --------------------------*/
    if(((RCC_ClkInitStruct.ClockType) & RCC_CLOCKTYPE_HCLK) == RCC_CLOCKTYPE_HCLK)
    {
      /* Set the highest APBx dividers in order to ensure that we do not go through
         a non-spec phase whatever we decrease or increase HCLK. */
      if(((RCC_ClkInitStruct.ClockType) & RCC_CLOCKTYPE_PCLK1) == RCC_CLOCKTYPE_PCLK1)
      {
        MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV16);
      }

      if(((RCC_ClkInitStruct.ClockType) & RCC_CLOCKTYPE_PCLK2) == RCC_CLOCKTYPE_PCLK2)
      {
        MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, (RCC_CFGR_PPRE1_DIV16 << 3));
      }

      MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_ClkInitStruct.AHBCLKDivider);
    }

    /*------------------------- SYSCLK Configuration ---------------------------*/
    if(((RCC_ClkInitStruct.ClockType) & RCC_CLOCKTYPE_SYSCLK) == RCC_CLOCKTYPE_SYSCLK)
    {
      /* HSE is selected as System Clock Source */
      if(RCC_ClkInitStruct.SYSCLKSource == RCC_SYSCLKSOURCE_HSE)
      {
      }

      __HAL_RCC_SYSCLK_CONFIG(RCC_ClkInitStruct.SYSCLKSource);
    }

    /* Decreasing the number of wait states because of lower CPU frequency */
    if(FLatency < __HAL_FLASH_GET_LATENCY())
    {
       /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
      __HAL_FLASH_SET_LATENCY(FLatency);

    }

    /*-------------------------- PCLK1 Configuration ---------------------------*/
    if(((RCC_ClkInitStruct.ClockType) & RCC_CLOCKTYPE_PCLK1) == RCC_CLOCKTYPE_PCLK1)
    {
      MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_ClkInitStruct.APB1CLKDivider);
    }

    /*-------------------------- PCLK2 Configuration ---------------------------*/
    if(((RCC_ClkInitStruct.ClockType) & RCC_CLOCKTYPE_PCLK2) == RCC_CLOCKTYPE_PCLK2)
    {
      MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, ((RCC_ClkInitStruct.APB2CLKDivider) << 3U));
    }

    /* Update the SystemCoreClock global variable */
    SystemCoreClock = RCC_GetSysClockFreq() >> AHBPrescTable[(RCC->CFGR & RCC_CFGR_HPRE)>> RCC_CFGR_HPRE_Pos];

    /* Configure the source of time base considering new system clocks settings */
    InitTick (uwTickPrio);

  }


void InitTick(uint32_t TickPriority)
{
  /* Configure the SysTick to have interrupt in 1ms time basis*/
  SysTick_Config(SystemCoreClock / (1000U / uwTickFreq));

  /* Configure the SysTick IRQ priority */
  if (TickPriority < (1UL << __NVIC_PRIO_BITS))
  {
	NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), TickPriority, 0U));
    uwTickPrio = TickPriority;
  }
}

uint32_t RCC_GetSysClockFreq(void)
{
  uint32_t pllm = 0U, pllvco = 0U, pllp = 0U;
  uint32_t sysclockfreq = 0U;

  /* Get SYSCLK source -------------------------------------------------------*/
  switch (RCC->CFGR & RCC_CFGR_SWS)
  {
    case RCC_CFGR_SWS_HSI:  /* HSI used as system clock source */
    {
      sysclockfreq = HSI_VALUE;
       break;
    }
    case RCC_CFGR_SWS_HSE:  /* HSE used as system clock  source */
    {
      sysclockfreq = HSE_VALUE;
      break;
    }
    case RCC_CFGR_SWS_PLL:  /* PLL used as system clock  source */
    {
      /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLLM) * PLLN
      SYSCLK = PLL_VCO / PLLP */
      pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
      if(__HAL_RCC_GET_PLL_OSCSOURCE() != RCC_PLLSOURCE_HSI)
      {
        /* HSE used as PLL clock source */
        pllvco = (uint32_t) ((((uint64_t) HSE_VALUE * ((uint64_t) ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos)))) / (uint64_t)pllm);
      }
      else
      {
        /* HSI used as PLL clock source */
        pllvco = (uint32_t) ((((uint64_t) HSI_VALUE * ((uint64_t) ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos)))) / (uint64_t)pllm);
      }
      pllp = ((((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> RCC_PLLCFGR_PLLP_Pos) + 1U) *2U);

      sysclockfreq = pllvco/pllp;
      break;
    }
    default:
    {
      sysclockfreq = HSI_VALUE;
      break;
    }
  }
  return sysclockfreq;
}
