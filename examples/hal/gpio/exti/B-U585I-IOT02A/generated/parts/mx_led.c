/**
  ******************************************************************************
  * file           : mx_led.c
  * brief          : led part resources body
  ******************************************************************************
  * attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "mx_led.h"

void led_io_init(led_t *p_led)
{
  switch (p_led->id)
  {
    case MX_STATUS_LED:
      p_led->port = MX_STATUS_LED_GPIO_PORT;
      p_led->pin  = MX_STATUS_LED_PIN;
      p_led->active_state = MX_STATUS_LED_ACTIVE_STATE;
      break;
    default:
      break;
  }
}

