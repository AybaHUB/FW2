/**
  ******************************************************************************
  * @file    stm32_basic_stdio.c
  * @author  MCD Application Team
  * @brief   This file contains the basic stdio utility functions based on UART.
  ******************************************************************************
  * @attention
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

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32_hal.h"
#include "stm32_basic_stdio.h"
#include "stm32_basic_stdio_internal.h"

/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/*
 * Static (private) variable holding the UART handle to use. Initialized to NULL.
 */
static hal_uart_handle_t *puartObj = NULL;

/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/

void UTIL_BASIC_STDIO_Init(void *pobj)
{
  puartObj = pobj;
}

#if defined(WRITE_PROTO)

WRITE_PROTO(file, ptr, len)
{
  (void)(file); /* prevent "unused variable" warnings */

  if (puartObj == NULL)
  {
    return 0;
  }

  if (HAL_UART_Transmit(puartObj, (const uint8_t *)ptr, len, 0xFFFFU) == HAL_OK)
  {
    return len;
  }
  else
  {
    return 0;
  }
}

#else

int fputc(int c, FILE *f)
{
  (void)(f); /* prevent "unused variable" warnings */

  if (puartObj == NULL)
  {
    return EOF;
  }

  if (HAL_UART_Transmit(puartObj, (uint8_t *)&c, 1U, 0xFFFFU) == HAL_OK)
  {
    return c;
  }
  else
  {
    return EOF;
  }
}

#endif /* WRITE_PROTO */
