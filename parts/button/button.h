/**
  ******************************************************************************
  * @file    button.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the board
  *          button driven by GPIO, whatever the STM32 family.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BUTTON_H
#define BUTTON_H


/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup BUTTON_Part_Driver Button Part driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup BUTTON_Part_Driver_Exported_Types Button Exported Types
  * @{
  */

/**
  * @brief Structure defining the properties for a Button.
  */
typedef struct
{
  uint32_t             id;              /*!< LED GPIO device Id */
  hal_gpio_t            port;           /*!< Button input GPIO port */
  uint16_t              pin;            /*!< Button input GPIO pin */
  IRQn_Type             irqline;        /*!< Button interrupt request line*/
  hal_gpio_pin_state_t  active_state;   /*!< Button input GPIO pin state (high or low) define the button active state */
  hal_exti_handle_t    *exti_handle;    /*!< EXTI handle for asynchronous features */
} button_t;


/**
  * @brief Enumeration defining the state of a Button
  */
typedef enum
{
  BUTTON_UNPRESSED = 0,  /*!< Indicate that the button state is not pressed */
  BUTTON_PRESSED         /*!< Indicate that the button state is pressed */
} button_state_t;

/**
  * @brief Enumeration representing the button state change event, used to register callbacks function.
  */
typedef enum
{
  BUTTON_EVENT_PRESSED = 0,       /*!< Event when the button state changes from unpressed to pressed  */
  BUTTON_EVENT_UNPRESSED,         /*!< Event when the button state changes from pressed to unpressed */
  BUTTON_EVENT_ANY                /*!< Event when the button state changes */
} button_event_t;

#if defined (USE_HAL_EXTI_REGISTER_CALLBACKS) && (USE_HAL_EXTI_REGISTER_CALLBACKS == 1)
typedef void (button_callback_t)(hal_exti_handle_t *p_exti); /*!< Button callback function pointer definition */
#endif /* USE_HAL_EXTI_REGISTER_CALLBACKS */
/**
  * @} BUTTON_Part_Driver_Exported_Types
  */

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported function ---------------------------------------------------------*/
/** @defgroup BUTTON_Part_Driver_Exported_Functions Button Exported Functions
  * @{
  */
void button_init(button_t *p_button, uint32_t id);

void button_io_init(button_t *p_button);

#if defined (USE_HAL_EXTI_REGISTER_CALLBACKS) && (USE_HAL_EXTI_REGISTER_CALLBACKS == 1)
void button_register_callbacks(const button_t *p_button, button_callback_t *p_cb, button_event_t button_event);
#endif /* USE_HAL_EXTI_REGISTER_CALLBACKS */

button_state_t button_get_state(const button_t *p_button);
void button_enableit(const button_t *p_button);
void button_disableit(const button_t *p_button);

/**
  * @} BUTTON_Part_Driver_Exported_Functions
  */

/**
  * @} BUTTON_Part_Driver
  */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BUTTON_H */
