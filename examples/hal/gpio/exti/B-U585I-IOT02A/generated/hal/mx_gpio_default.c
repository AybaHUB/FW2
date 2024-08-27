/**
  ******************************************************************************
  * @file    mx_gpio_default.c
  * @brief   gpio_default Peripheral initialization
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
#include "mx_gpio_default.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported variables by reference -------------------------------------------*/
static hal_exti_handle_t hEXTI13;

/******************************************************************************/
/* Exported functions for GPIO in HAL layer (SW instance MyGPIO_1 */
/******************************************************************************/
system_status_t mx_gpio_default_cfg1_hal_init(void)
{
   hal_gpio_config_t  gpio_config;

  HAL_RCC_GPIOE_EnableClock();

  HAL_RCC_GPIOC_EnableClock();

  HAL_GPIO_WritePin(HAL_GPIOE, HAL_GPIO_PIN_13, HAL_GPIO_PIN_RESET);

  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_PUSHPULL;
  if (HAL_GPIO_Init(HAL_GPIOE, HAL_GPIO_PIN_13, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  HAL_GPIO_DisableHighSpeedLowVoltage(HAL_GPIOE, HAL_GPIO_PIN_13);

  gpio_config.mode            = HAL_GPIO_MODE_INPUT;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  if (HAL_GPIO_Init(HAL_GPIOC, HAL_GPIO_PIN_13, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  HAL_GPIO_DisableHighSpeedLowVoltage(HAL_GPIOC, HAL_GPIO_PIN_13);

  hal_exti_config_t exti_config;

  /* Initialize and configure the EXTI for GPIOC line13 */
  HAL_EXTI_Init(&hEXTI13, HAL_EXTI_LINE_13);

  exti_config.trigger   = HAL_EXTI_TRIGGER_RISING;
  exti_config.gpio_port = HAL_EXTI_GPIOC;

  HAL_EXTI_SetConfig(&hEXTI13, &exti_config);

  /* set line 13 Interrupt priority */
  HAL_CORTEX_NVIC_SetPriority(EXTI13_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(EXTI13_IRQn);

  return SYSTEM_OK;
}

system_status_t mx_gpio_default_cfg1_hal_deinit(void)
{
  HAL_GPIO_DeInit(HAL_GPIOE, HAL_GPIO_PIN_13);

  /* Deinitialize the EXTI for GPIOC line13 */
  HAL_EXTI_DeInit(&hEXTI13);

  /* set line 13 Interrupt priority */
  HAL_CORTEX_NVIC_DisableIRQ(EXTI13_IRQn);

  HAL_GPIO_DeInit(HAL_GPIOC, HAL_GPIO_PIN_13);

  return SYSTEM_OK;
}


hal_exti_handle_t *mx_gpio_exti13_gethandle(void)
{
  return &hEXTI13;
}

/******************************************************************************/
/*                     EXTI Line13 interrupt                    */
/******************************************************************************/
void EXTI13_IRQHandler(void)
{
  HAL_EXTI_IRQHandler(&hEXTI13);
}

