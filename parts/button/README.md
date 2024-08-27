<img src="doc/subbrand-stm32.svg" wi__Summary__dth="50"/>

# __Part driver: Button__

## __Summary__

Part Button provides API to drive Buttons.

## __Description__

### Part Button


#### Button API definition

Buttons ares identified by a structure of type _button_t_ representing a button instance.

  -
    ```c
    void button_init (const button_t *button)
    ```
    This function initializes the logical part of the driver.

    **Note:** this function does not initialize the GPIO and EXTI peripherals.

    - __button_t *__p_button___

      The __p_button__  parameter is pointer to the structure used to identify the button instance.

  - ```c
    button_state_t  button_get_state (const button_t *p_button)
    ```

    This function return the state of the button.
    - _button_t *__p_button___

      The __p_button__ parameter is pointer to the structure used to identify the button instance.
    -  _button_state_t_ __retrun value__:

       State of the button

  - ```c
    void button_enableit (const button_t *p_button)
    ```

    This function enable the interruption for button.

    - _button_t *__p_button___

      The __p_button__ parameter is pointer to the structure used to identify the button instance.

  - ```c
    void button_disableit (const button_t *p_button)
    ```

    This function disable the interruption for button.

    - _button_t *__p_button___

      The __p_button__ parameter is pointer to the structure used to identify the button instance.


  - ```c
    void button_register_callbacks(const button_t *button, button_callback_t *p_cb, button_event_t button_event)
    ```

    - _button_t *__p_button___

      The __p_button__ parameter is pointer to the structure used to identify the button instance.

    - button_callback_t *__p_cb___

      The __p_cb__ parameter is a pointer to the callback function.

    - _button_event_t __button_event___
      The __button_event__ parameter is a pointer to the callback function.

    This function register a callback function for button interruption event.
    The callback function is called on button interruption event, when the button is activated.


 - ```c
   void button_irq_handler (const button_t *p_button)
   ```
    - __button_t *__p_button___

      The __p_button__ parameter is pointer to the structure used to identify the button instance.

    This function call the button interrupt handles, the callback function registered with the function _button_register_callbacks_.

#### Button types definition

  - Button function callback type definition:
    ```c
    typedef void (* button_callback_t)(void);
    ```

  - Button state value type definition:
    ```c
    typedef enum
    {
      BUTTON_UNPRESSED = 0,
      BUTTON_PRESSED
    } button_state_t;
    ```

  - Button event type definition:
    typedef enum
    {
      BUTTON_EVENT_PRESSED = 0,
      BUTTON_EVENT_UNPRESSED,
      BUTTON_EVENT_ANY
    } button_event_t;
    ```

  - Button instance Structure definition:
    ```c
    typedef struct
    {
      hal_gpio_t            port;
      uint16_t              pin;
      IRQn_Type             irqline;
      hal_gpio_pin_state_t  active_state;
      void *(*gethandle)(void);
    } button_t;
    ```

### Peripherals initialization:
  Part Button part driver assumes that the initialisation of all needed peripherals is done by the main application.

  The GPIO and EXTI peripherals is, by default in the example projects default,
  initialized by the auto generated code produced by the STM32CubeStudio in "stm32_mcu_def.h" file.
  Otherwise it up to the user to correctly initializes the GPIO as an input and EXTI interrupt.

## __How to use it?__

### Buttons defined with STM32CubeStudio:

For using a BUTTON using the part LED API, a variable representing the BUTTON must be defined.
Using STM32CubeSTUDIO, BUTTONs IO structures are generated in "mx_button.c" and "mx_button.h" files:

Example for custom Button connected to pin 7 of GPIO port H, with a low signal when pressed, IRQ, get:
  - "mx_button.h"
    ```c
    extern const button_t               sMX_BUTTON_EXAMPLE;
    #define MX_BUTTON_EXAMPLE          &sMX_BUTTON_EXAMPLE
    ```
  - "mx_button.c"
    ```c
    #include "mx_button.h"

    const button_t sMX_BUTTON_EXAMPLE =
    {
      .port = HAL_GPIOH,
      .pin = HAL_GPIO_PIN_7,
      .irqline = EXTI13_IRQn,
      .active_state = HAL_GPIO_PIN_RESET,
      .gethandle = exti_gethandled
    };
    ```

## Needed components
### For part Button:
 - STM32 HAL GPIO
 - STM32 HAL EXTI


## __Contributing__

STM32 customers and users who want to contribute to this component can follow instructions on [STMicroelectronics GitHub page]( https://github.com/STMicroelectronics)

## __License__

Copyright (c) 2022 STMicroelectronics.

This software is licensed under terms that can be found in the LICENSE file in the root directory of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.

## __Keywords__
HAL
STM32
BSP
Parts
Button
