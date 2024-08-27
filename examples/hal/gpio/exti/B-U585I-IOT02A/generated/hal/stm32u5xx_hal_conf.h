/**
  ******************************************************************************
  * @file    stm32u5xx_hal_conf.h
  * @author  GPM Application Team
  * @brief   HAL configuration file.
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
#ifndef  STM32U5XX_HAL_CONF_H
#define  STM32U5XX_HAL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* ########################## Module Selection ############################## */
/**
  * @brief This is the list of modules to be used in the HAL driver
  */
#define USE_HAL_MODULE                          1U
#define USE_HAL_ADC_MODULE                      0U
#define USE_HAL_AES_MODULE                      0U
#define USE_HAL_COMP_MODULE                     0U
#define USE_HAL_CORDIC_MODULE                   0U
#define USE_HAL_CORTEX_MODULE                   1U
#define USE_HAL_CRC_MODULE                      0U
#define USE_HAL_CRS_MODULE                      0U
#define USE_HAL_DAC_MODULE                      0U
#define USE_HAL_DBGMCU_MODULE                   0U
#define USE_HAL_DCACHE_MODULE                   0U
#define USE_HAL_DCMI_MODULE                     0U
#define USE_HAL_DMA_MODULE                      1U
#define USE_HAL_DMA2D_MODULE                    0U
#define USE_HAL_DSI_MODULE                      0U
#define USE_HAL_EXTI_MODULE                     1U
#define USE_HAL_FDCAN_MODULE                    0U
#define USE_HAL_FLASH_MODULE                    1U
#define USE_HAL_FLASH_OB_MODULE                 0U
#define USE_HAL_FMAC_MODULE                     0U
#define USE_HAL_GFXMMU_MODULE                   0U
#define USE_HAL_GPIO_MODULE                     1U
#define USE_HAL_GPU2D_MODULE                    0U
#define USE_HAL_GTZC_MODULE                     0U
#define USE_HAL_HASH_MODULE                     0U
#define USE_HAL_HCD_MODULE                      0U
#define USE_HAL_I2C_MODULE                      0U
#define USE_HAL_ICACHE_MODULE                   1U
#define USE_HAL_IWDG_MODULE                     0U
#define USE_HAL_JPEG_MODULE                     0U
#define USE_HAL_LPTIM_MODULE                    0U
#define USE_HAL_LTDC_MODULE                     0U
#define USE_HAL_MDF_MODULE                      0U
#define USE_HAL_MMC_MODULE                      0U
#define USE_HAL_NAND_MODULE                     0U
#define USE_HAL_NOR_MODULE                      0U
#define USE_HAL_OPAMP_MODULE                    0U
#define USE_HAL_PCD_MODULE                      0U
#define USE_HAL_PKA_MODULE                      0U
#define USE_HAL_PSSI_MODULE                     0U
#define USE_HAL_PWR_MODULE                      1U
#define USE_HAL_RAMCFG_MODULE                   0U
#define USE_HAL_RCC_MODULE                      1U
#define USE_HAL_RNG_MODULE                      0U
#define USE_HAL_RTC_MODULE                      0U
#define USE_HAL_SAI_MODULE                      0U
#define USE_HAL_SD_MODULE                       0U
#define USE_HAL_SMARTCARD_MODULE                0U
#define USE_HAL_SMBUS_MODULE                    0U
#define USE_HAL_SPI_MODULE                      0U
#define USE_HAL_SRAM_MODULE                     0U
#define USE_HAL_SYSCFG_MODULE                   1U
#define USE_HAL_TAMP_MODULE                     0U
#define USE_HAL_TIM_MODULE                      0U
#define USE_HAL_UART_MODULE                     1U
#define USE_HAL_UCPD_MODULE                     0U
#define USE_HAL_USART_MODULE                    0U
#define USE_HAL_VREFBUF_MODULE                  0U
#define USE_HAL_WWDG_MODULE                     0U
#define USE_HAL_XSPI_MODULE                     0U
#define USE_HAL_XSPI_OTFDEC                     0U

/* ########################### System Configuration ######################### */
/**
  * @brief This is the HAL system configuration section
  */
#define  VDD_VALUE                              3300UL /*!< Value of VDD in mv */
#define  TICK_INT_PRIORITY                      ((1UL << __NVIC_PRIO_BITS) - 1UL)  /*!< tick interrupt priority (lowest by default) */
#define  USE_HAL_PREFETCH                       1U     /*!< Enable Flash prefetch */

/* ########################## HAL OS configuration ########################## */
/**
  * @brief Used by the HAL PPP Acquire/Release APIs when the define USE_HAL_MUTEX is set to 1
  */
#define USE_HAL_MUTEX                           0U

/* ########################## HAL API parameters check  ##################### */
/**
  * @brief Run time parameter check activation
  */
#define USE_HAL_CHECK_PARAM                     0U
#define USE_HAL_SECURE_CHECK_PARAM              0U

/* ########################## State transition   ############################ */
/**
  * @brief Enable protection of state transition in thread safe
  */
#define USE_HAL_CHECK_PROCESS_STATE             0U

/* ########################## Peripheral clock gating  ############################# */
/**
  * @brief This clock activation is done inside each PPP
  *        Each PPP can be configured independently in using defined available in stm32u5xx_hal_def.h)
  *           @arg HAL_CLK_ENABLE_NO                No clock activation in PPP
  *           @arg HAL_CLK_ENABLE_PERIPH_ONLY       PERIPH Clock activation only
  *           @arg HAL_CLK_ENABLE_PERIPH_PWR_SYSTEM PERIPH Clock activation including PWR and/or system
  */
#define USE_HAL_ADC_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_AES_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_COMP_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_CORDIC_CLK_ENABLE_MODEL         HAL_CLK_ENABLE_NO
#define USE_HAL_CRC_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_CRS_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_DAC_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_DCACHE_CLK_ENABLE_MODEL         HAL_CLK_ENABLE_NO
#define USE_HAL_DCMI_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_DMA_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_DMA2D_CLK_ENABLE_MODEL          HAL_CLK_ENABLE_NO
#define USE_HAL_DSI_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_FDCAN_CLK_ENABLE_MODEL          HAL_CLK_ENABLE_NO
#define USE_HAL_FLASH_CLK_ENABLE_MODEL          HAL_CLK_ENABLE_NO
#define USE_HAL_FMAC_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_GFXMMU_CLK_ENABLE_MODEL         HAL_CLK_ENABLE_NO
#define USE_HAL_GPIO_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_GPU2D_CLK_ENABLE_MODEL          HAL_CLK_ENABLE_NO
#define USE_HAL_GTZC_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_HASH_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_HCD_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_I2C_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_JPEG_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_LPTIM_CLK_ENABLE_MODEL          HAL_CLK_ENABLE_NO
#define USE_HAL_LTDC_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_MDF_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_MMC_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_NAND_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_NOR_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_OPAMP_CLK_ENABLE_MODEL          HAL_CLK_ENABLE_NO
#define USE_HAL_OTFDEC_CLK_ENABLE_MODEL         HAL_CLK_ENABLE_NO
#define USE_HAL_PCD_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_PKA_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_PSSI_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_PWR_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_RAMCFG_CLK_ENABLE_MODEL         HAL_CLK_ENABLE_NO
#define USE_HAL_RNG_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_SAI_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_SD_CLK_ENABLE_MODEL             HAL_CLK_ENABLE_NO
#define USE_HAL_SMARTCARD_CLK_ENABLE_MODEL      HAL_CLK_ENABLE_NO
#define USE_HAL_SMBUS_CLK_ENABLE_MODEL          HAL_CLK_ENABLE_NO
#define USE_HAL_SPI_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_SRAM_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_TIM_CLK_ENABLE_MODEL            HAL_CLK_ENABLE_NO
#define USE_HAL_UART_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_UCPD_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_USART_CLK_ENABLE_MODEL          HAL_CLK_ENABLE_NO
#define USE_HAL_WWDG_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO
#define USE_HAL_XSPI_CLK_ENABLE_MODEL           HAL_CLK_ENABLE_NO

/* ################## Register callback feature configuration ############### */
/**
  * @brief Set below the peripheral configuration  to "1U" to add the support
  *        of HAL callback registration/unregistration feature for the HAL
  *        driver(s). This allows user application to provide specific callback
  *        functions thanks to HAL_PPP_RegisterCallback() rather than overwriting
  *        the default weak callback functions (see each stm32u5xx_hal_ppp.h file
  *        for possible callback identifiers defined in HAL_PPP_CallbackIDTypeDef
  *        for each PPP peripheral).
  */
#define USE_HAL_ADC_REGISTER_CALLBACKS          0U
#define USE_HAL_AES_REGISTER_CALLBACKS          0U
#define USE_HAL_COMP_REGISTER_CALLBACKS         0U
#define USE_HAL_CORDIC_REGISTER_CALLBACKS       0U
#define USE_HAL_CRS_REGISTER_CALLBACKS          0U
#define USE_HAL_DAC_REGISTER_CALLBACKS          0U
#define USE_HAL_DCACHE_REGISTER_CALLBACKS       0U
#define USE_HAL_DCMI_REGISTER_CALLBACKS         0U
#define USE_HAL_DMA2D_REGISTER_CALLBACKS        0U
#define USE_HAL_DSI_REGISTER_CALLBACKS          0U
#define USE_HAL_EXTI_REGISTER_CALLBACKS         1U
#define USE_HAL_FDCAN_REGISTER_CALLBACKS        0U
#define USE_HAL_FLASH_REGISTER_CALLBACKS        0U
#define USE_HAL_FMAC_REGISTER_CALLBACKS         0U
#define USE_HAL_GFXMMU_REGISTER_CALLBACKS       0U
#define USE_HAL_GPU2D_REGISTER_CALLBACKS        0U
#define USE_HAL_HASH_REGISTER_CALLBACKS         0U
#define USE_HAL_HCD_REGISTER_CALLBACKS          0U
#define USE_HAL_I2C_REGISTER_CALLBACKS          0U
#define USE_HAL_ICACHE_REGISTER_CALLBACKS       0U
#define USE_HAL_IWDG_REGISTER_CALLBACKS         0U
#define USE_HAL_JPEG_REGISTER_CALLBACKS         0U
#define USE_HAL_LPTIM_REGISTER_CALLBACKS        0U
#define USE_HAL_LTDC_REGISTER_CALLBACKS         0U
#define USE_HAL_MDF_REGISTER_CALLBACKS          0U
#define USE_HAL_MMC_REGISTER_CALLBACKS          0U
#define USE_HAL_NAND_REGISTER_CALLBACKS         0U
#define USE_HAL_NOR_REGISTER_CALLBACKS          0U
#define USE_HAL_OPAMP_REGISTER_CALLBACKS        0U
#define USE_HAL_OTFDEC_REGISTER_CALLBACKS       0U
#define USE_HAL_PCD_REGISTER_CALLBACKS          0U
#define USE_HAL_PKA_REGISTER_CALLBACKS          0U
#define USE_HAL_PSSI_REGISTER_CALLBACKS         0U
#define USE_HAL_RAMCFG_REGISTER_CALLBACKS       0U
#define USE_HAL_RNG_REGISTER_CALLBACKS          0U
#define USE_HAL_SAI_REGISTER_CALLBACKS          0U
#define USE_HAL_SD_REGISTER_CALLBACKS           0U
#define USE_HAL_SMARTCARD_REGISTER_CALLBACKS    0U
#define USE_HAL_SMBUS_REGISTER_CALLBACKS        0U
#define USE_HAL_SPI_REGISTER_CALLBACKS          0U
#define USE_HAL_SRAM_REGISTER_CALLBACKS         0U
#define USE_HAL_TIM_REGISTER_CALLBACKS          0U
#define USE_HAL_UART_REGISTER_CALLBACKS         0U
#define USE_HAL_UCPD_REGISTER_CALLBACKS         0U
#define USE_HAL_USART_REGISTER_CALLBACKS        0U
#define USE_HAL_WWDG_REGISTER_CALLBACKS         0U
#define USE_HAL_XSPI_REGISTER_CALLBACKS         0U

/* ################## User data feature configuration ############### */
/**
  * @brief Manage a user data pointer stored in the peripheral handle.
  */
#define  USE_HAL_ADC_USER_DATA                  0U
#define  USE_HAL_AES_USER_DATA                  0U
#define  USE_HAL_COMP_USER_DATA                 0U
#define  USE_HAL_CORDIC_USER_DATA               0U
#define  USE_HAL_CRC_USER_DATA                  0U
#define  USE_HAL_DAC_USER_DATA                  0U
#define  USE_HAL_DCACHE_USER_DATA               0U
#define  USE_HAL_DCMI_USER_DATA                 0U
#define  USE_HAL_DMA2D_USER_DATA                0U
#define  USE_HAL_DSI_USER_DATA                  0U
#define  USE_HAL_EXTI_USER_DATA                 0U
#define  USE_HAL_FDCAN_USER_DATA                0U
#define  USE_HAL_FLASH_USER_DATA                0U
#define  USE_HAL_FMAC_USER_DATA                 0U
#define  USE_HAL_GFXMMU_USER_DATA               0U
#define  USE_HAL_GPU2D_USER_DATA                0U
#define  USE_HAL_HASH_USER_DATA                 0U
#define  USE_HAL_HCD_USER_DATA                  0U
#define  USE_HAL_I2C_USER_DATA                  0U
#define  USE_HAL_ICACHE_USER_DATA               0U
#define  USE_HAL_IWDG_USER_DATA                 0U
#define  USE_HAL_JPEG_USER_DATA                 0U
#define  USE_HAL_LPTIM_USER_DATA                0U
#define  USE_HAL_LTDC_USER_DATA                 0U
#define  USE_HAL_MDF_USER_DATA                  0U
#define  USE_HAL_MMC_USER_DATA                  0U
#define  USE_HAL_NAND_USER_DATA                 0U
#define  USE_HAL_NOR_USER_DATA                  0U
#define  USE_HAL_OPAMP_USER_DATA                0U
#define  USE_HAL_OTFDEC_USER_DATA               0U
#define  USE_HAL_PCD_USER_DATA                  0U
#define  USE_HAL_PKA_USER_DATA                  0U
#define  USE_HAL_PSSI_USER_DATA                 0U
#define  USE_HAL_RAMCFG_USER_DATA               0U
#define  USE_HAL_RNG_USER_DATA                  0U
#define  USE_HAL_SAI_USER_DATA                  0U
#define  USE_HAL_SD_USER_DATA                   0U
#define  USE_HAL_SMARTCARD_USER_DATA            0U
#define  USE_HAL_SMBUS_USER_DATA                0U
#define  USE_HAL_SPI_USER_DATA                  0U
#define  USE_HAL_SRAM_USER_DATA                 0U
#define  USE_HAL_TIM_USER_DATA                  0U
#define  USE_HAL_UART_USER_DATA                 0U
#define  USE_HAL_UCPD_USER_DATA                 0U
#define  USE_HAL_USART_USER_DATA                0U
#define  USE_HAL_WWDG_USER_DATA                 0U
#define  USE_HAL_XSPI_USER_DATA                 0U

/* ################## Get last errors feature configuration ############### */
/**
  * @brief Store the errors limited to the last process of a peripheral.
  */
#define  USE_HAL_ADC_GET_LAST_ERRORS            0U
#define  USE_HAL_AES_GET_LAST_ERRORS            0U
#define  USE_HAL_COMP_GET_LAST_ERRORS           0U
#define  USE_HAL_CORDIC_GET_LAST_ERRORS         0U
#define  USE_HAL_CRS_GET_LAST_ERRORS            0U
#define  USE_HAL_DAC_GET_LAST_ERRORS            0U
#define  USE_HAL_DCACHE_GET_LAST_ERRORS         0U
#define  USE_HAL_DCMI_GET_LAST_ERRORS           0U
#define  USE_HAL_DMA2D_GET_LAST_ERRORS          0U
#define  USE_HAL_DSI_GET_LAST_ERRORS            0U
#define  USE_HAL_EXTI_GET_LAST_ERRORS           0U
#define  USE_HAL_FDCAN_GET_LAST_ERRORS          0U
#define  USE_HAL_FLASH_GET_LAST_ERRORS          0U
#define  USE_HAL_FMAC_GET_LAST_ERRORS           0U
#define  USE_HAL_GFXMMU_GET_LAST_ERRORS         0U
#define  USE_HAL_GPU2D_GET_LAST_ERRORS          0U
#define  USE_HAL_HASH_GET_LAST_ERRORS           0U
#define  USE_HAL_HCD_GET_LAST_ERRORS            0U
#define  USE_HAL_I2C_GET_LAST_ERRORS            0U
#define  USE_HAL_ICACHE_GET_LAST_ERRORS         0U
#define  USE_HAL_IWDG_GET_LAST_ERRORS           0U
#define  USE_HAL_JPEG_GET_LAST_ERRORS           0U
#define  USE_HAL_LPTIM_GET_LAST_ERRORS          0U
#define  USE_HAL_LTDC_GET_LAST_ERRORS           0U
#define  USE_HAL_MDF_GET_LAST_ERRORS            0U
#define  USE_HAL_MMC_GET_LAST_ERRORS            0U
#define  USE_HAL_NAND_GET_LAST_ERRORS           0U
#define  USE_HAL_NOR_GET_LAST_ERRORS            0U
#define  USE_HAL_OPAMP_GET_LAST_ERRORS          0U
#define  USE_HAL_OTFDEC_GET_LAST_ERRORS         0U
#define  USE_HAL_PCD_GET_LAST_ERRORS            0U
#define  USE_HAL_PKA_GET_LAST_ERRORS            0U
#define  USE_HAL_PSSI_GET_LAST_ERRORS           0U
#define  USE_HAL_RAMCFG_GET_LAST_ERRORS         0U
#define  USE_HAL_RNG_GET_LAST_ERRORS            0U
#define  USE_HAL_SAI_GET_LAST_ERRORS            0U
#define  USE_HAL_SD_GET_LAST_ERRORS             0U
#define  USE_HAL_SMARTCARD_GET_LAST_ERRORS      0U
#define  USE_HAL_SMBUS_GET_LAST_ERRORS          0U
#define  USE_HAL_SPI_GET_LAST_ERRORS            0U
#define  USE_HAL_SRAM_GET_LAST_ERRORS           0U
#define  USE_HAL_TIM_GET_LAST_ERRORS            0U
#define  USE_HAL_UART_GET_LAST_ERRORS           0U
#define  USE_HAL_UCPD_GET_LAST_ERRORS           0U
#define  USE_HAL_USART_GET_LAST_ERRORS          0U
#define  USE_HAL_WWDG_GET_LAST_ERRORS           0U
#define  USE_HAL_XSPI_GET_LAST_ERRORS           0U

/* ########################## DMA Module Services Selection ############################# */
/**
  * @brief This is the list of modules that uses HAL DMA services
  */
#define USE_HAL_ADC_DMA                         0U
#define USE_HAL_AES_DMA                         0U
#define USE_HAL_CORDIC_DMA                      0U
#define USE_HAL_DAC_DMA                         0U
#define USE_HAL_DCMI_DMA                        0U
#define USE_HAL_FMAC_DMA                        0U
#define USE_HAL_HASH_DMA                        0U
#define USE_HAL_I2C_DMA                         0U
#define USE_HAL_JPEG_DMA                        0U
#define USE_HAL_LPTIM_DMA                       0U
#define USE_HAL_MDF_DMA                         0U
#define USE_HAL_PSSI_DMA                        0U
#define USE_HAL_SAI_DMA                         0U
#define USE_HAL_SMARTCARD_DMA                   0U
#define USE_HAL_SPI_DMA                         0U
#define USE_HAL_TIM_DMA                         0U
#define USE_HAL_UART_DMA                        0U
#define USE_HAL_USART_DMA                       0U
#define USE_HAL_XSPI_DMA                        0U

/* ################## COMP peripheral configuration ######################## */
/* Use comparator with EXTI (needed to generate system wake-up event and CPU event)
   Note: USE_HAL_EXTI_MODULE must be enabled */
#define USE_HAL_COMP_EXTI                       0U
/* Use comparators window mode feature */
#define USE_HAL_COMP_WINDOW_MODE                0U

/* ################## SPI peripheral configuration ######################### */

/* CRC FEATURE: Use to activate CRC feature inside HAL SPI Driver
 * Activated: CRC code is present inside driver
 * Deactivated: CRC code cleaned from driver
 */
#define USE_HAL_SPI_CRC                         0U

/* ################## MMC peripheral configuration ######################### */
/* Use the MMC in linked-list mode */
#define USE_HAL_MMC_LINKEDLIST                  0U
/* Enable or Disable MMC Custom Frequency */
#define USE_HAL_MMC_AUTO_DETECTION_FREQUENCY    0U

/* ################## SD peripheral configuration ######################### */
/* Use the SD in linked-list mode */
#define USE_HAL_SD_LINKEDLIST                   0U
/* Enable or Disable SD Custom Frequency */
#define USE_HAL_SD_AUTO_DETECTION_FREQUENCY     0U

/* #################### DMA peripheral configuration ######################### */
#define USE_HAL_DMA_LINKEDLIST                  0U

/* #################### DMA2D IRQ CLUT configuration ######################## */
#define USE_HAL_DMA2D_CLUT_IRQ                  0U

/* ################## XSPI peripheral configuration ######################### */
#define USE_HAL_XSPI_HYPERBUS                   0U

/* ################## DAC peripheral configuration ######################### */

#define USE_HAL_DAC_DUAL_CHANNEL                0U

/* ################## OPAMP peripheral configuration ######################### */

#define USE_HAL_OPAMP_CALIBRATE_PARALLEL        0U

/* ################## AES peripheral configuration ######################### */
#define USE_HAL_AES_ECB_CBC_ALGO                0U
#define USE_HAL_AES_CTR_ALGO                    0U
#define USE_HAL_AES_GCM_GMAC_ALGO               0U
#define USE_HAL_AES_CCM_ALGO                    0U
#define USE_HAL_AES_SUSPEND_RESUME              0U

/* ################## UCPD peripheral configuration ########################## */

#define USE_HAL_UCPD_POWER_DELIVERY             0U


/* ################## RNG peripheral configuration ########################## */
#define USE_HAL_RNG_FREE_RUNNING_MODE           0U

/* ################## FLASH peripheral configuration ######################### */
/* Use the FLASH programming by address feature */
#define USE_HAL_FLASH_PROGRAM_BY_ADDR           0U
/* Use the FLASH erasing by address feature */
#define USE_HAL_FLASH_ERASE_BY_ADDR             0U
/* Use the FLASH erasing by page feature */
#define USE_HAL_FLASH_ERASE_PAGE                0U
/* Use the FLASH bank erase feature */
#define USE_HAL_FLASH_ERASE_BANK                0U
/* Use the FLASH mass erase feature */
#define USE_HAL_FLASH_MASS_ERASE                0U
/* Use the FLASH ECC feature */
#define USE_HAL_FLASH_ECC                       0U

/* ################## xxx peripheral configuration ######################### */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*  STM32U5XX_HAL_CONF_H */
