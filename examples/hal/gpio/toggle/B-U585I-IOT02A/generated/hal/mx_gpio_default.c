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

/******************************************************************************/
/* Exported functions for GPIO in HAL layer (SW instance MyGPIO_1 */
/******************************************************************************/
system_status_t mx_gpio_default_cfg1_hal_init(void)
{
  hal_gpio_config_t  gpio_config;

  HAL_RCC_GPIOE_EnableClock();

  HAL_GPIO_WritePin(HAL_GPIOE, HAL_GPIO_PIN_13, HAL_GPIO_PIN_RESET);

  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_PUSHPULL;
  if (HAL_GPIO_Init(HAL_GPIOE, HAL_GPIO_PIN_13, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  HAL_GPIO_DisableHighSpeedLowVoltage(HAL_GPIOE, HAL_GPIO_PIN_13);

  return SYSTEM_OK;
}

system_status_t mx_gpio_default_cfg1_hal_deinit(void)
{
  HAL_GPIO_DeInit(HAL_GPIOE, HAL_GPIO_PIN_13);

  return SYSTEM_OK;
}



