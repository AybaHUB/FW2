/**
  ******************************************************************************
  * @file    stm32_basic_stdio.h
  * @author  MCD Application Team
  * @brief   public API header for the Basic stdio utility
  ******************************************************************************
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32_BASIC_STDIO_H
#define STM32_BASIC_STDIO_H

/* Includes ------------------------------------------------------------------*/
/* Internal functions ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
{
#endif

/** @brief Overall module initialization function.
  *
  * This function initializes Basic Trace.
  * Its actual effect changes depending on the selected variant:
  * - UART: @param pobj is actually a `UART_HandleTypeDef*`, and should be initialized manually
  * in polling mode with the desired output configuration.
  * The calls stores it for use for all later transmissions.
  * - ITM: @param pobj unused. Pass NULL in when calling.
  * - Template: behavior and semantics are user-defined.
  */
void UTIL_BASIC_STDIO_Init(void *pobj);

#ifdef __cplusplus
}
#endif

#endif /* STM32_BASIC_STDIO_H */
