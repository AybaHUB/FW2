/**
  ******************************************************************************
  * file           : main.c
  * brief          : Main program body
  *                  main() calls the target system initialization, then calls the example entry point.
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32_basic_stdio.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
app_status_t ExecStatus = EXEC_STATUS_UNKNOWN; /* application status */
led_t status_led;

/* Private functions prototype -----------------------------------------------*/
static void error_handler(void);
static void success_handler(void);

/** brief:  The application entry point.
  * retval: none but we specify int to comply with C99 standard
  */
int main(void)
{
  /** System Init: this generated code placed in targets folder initializes your system.
    * It calls the initialization (and sets the initial configuration) of the peripherals.
    * You can use STM32CubeMX to generate and call this code or not in this project.
    * It also contains the HAL initialization and the initial clock configuration.
    */
  if (mx_system_init() != 0)
  {
    ExecStatus = EXEC_STATUS_ERROR; /* memorize the error */
  }
  else
  {
    /* Initialize basic_stdio separately, but after system init. */
    UTIL_BASIC_STDIO_Init(mx_basic_stdio_gethandle());

    /* Initialize status LED */
    led_init(&status_led, MX_STATUS_LED);

    /** Example execution: this hardware and IDE agnostic code contains the scenario that we demonstrate.
      * This is the applicative code showing how to use the peripheral (functionality-wise).
      * You may copy/paste it in your own application,
      * while you may keep on generating the initialization and configuration code with STM32CubeMX.
      */
    ExecStatus = app_init();

    if (ExecStatus != EXEC_STATUS_ERROR)
    {
      ExecStatus = app_process();
    }

    if (ExecStatus == EXEC_STATUS_OK)
    {
      ExecStatus = app_deinit();
    }

  } /* end applicative part */

  /* Report the example status */
  if (ExecStatus == EXEC_STATUS_OK)
  {
    success_handler();
  }
  else
  {
    error_handler();
  }

  /* This point should not be reached */
  return (0);
} /* end main */

/** The functions below are used to report the example status.
  * ----------------------------------------------------------
  */

/** brief:  Error notification
  * retval: None (infinite loop)
  */
static void error_handler(void)
{
  while (1)
  {
    /* Repeated flashing status LED (50ms on and 2sec off) when execution loop is exited */
    led_on(&status_led);
    HAL_Delay(50);
    led_off(&status_led);
    HAL_Delay(2000);
  }
} /* end error_handler */

/** brief:  Success notification
  * retval: None (infinite loop)
  */
static void success_handler(void)
{
  /* Report success: LED_USER remains turned on */
  led_on(&status_led);
  while (1);
} /* end success_handler */

/** Redefines the HardFault handler from the startup file.
  * brief:  Hard Fault Handler
  * retval: None (infinite loop)
  *
  * The default handler is redefined here so that:
  * 1. The example status can be updated.
  * 2. You can easily set a breakpoint to investigate the issue.
  */
void HardFault_Handler(void)
{
  /* The example encountered an unrecoverable error */
  ExecStatus = EXEC_STATUS_ERROR;

  /* Take a chance to turn the status LED off (this might fail) */
  led_off(&status_led);

  /* Unrecoverable error: infinite loop */
  while (1);
}
