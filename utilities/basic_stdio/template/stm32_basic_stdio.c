/**
  ******************************************************************************
  * @file    stm32_basic_stdio.c
  * @author  MCD Application Team
  * @brief   This file contains the basic stdio utility functions based on the technology of your choice.
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
#include "stm32_basic_stdio.h"
#include "stm32_basic_stdio_internal.h"

/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/

/* Documentation for these functions is available in
 * - doc/stm32_basic_stdio.h
 * - doc/stm32_basic_stdio_internal.h
*/

void UTIL_BASIC_STDIO_Init(void *pobj)
{
  /* Empty */
  (void)(pobj); /* prevent "unused variable" warnings */
}

#if defined(WRITE_PROTO)

WRITE_PROTO(file, ptr, len)
{
  /* Default implementation: always fail */

  /* prevent "unused variable" warnings */
  (void)(file);
  (void)(ptr);
  (void)(len);

  return 0;
}

#else

int fputc(int c, FILE *f)
{
  /* Default implementation: always fail */

  /* prevent "unused variable" warnings */
  (void)(c);
  (void)(f);

  return EOF;
}

#endif /* WRITE_PROTO */
