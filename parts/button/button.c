/**
  ******************************************************************************
  * @file    button.c
  * @author  MCD Application Team
  * @brief   This file contains all the functions for the board Button
  *          whatever the STM32 family.
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
#include "button.h"

/** @addtogroup BUTTON_Part_Driver
  * @{
  *
    The Button part driver provides the interface for an external button on the board and
    it is not directly dependent of the HAL nor the board hardware design.
    The component driver provides specific services and could be used by any board
    with GPIO driven button.
    - BUTTON part resources init path : activated parts resources
      are initialized either from the system_init or user code,
      before the using BUTTON parts services.
    -  BUTTON parts services are invoked by the applicative layer
      using logical instance object


  The button driver is a multi-instance object based on the button_t structure.

  #### Button definition

  The BUTTON driver pattern is a multi-instance object based on the button_t structure.
  The instance structures are defined in user code.
  The low-level initialization function (which assigns resources to Button instances) can be generated
  by CubeMX2 in mx_button.c/.h.
  Button instances are identified by their `id` field.
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup BUTTON_Part_Driver_Exported_Functions
  * @{

  #### Button services usage

  Button interrupt, state change event, management:
  Use the function _button_enableit_ to enable the button interrupt and catch button state change.

  When not using HAL EXTI register callbacks the user must implement one of the EXTI callback functions
  _HAL_EXTI_Rising_Callback_ or _HAL_EXTI_Falling_Callback_.
  The right callback function to implement will depend on the button active state defined by the user:
   * Use _HAL_EXTI_Rising_Callback_ when the button active state is high, _HAL_GPIO_PIN_SET_,
   pushing the button will produce rising edge.
   * Use _HAL_EXTI_Falling_Callback_ when the button active state is low, _HAL_GPIO_PIN_RESET_,
   pushing the button will produce falling edge.

  When using HAL EXTI register callbacks the user has to write his own callback function and use the function
  _button_register_callbacks_ to register it.
  The call back function is then called on the configured button event _BUTTON_EVENT_PRESSED_,
  _BUTTON_EVENT_UNPRESSED_ or _BUTTON_EVENT_PRESSED_UNPRESSED_.

  #### BUTTON Parts driver functions:

  Init function:
  - Use button_init() to initialize the button.

  Services functions:
  - Use button_get_state() to get the state of the button pressed or unpressed.
  - Use button_enableit() to enable the interruption for the button.
  - Use button_disableit() to disable the interruption for the button.
  - Use button_register_callbacks() to register callback function for the button.
  */

/**
  * @brief This function initializes the button.
  * It disables the button interrupt.
  * The GPIO peripheral must be initialized beforehand.
  * Usually it is initialized by auto generated code from STM32CubeSTUDIO otherwise
  * it up to the user to correctly initialize the GPIO peripheral.
  *
  * @param p_button  A pointer to the type button_t, that can be defined using the macro DEFINE_BUTTON
  * for button defined using STM32CubeSTUDIO.
  *
  */
void button_init(button_t *p_button, uint32_t id)
{
  p_button->id = id;
  button_io_init(p_button);
  button_disableit(p_button);
}

__WEAK void button_io_init(button_t *p_button)
{
  (void)p_button;
}

/**
  * @brief This function enables interrupt request on button event.
  *
  * @param p_button  A pointer to the type button_t, that can be defined using the macro DEFINE_BUTTON
  * for button defined using STM32CubeSTUDIO.
  *
  */
void button_enableit(const button_t *p_button)
{
  /* Clear interrupt pending bit of the selected EXTI line. */
  HAL_EXTI_ClearPending(p_button->exti_handle, HAL_EXTI_TRIGGER_RISING_FALLING);
  /* Enable NVIC interrupt request for the selected EXTI line.*/
  HAL_CORTEX_NVIC_EnableIRQ(p_button->irqline);
  /* Start the selected EXTI line on Interrupt Mode. */
  HAL_EXTI_Start(p_button->exti_handle, HAL_EXTI_MODE_INTERRUPT);

}

/**
  * @brief This function disables the interrupt for the button.
  *
  * @param p_button  A pointer to the type button_t, that can be defined using the macro DEFINE_BUTTON
  * for button defined using STM32CubeSTUDIO.
  *
  */
void button_disableit(const button_t *p_button)
{
  /* Stop the selected EXTI line. */
  HAL_EXTI_Stop(p_button->exti_handle);
  /* Disable NVIC interrupt request for the selected EXTI line.*/
  HAL_CORTEX_NVIC_DisableIRQ(p_button->irqline);
  /* Clear interrupt pending bit of the selected EXTI line. */
  HAL_EXTI_ClearPending(p_button->exti_handle, HAL_EXTI_TRIGGER_RISING_FALLING);
}

/**
  * @brief This function returns the state of the button BUTTON_PRESSED or BUTTON_UNPRESSED.
  *
  * @param p_button  A pointer to the type button_t, that can be defined using the macro DEFINE_BUTTON
  * for button defined using STM32CubeSTUDIO.
  *
  */
button_state_t button_get_state(const button_t *p_button)
{
  if (HAL_GPIO_ReadPin(p_button->port, p_button->pin) == p_button->active_state)
  {
    return BUTTON_PRESSED;
  }
  else
  {
    return BUTTON_UNPRESSED;
  }
}


/**
  * @brief This function register a callback function for the button.
  * The callback function is called on the selected button event.
  * This function can only be used when EXTI register reminder is enabled.
  * Otherwise the user can overwrite the default weak callback functions
  * _HAL_EXTI_Rising_Callback_ and _HAL_EXTI_Falling_Callback_
  *
  * @param p_button  A pointer to the type button_t, that can be defined using the macro DEFINE_BUTTON
  * for button defined using STM32CubeSTUDIO.
  *
  * @param p_cb  A pointer to the callback function called on button events.
  *
  * @param button_event  Define the button event, pressed/unpressed on wish the the button
  * callback function should be called
  *
  */

#if defined (USE_HAL_EXTI_REGISTER_CALLBACKS) && (USE_HAL_EXTI_REGISTER_CALLBACKS == 1)
void button_register_callbacks(const button_t *p_button, button_callback_t *p_cb, button_event_t button_event)
{
  if (button_event == BUTTON_EVENT_PRESSED)
  {
    if (p_button->active_state == HAL_GPIO_PIN_SET)
    {
      HAL_EXTI_RegisterRisingCallback(p_button->exti_handle, p_cb);
    }
    else
    {
      HAL_EXTI_RegisterFallingCallback(p_button->exti_handle, p_cb);
    }
  }
  else if (button_event == BUTTON_EVENT_UNPRESSED)
  {
    if (p_button->active_state == HAL_GPIO_PIN_SET)
    {
      HAL_EXTI_RegisterFallingCallback(p_button->exti_handle, p_cb);
    }
    else
    {
      HAL_EXTI_RegisterRisingCallback(p_button->exti_handle, p_cb);
    }
  }
  else
  {
    /*  button_event == BUTTON_EVENT_ANY*/
    HAL_EXTI_RegisterRisingFallingCallback(p_button->exti_handle, p_cb);
  }
}
#endif /* USE_HAL_EXTI_REGISTER_CALLBACKS */


/**
  * @} BUTTON_Part_Driver_Exported_Functions
  */

/* private functions --------------------------------------------------------*/

/**
  * @} BUTTON_Part_Driver
  */
