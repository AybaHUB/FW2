/**
  ******************************************************************************
  * @file    stm32u5xx_hal.c
  * @author  GPM Application Team
  * @brief   HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of HAL module:
  *           + Initialization and de-initialization functions
  *           + HAL tick operation functions
  *           + HAL driver and device identification functions
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021-2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"
#include "stm32u5xx_ll_bus.h"

/** @addtogroup STM32U5XX_HAL_Driver
  * @{
  */

/** @addtogroup HAL
  * @{
# How to use the HAL module driver

## The HAL driver can be used as follows:

- Initialize the HAL generic features

## Configuration inside the HAL driver

Config defines                  | Description           | Default value      | Note
------------------------------- | --------------------- | ------------------ | -----------------------------------------
USE_HAL_MODULE                  | from hal_conf.h       | 1                  | When set, HAL module is enabled
USE_ASSERT_DBG_PARAM            | from PreProcessor env | None               | When defined, enable the params assert
USE_EXTERNAL_ENV                | from PreProcessor env | Defined            | Enable external oscillators
USE_HAL_CHECK_PARAM             | from hal_conf.h       | 0                  | When set, parameters are checked in
                                |                       |                    | runtime
TICK_INT_PRIORITY               | from hal_conf.h       | bitfield range max | HAL tick interrupt priority
                                |                       |                    | (lowest by default)
USE_HAL_PREFETCH                | from hal_conf.h       | 1                  | When set, prefetch is enabled
  */

#if defined(USE_HAL_MODULE) && (USE_HAL_MODULE == 1)

/* Private constants ---------------------------------------------------------*/
/** @defgroup HAL_Private_Constants HAL Private Constants
  * @{
  */
/*! Reset all AHB1_GRP1 peripherals (except system ones needed for code execution) */
#if defined(LL_AHB1_GRP1_PERIPH_DCACHE2)
#define AHB1_GRP1_PERIPH_RESET (LL_AHB1_GRP1_PERIPH_ALL & ~(LL_AHB1_GRP1_PERIPH_SRAM1 \
                                                            | LL_AHB1_GRP1_PERIPH_DCACHE1 \
                                                            | LL_AHB1_GRP1_PERIPH_DCACHE2 \
                                                            | LL_AHB1_GRP1_PERIPH_BKPSRAM \
                                                            | LL_AHB1_GRP1_PERIPH_FLASH))
#else
#define AHB1_GRP1_PERIPH_RESET (LL_AHB1_GRP1_PERIPH_ALL & ~(LL_AHB1_GRP1_PERIPH_SRAM1 \
                                                            | LL_AHB1_GRP1_PERIPH_DCACHE1 \
                                                            | LL_AHB1_GRP1_PERIPH_BKPSRAM \
                                                            | LL_AHB1_GRP1_PERIPH_FLASH))
#endif /* defined(LL_AHB1_GRP1_PERIPH_DCACHE2) */

/*! Reset all AHB2_GRP1 peripherals (except system ones needed for code execution) */
#if defined(LL_AHB2_GRP1_PERIPH_SRAM3)
#define AHB2_GRP1_PERIPH_RESET (LL_AHB2_GRP1_PERIPH_ALL & ~(LL_AHB2_GRP1_PERIPH_SRAM2 \
                                                            | LL_AHB2_GRP1_PERIPH_SRAM3))
#else
#define AHB2_GRP1_PERIPH_RESET (LL_AHB2_GRP1_PERIPH_ALL & ~(LL_AHB2_GRP1_PERIPH_SRAM2))
#endif /* defined(LL_AHB2_GRP1_PERIPH_SRAM3) */

/*! Reset all AHB2_GRP2 peripherals (except system ones needed for code execution) */
#if defined(LL_AHB2_GRP2_PERIPH_SRAM5) && defined(LL_AHB2_GRP2_PERIPH_SRAM6)
#define AHB2_GRP2_PERIPH_RESET (LL_AHB2_GRP2_PERIPH_ALL & ~(LL_AHB2_GRP2_PERIPH_SRAM5 \
                                                            | LL_AHB2_GRP2_PERIPH_SRAM6))
#elif defined(LL_AHB2_GRP2_PERIPH_SRAM5)
#define AHB2_GRP2_PERIPH_RESET (LL_AHB2_GRP2_PERIPH_ALL & ~(LL_AHB2_GRP2_PERIPH_SRAM5))
#else
#define AHB2_GRP2_PERIPH_RESET (LL_AHB2_GRP2_PERIPH_ALL)
#endif /* defined(LL_AHB2_GRP2_PERIPH_SRAM5) && defined(LL_AHB2_GRP2_PERIPH_SRAM6) */

/*! Reset all AHB3_GRP1 peripherals (except system ones needed for code execution) */
#define AHB3_GRP1_PERIPH_RESET (LL_AHB3_GRP1_PERIPH_ALL & ~(LL_AHB3_GRP1_PERIPH_SRAM4 \
                                                            | LL_AHB3_GRP1_PERIPH_GTZC2))

/*! Reset all APB1_GRP1 peripherals (except system ones needed for code execution) */
#define APB1_GRP1_PERIPH_RESET (LL_APB1_GRP1_PERIPH_ALL &~ LL_APB1_GRP1_PERIPH_WWDG)
/*! Reset all APB1_GRP2 peripherals (except system ones needed for code execution) */
#define APB1_GRP2_PERIPH_RESET (LL_APB1_GRP2_PERIPH_ALL)
/*! Reset all APB2_GRP1 peripherals (except system ones needed for code execution) */
#define APB2_GRP1_PERIPH_RESET (LL_APB2_GRP1_PERIPH_ALL)
/*! Reset all APB3_GRP1 peripherals (except system ones needed for code execution) */
#define APB3_GRP1_PERIPH_RESET (LL_APB3_GRP1_PERIPH_ALL)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup HAL_Private_Macros HAL Private Macros
  * @{
  */

/*! Check HAL tick frequency value */
#define IS_TICK_FREQ(freq) (((freq) == HAL_TICK_FREQ_10HZ)  || \
                            ((freq) == HAL_TICK_FREQ_100HZ) || \
                            ((freq) == HAL_TICK_FREQ_1KHZ))

/*! Check HAL tick priority value */
#define IS_TICK_PRIO(prio) ((prio) <= ((1UL << __NVIC_PRIO_BITS) - 1UL))

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @defgroup HAL_Exported_Variables_init HAL Exported Variables (@ref HAL_Exported_Variables) initialization
  * @{
  */
volatile uint32_t uwTick;
uint32_t uwTickPrio = ((1UL << __NVIC_PRIO_BITS) - 1UL); /* Initial value: low priority */
hal_tick_freq_t uwTickFreq = HAL_TICK_FREQ_DEFAULT;  /* 1KHz */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup HAL_Exported_Functions
  * @{
  */

/** @addtogroup HAL_Exported_Functions_Group1
  * @{
  This subsection provides a set of functions allowing to initialize and deinitialize the HAL module:

  - Function HAL_Init() must be called at the beginning of program start to make device ready
    for other HAL modules operation.
    It configures:
    - HAL time base with default parameters: HAL tick from SysTick, interruption enable, period 1ms
    - System generic features (NVIC priority grouping configuration, ...)

  - Function HAL_DeInit() can be called (optional) to revert HAL configuration.

  - Function HAL_InitTick() is called by HAL_Init() with HAL default parameters and by HAL RCC when system clock
    is updated.
    User can call it from application with different parameters.
    User can override it (function declared as __WEAK) to use HAL tick with different clock source (timer, RTC, ...)
  */

/**
  * @brief  Initialize the HAL module and make device ready to use the various HAL modules.
  * @note   HAL_Init() function is called at the beginning of program after reset and before
  *         the clock configuration.
  * @note   In the default implementation the System Timer (Systick) is used as source of time base.
  *         The Systick configuration is based on MSI clock, as MSI is the clock
  *         used after a system Reset and the NVIC configuration is set to Priority group 4.
  *         Once done, time base tick starts incrementing: the tick variable counter is incremented
  *         each 1ms in the SysTick_Handler() interrupt handler.
  * @retval HAL_OK HAL correctly initialized
  * @retval HAL_ERROR Error occurred during HAL initialization process (refer to HAL services called in this function)
  */
hal_status_t HAL_Init(void)
{
#if defined(USE_HAL_PREFETCH) && (USE_HAL_PREFETCH == 1)
  /* Configure Flash prefetch */
  LL_FLASH_EnablePrefetch(FLASH1);
#endif /* USE_HAL_PREFETCH */

  /* Update the SystemCoreClock global variable */
  SystemCoreClock = HAL_RCC_GetSysClockFreq() >> AHBPrescTable[LL_RCC_GetAHBPrescaler()];

  /* Set SysTick clock source to HCLK (CPU internal free running clock) */
  HAL_CORTEX_SYSTICK_SetClockSrc(HAL_CORTEX_SYSTICK_CLKSOURCE_HCLK);

  /* Set Interrupt Group Priority */
  HAL_CORTEX_NVIC_SetPriorityGrouping(HAL_CORTEX_NVIC_PRIORITY_GROUP_4);

  /* Use SysTick as time base source and configure 1ms tick */
  if (HAL_InitTick(HAL_TICK_FREQ_DEFAULT, TICK_INT_PRIORITY) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  DeInitialize the HAL module.
  * @note   Call of this function is optional
  * @retval HAL_OK
  */
hal_status_t HAL_DeInit(void)
{
  /* Reset all peripherals (except system ones needed for code execution) */
  LL_AHB1_GRP1_ForceReset(AHB1_GRP1_PERIPH_RESET);
  LL_AHB2_GRP1_ForceReset(AHB2_GRP1_PERIPH_RESET);
  LL_AHB2_GRP2_ForceReset(AHB2_GRP2_PERIPH_RESET);
  LL_AHB3_GRP1_ForceReset(AHB3_GRP1_PERIPH_RESET);
  LL_APB1_GRP1_ForceReset(APB1_GRP1_PERIPH_RESET);
  LL_APB1_GRP2_ForceReset(APB1_GRP2_PERIPH_RESET);
  LL_APB2_GRP1_ForceReset(APB2_GRP1_PERIPH_RESET);
  LL_APB3_GRP1_ForceReset(APB3_GRP1_PERIPH_RESET);

  LL_AHB1_GRP1_ReleaseReset(AHB1_GRP1_PERIPH_RESET);
  LL_AHB2_GRP1_ReleaseReset(AHB2_GRP1_PERIPH_RESET);
  LL_AHB2_GRP2_ReleaseReset(AHB2_GRP2_PERIPH_RESET);
  LL_AHB3_GRP1_ReleaseReset(AHB3_GRP1_PERIPH_RESET);
  LL_APB1_GRP1_ReleaseReset(APB1_GRP1_PERIPH_RESET);
  LL_APB1_GRP2_ReleaseReset(APB1_GRP2_PERIPH_RESET);
  LL_APB2_GRP1_ReleaseReset(APB2_GRP1_PERIPH_RESET);
  LL_APB3_GRP1_ReleaseReset(APB3_GRP1_PERIPH_RESET);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief This function configures the time base frequency and interruption priority.
  * @warning HAL tick is updated from interrupts at regular time intervals.
  *        Care must be taken if HAL_Delay() is called from a peripheral interruption process:
  *        the tick interrupt line must have higher priority (numerically lower) than the peripheral interrupt,
  *        otherwise the caller interruption process will be blocked.
  * @note  This function is called at the beginning of program by HAL_Init()
  *        or at any time when system core clock is modified (for instance, called by HAL RCC driver when needed).
  * @note  This function is declared as __WEAK to be overridden in case of other
  *        implementations in user file.
  * @param tick_freq  Tick frequency (to keep current value, use global variable @ref uwTickFreq)
  * @param tick_priority Tick interrupt priority (to keep current value, use global variable @ref uwTickPrio)
  * @retval HAL_OK HAL time base correctly configured
  * @retval HAL_ERROR Error occurred during HAL time base configuration (refer to HAL services called in this function)
  * @retval HAL_INVALID_PARAM Input parameter(s) not in expected range
  */
__WEAK hal_status_t HAL_InitTick(hal_tick_freq_t tick_freq, uint32_t tick_priority)
{
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(IS_TICK_FREQ(tick_freq));
  ASSERT_DBG_PARAM(IS_TICK_PRIO(tick_priority));

  /* Check uwTickFreq for MisraC 2012 (despite variable of enum type that does not take value zero) */
  if ((uint32_t)uwTickFreq != 0U)
  {
    /* Configure SysTick frequency */
    /* Note: Value "1000" to convert value to Hz */
    if (HAL_CORTEX_SYSTICK_SetFreq(1000UL / (uint32_t)tick_freq) == HAL_OK)
    {
      uwTickFreq = tick_freq;

      /* Configure SysTick interruption priority */
      HAL_CORTEX_NVIC_SetPriority(SysTick_IRQn, (hal_cortex_nvic_preemp_priority_t)tick_priority,
                                  (hal_cortex_nvic_sub_priority_t)0U);
      uwTickPrio = tick_priority;
    }
    else
    {
      status = HAL_ERROR;
    }
  }
  else
  {
    status = HAL_ERROR;
  }

  /* Return function status */
  return status;
}

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group2
  * @{
  This subsection provides a set of functions allowing to control and use HAL tick.

  @warning HAL tick is updated from interrupts at regular time intervals.
           Care must be taken if HAL_Delay() is called from a peripheral interruption process:
           the tick interrupt line must have higher priority (numerically lower) than the peripheral interrupt,
           otherwise the caller interruption process will be blocked.
  */

/**
  * @brief This function is called to increment a global variable @ref uwTick
  *        used as application time base.
  * @note In the default implementation, this function is called within Systick ISR.
  * @note This function is declared as __WEAK to be overridden in case of other
  *       implementations in user file.
  */
__WEAK void HAL_IncTick(void)
{
  uwTick += (uint32_t)uwTickFreq;
}

/**
  * @brief Provides a tick value in millisecond.
  * @note This function is declared as __WEAK to be overridden in case of other
  *       implementations in user file.
  * @retval uint32_t HAL tick current value (unit: ms)
  */
__WEAK uint32_t HAL_GetTick(void)
{
  return uwTick;
}

/**
  * @brief This function returns a tick priority.
  * @retval uint32_t HAL tick priority
  */
uint32_t HAL_GetTickPrio(void)
{
  return uwTickPrio;
}

/**
  * @brief Return tick frequency.
  * @retval hal_tick_freq_t HAL tick frequency setting
  */
hal_tick_freq_t HAL_GetTickFreq(void)
{
  return uwTickFreq;
}

/**
  * @brief This function provides minimum delay (in milliseconds) based on variable incremented.
  * @note In the default implementation, SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals where HAL_IncTick() is called
  *       to increment the uwTick variable.
  * @note This function is declared as __WEAK to be overridden in case of other
  *       implementations in user file.
  * @param delay_ms delay duration, value range in 32 bit value capacity (unit: milliseconds)
  */
__WEAK void HAL_Delay(uint32_t delay_ms)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = delay_ms;

  /* Add a delay unit to guarantee minimum wait */
  if (wait < (HAL_MAX_DELAY - (uint32_t)uwTickFreq))
  {
    wait += (uint32_t)(uwTickFreq);
  }

  while ((HAL_GetTick() - tickstart) < wait)
  {
  }
}

/**
  * @brief Suspend Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_SuspendTick()
  *       is called, the SysTick interrupt will be disabled and so Tick increment
  *       is suspended.
  * @note This function is declared as __WEAK to be overridden in case of other
  *       implementations in user file.
  */
__WEAK void HAL_SuspendTick(void)
{
  /* Disable SysTick Interrupt */
  HAL_CORTEX_SYSTICK_Suspend();
}

/**
  * @brief Resume Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_ResumeTick()
  *       is called, the SysTick interrupt will be enabled and so Tick increment
  *       is resumed.
  * @note This function is declared as __WEAK to be overridden in case of other
  *       implementations in user file.
  */
__WEAK void HAL_ResumeTick(void)
{
  /* Enable SysTick Interrupt */
  HAL_CORTEX_SYSTICK_Resume();
}

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group3
  * @{
  This subsection provides a set of functions allowing to get HAL driver version.
  */

/**
  * @brief  Returns the HAL revision
  * @retval uint32_t HAL driver version: 0xXYZR (8bits for each decimal, R for release candidate)
  */
uint32_t HAL_GetVersion(void)
{
  return HAL_VERSION;
}

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group4
  * @{
  This subsection provides a set of functions allowing to get device identification data.
  */

/**
  * @brief  Return the device unique identification data
  * @param  p_uid Pointer to hal_device_uid_t structure containing identification data
  * @retval HAL_OK            Clock configuration successfully done
  * @retval HAL_INVALID_PARAM Input parameter not valid (USE_HAL_CHECK_PARAM enabled)
  */
hal_status_t HAL_GetDeviceUniqueID(hal_device_uid_t *p_uid)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((p_uid != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the handle struct pointer */
  if (p_uid == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_uid->uid_0 = LL_GetUID_Word0();
  p_uid->uid_1 = LL_GetUID_Word1();
  p_uid->uid_2 = LL_GetUID_Word2();

  return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* USE_HAL_MODULE */

/**
  * @}
  */

/**
  * @}
  */
