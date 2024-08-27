/**
  ******************************************************************************
  * @file           : mx_hal_def.h
  * @brief          : Exporting peripherals initialization
  *                   Include entry for the target folder to the application.
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
#ifndef MX_HAL_DEF_H
#define MX_HAL_DEF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"
#include "mx_usart1.h"
#include "mx_gpio_default.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* ########### Aliases to initialization functions ########### */

/* *********************************************************** */
/*        gpio_default_instance0: aliases for initialization functions */
/* *********************************************************** */

/**
  * @brief  Initialize the mx_gpio_default_cfg1_hal with HAL layer
  *         Name of the User label:
  *                   mx_example_exti_trigger
  *         Name of the Config label:
  *                   
  * @retval hal_gpio_handle_t Pointer on the handle on the gpio_default instance
  */
#define mx_example_exti_trigger_init mx_gpio_default_cfg1_hal_init


/* *********************************************************** */
/*        usart1_instance2: aliases for initialization functions */
/* *********************************************************** */

/**
  * @brief  Initialize the mx_usart1_cfg1_hal_uart with HAL layer
  *         Name of the User label:
  *                   mx_basic_stdio
  *         Name of the Config label:
  *                   
  * @retval hal_uart_handle_t Pointer on the handle on the USART1 instance
  */
#define mx_basic_stdio_init mx_usart1_cfg1_hal_uart_init


/* ########################################################### */

/* ########### Aliases to De-Initialization functions ########### */

/* *********************************************************** */
/*        gpio_default_instance0: aliases for De-Initialization functions */
/* *********************************************************** */

/**
  * @brief  De-Initialize the mx_gpio_default_cfg1_hal with HAL layer
  *         Name of the User label:
  *                   mx_example_exti_trigger
  *         Name of the Config label:
  *                   
  */
#define mx_example_exti_trigger_deinit mx_gpio_default_cfg1_hal_deinit


/* *********************************************************** */
/*        usart1_instance2: aliases for De-Initialization functions */
/* *********************************************************** */

/**
  * @brief  De-Initialize the mx_usart1_cfg1_hal_uart with HAL layer
  *         Name of the User label:
  *                   mx_basic_stdio
  *         Name of the Config label:
  *                   
  */
#define mx_basic_stdio_deinit mx_usart1_cfg1_hal_uart_deinit


/* ########################################################### */

/* ########### Aliases to get HAL handle functions ########### */

/* *********************************************************** */
/*        GPIO: aliases for get EXTI object functions */
/* *********************************************************** */

/**
  * @brief  Get the EXTI handle for EXTI13 used for PC13
  *         Name of the User label:
  *                   mx_example_exti_trigger
* @retval hal_exti_handle_t Pointer on the handle on the EXTI instance
  */
#define mx_example_exti_trigger_exti_gethandle   mx_gpio_exti13_gethandle

/* *********************************************************** */
/*        usart1_instance2: aliases for get handle functions */
/* *********************************************************** */

/**
  * @brief  Get the HAL handle for USART1
  *         Name of the User label:
  *                   mx_basic_stdio
  * @retval hal_uart_handle_t Pointer on the handle on the USART1 instance
  */
#define mx_basic_stdio_gethandle mx_usart1_hal_uart_gethandle



/* ########################################################### */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_HAL_DEF_H */
