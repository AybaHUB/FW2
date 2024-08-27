/**
  ******************************************************************************
  * @file           : mx_interrupts.h
  * @brief          : Header for mx_mx_interrupts.c file.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_INTERRUPTS_H
#define MX_INTERRUPTS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"
#include "mx_def.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
  * @brief  System initialization
  * @retval Status
  */
system_status_t mx_interrupts_init(void);

void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_INTERRUPTS_H */
