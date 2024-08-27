/**
  **********************************************************************************************************************
  * @file    stm32u5xx_fmc_core.c
  * @author  GPM Application Team
  * @brief   FMC Low Layer HAL module driver.
  *
  *          This file provides firmware functions to manage the following functionalities of the Flexible Memory
  *          Controller (FMC):
  *           + Set the FMC registers configuration functions
  *           + Retrieve the FMC registers configuration functions
  *
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2021-2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

#if defined (FMC_BASE)

/** @addtogroup FMC_Core
  * @{
  */

#if (defined(USE_HAL_SRAM_MODULE) && (USE_HAL_SRAM_MODULE == 1)) \
    || (defined(USE_HAL_NOR_MODULE) && (USE_HAL_NOR_MODULE == 1U))

/** @defgroup FMC_Core_Private_Constants FMC Core Private Constants
  * @{
  */
/* BCR register configuration mask */
#define BCR_CFG_MSK (FMC_BCRx_MBKEN     | FMC_BCRx_MUXEN     | FMC_BCRx_MTYP     | \
                     FMC_BCRx_MWID      | FMC_BCRx_FACCEN    | FMC_BCRx_BURSTEN  | \
                     FMC_BCRx_WAITPOL   | FMC_BCRx_WAITCFG   | FMC_BCRx_WAITEN   | \
                     FMC_BCRx_EXTMOD    | FMC_BCRx_ASYNCWAIT | FMC_BCRx_CBURSTRW | \
                     FMC_BCR1_CCLKEN    | FMC_BCR1_WFDIS     | FMC_BCRx_NBLSET   | \
                     FMC_BCRx_CPSIZE    | FMC_BCRx_WREN)

/* BWTR register configuration mask */
#define BWTR_CFG_MASK (FMC_BWTRx_ADDSET  | FMC_BWTRx_ADDHLD |FMC_BWTRx_DATAST | \
                       FMC_BWTRx_BUSTURN | FMC_BWTRx_ACCMOD | FMC_BWTRx_DATAHLD)

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup FMC_Core_Exported_Functions
  * @{
This driver contains a set of APIs to interface with the FMC NORSRAM banks in order to run the NORSRAM external devices.
  */

/** @addtogroup FMC_CORE_NORSRAM_Exported_Functions
  * @{
This section provides functions allowing to:
  - Configure the FMC NORSRAM interface
  - Get the FMC NORSRAM interface configuration
  */

/**
  * @brief  Set the FMC NORSRAM device according to the specified memory parameters.
  * @param  p_instance  Pointer to NORSRAM device instance.
  * @param  memory_cfg  Contains the memory configuration information.
  * @param  counter_cfg Contains the counter configuration information.
  * @retval None
  */
void FMC_NOR_SRAM_SetConfigMemory(fmc_norsram_subbank_t *p_instance,
                                  uint32_t memory_cfg,
                                  uint32_t counter_cfg)
{
  uint32_t mask = 1UL << (((((uint32_t)p_instance % (uint32_t)FMC_NORSRAM1_SUBBANK1) / 8U) + FMC_PCSCNTR_CNTB1EN_Pos)
                          & 0x1FUL);

  MODIFY_REG(p_instance->BCR, BCR_CFG_MSK, (memory_cfg | FMC_BCRx_WREN));

  if (counter_cfg > 0U)
  {
    /* Configure PSRAM chip select counter value */
    MODIFY_REG(FMC_NORSRAM1_COMMON->PCSCNTR, FMC_PCSCNTR_CSCOUNT, counter_cfg);
    /* Enable the PSRAM chip select counter */
    SET_BIT(FMC_NORSRAM1_COMMON->PCSCNTR, mask);
  }
  else
  {
    /* Disable the PSRAM chip select counter */
    CLEAR_BIT(FMC_NORSRAM1_COMMON->PCSCNTR, mask);
  }

  /* Configure Write FIFO mode when Write Fifo is enabled for bank2..4 */
  if ((p_instance != FMC_NORSRAM1_SUBBANK1) && ((memory_cfg & FMC_BCR1_WFDIS) == FMC_WRITE_FIFO_ENABLE))
  {
    CLEAR_BIT(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_WFDIS);
  }
}

/**
  * @brief  Retrieve the FMC NORSRAM device memory parameters.
  * @param  p_instance    Pointer to NORSRAM device instance.
  * @param  p_memory_cfg  Contains the memory configuration information.
  * @param  p_counter_cfg Contains the counter configuration information.
  * @retval None
  */
void FMC_NOR_SRAM_GetConfigMemory(fmc_norsram_subbank_t *p_instance,
                                  uint32_t *p_memory_cfg,
                                  uint32_t *p_counter_cfg)
{
  uint32_t mask = 1UL << (((((uint32_t)p_instance % (uint32_t)FMC_NORSRAM1_SUBBANK1) / 8U) + FMC_PCSCNTR_CNTB1EN_Pos)
                          & 0x1FU);

  *p_memory_cfg = READ_REG(p_instance->BCR);

  /* Check FIFO configuration */
  if (READ_BIT(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_WFDIS) == 0U)
  {
    CLEAR_BIT(*p_memory_cfg, FMC_BCR1_WFDIS);
  }

  /* Get counter value */
  if (READ_BIT(FMC_NORSRAM1_COMMON->PCSCNTR, mask) == mask)
  {
    *p_counter_cfg = READ_BIT(FMC_NORSRAM1_COMMON->PCSCNTR, FMC_PCSCNTR_CSCOUNT);
  }
  else
  {
    *p_counter_cfg = 0;
  }
}

/**
  * @brief  Set the FMC NORSRAM device clock configuration.
  * @param  clock_cfg     Contains the clock configuration information.
  * @param  clock_div_cfg Contains the clock division configuration information.
  * @retval None
  */
void FMC_NOR_SRAM_SetClock(uint32_t clock_cfg, uint32_t clock_div_cfg)
{
  /* Configure the continuous clock when Continuous clock is enabled for bank2..4 */
  SET_BIT(FMC_NORSRAM1_SUBBANK1->BCR, clock_cfg);

  /* Align the clock div to the lowest frequency when the continuous clock is enabled */
  if (clock_cfg != 0U)
  {
    if (clock_div_cfg > READ_BIT(FMC_NORSRAM1_SUBBANK1->BTR, FMC_BTRx_CLKDIV))
    {
      MODIFY_REG(FMC_NORSRAM1_SUBBANK1->BTR, FMC_BTRx_CLKDIV, clock_div_cfg);
    }
  }
}

/**
  * @brief  Set the FMC NORSRAM device according to the specified timing parameters.
  * @param  p_instance    Pointer to NORSRAM device instance.
  * @param  control_cfg   Contains the control configuration information.
  * @param  timing_cfg    Contains the timing configuration information.
  * @param  wr_timing_cfg Contains the write timing configuration information.
  * @retval None
  */
void FMC_NOR_SRAM_SetTiming(fmc_norsram_subbank_t *p_instance,
                            uint32_t control_cfg,
                            uint32_t timing_cfg,
                            uint32_t wr_timing_cfg)
{
  /* Set the timing parameters */
  MODIFY_REG(p_instance->BCR, FMC_BCRx_ASYNCWAIT | FMC_BCRx_WAITEN | FMC_BCRx_EXTMOD | FMC_BCRx_CBURSTRW |
             FMC_BCRx_BURSTEN | FMC_BCRx_WAITCFG, control_cfg);
  WRITE_REG(p_instance->BTR, timing_cfg);
  MODIFY_REG(p_instance->BWTR, BWTR_CFG_MASK, wr_timing_cfg);
}

/**
  * @brief  Retrieve the FMC NORSRAM device timing parameters.
  * @param  p_instance      Pointer to NORSRAM device instance.
  * @param  p_control_cfg   Contains the control configuration information.
  * @param  p_timing_cfg    Contains the timing configuration information.
  * @param  p_wr_timing_cfg Contains the write timing configuration information.
  * @retval None
  */
void FMC_NOR_SRAM_GetTiming(fmc_norsram_subbank_t *p_instance,
                            uint32_t *p_control_cfg,
                            uint32_t *p_timing_cfg,
                            uint32_t *p_wr_timing_cfg)
{
  *p_control_cfg = READ_REG(p_instance->BCR);
  *p_timing_cfg = READ_REG(p_instance->BTR);

  /* Check continuous clock and clock div configuration */
  if (READ_BIT(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_CCLKEN) == FMC_BCR1_CCLKEN)
  {
    SET_BIT(*p_control_cfg, FMC_BCR1_CCLKEN);
    MODIFY_REG(*p_timing_cfg, FMC_BTRx_CLKDIV, READ_BIT(FMC_NORSRAM1_SUBBANK1->BTR, FMC_BTRx_CLKDIV));
  }

  if (READ_BIT(p_instance->BCR, FMC_BCRx_EXTMOD) == FMC_BCRx_EXTMOD)
  {
    *p_wr_timing_cfg = READ_REG(p_instance->BWTR);
  }
  else
  {
    *p_wr_timing_cfg = 0U;
  }
}

/**
  * @brief  Convert the timing parameters from nanoseconds to AHB clock cycle number.
  * @param  timing_nsec  The timing parameter in nanoseconds.
  * @param  hclk_freq_hz The HCLK frequency in Hz.
  * @retval timing parameter in AHB clock cycle number.
  */
uint32_t FMC_NOR_SRAM_GetAHBClockCycle(uint32_t timing_nsec, uint32_t hclk_freq_hz)
{
  uint32_t default_cycle = 0U;
  uint64_t temp = (uint64_t)timing_nsec * (uint64_t)hclk_freq_hz;

  if ((temp % 1000000000U) != 0U)
  {
    default_cycle++;
  }

  return (((uint32_t)(temp / 1000000000U)) + default_cycle);
}
/**
  * @}
  */

/**
  * @}
  */
#endif /* USE_HAL_SRAM_MODULE || USE_HAL_NOR_MODULE */

/**
  * @}
  */
#endif /* FMC_BASE */
