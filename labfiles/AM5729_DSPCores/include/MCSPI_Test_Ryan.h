/*
 * MCSPI_Test_Ryan.h
 *
 *  Created on: Sep 24, 2019
 *      Author: rsomer2
 */

#ifndef MCSPI_TEST_RYAN_H_
#define MCSPI_TEST_RYAN_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include <stdio.h>
#include <ti/csl/csl_mcspi.h>
#include <ti/csl/csl_i2c.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/example/utils/common/inc/app_utils.h>

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
#define HSI2C_SLAVE_ADDR 0x21
#define SEL_UART3_SPI2   0x0E
#define UART_SEL1_3      0x0C
#define I2C_INT_NUM      56

#define MCSPI_POLLED_MODE      0

#define HSI2C_EN_SPI2      ((uint8_t) 0x40U)
#define HSI2C_ZERO      ((uint8_t) 0x00U)

#define MCSPI_OUT_FREQ              (5000000U)
#define MCSPI_IN_CLK                (48000000U)
#define McSPI_DATA_COUNT            16U // Data Count Transaction

#define MCSPI3_BASE_ADDRESS         (CSL_MPU_MCSPI3_REGS)
#define MCSPI4_BASE_ADDRESS         (CSL_MPU_MCSPI4_REGS)
#undef SOC_I2C1_BASE
#define SOC_I2C1_BASE CSL_MPU_I2C1_REGS


/** \brief EDMA3 channel for SPI1 Channel 0 Tx and Rx*/
#define MCSPI1_TX_EVENT                  (34U)
#define MCSPI1_RX_EVENT                  (35U)

/** \brief EDMA3 channel for SPI2 Channel 0 Tx and Rx*/
#define MCSPI2_TX_EVENT                  (42U)
#define MCSPI2_RX_EVENT                  (43U)

/** \brief MCSPI Tx/Rx buffer base address */
#define MCSPI1_TX0_REG                   (SOC_MCSPI1_BASE + (0x138U))
#define MCSPI1_RX0_REG                   (SOC_MCSPI1_BASE + (0x13CU))

#define MCSPI2_TX0_REG                   (SOC_MCSPI2_BASE + (0x138U))
#define MCSPI2_RX0_REG                   (SOC_MCSPI2_BASE + (0x13CU))

/** \brief MCSPI Channel number*/
#define MCSPI_CH_NUM                    (0U)

#define EVT_QUEQUE_NUM                  (0U)
#define DUMMY_CH_NUM                    (5U)

#define EDMA_TDA2XX_U_BASE              (SOC_EDMA_TPCC_BASE_VIRT)

#define EDMA3CC_PaRAM_BASE            (0x4000)
#define EDMA3CC_OPT(n)                (EDMA3CC_PaRAM_BASE + 0x0 + (0x20 * n))

#define EDMA3_CC_XFER_COMPLETION_INT_A15                (12U)
#define EDMA3_CC_XFER_COMPLETION_INT_M4                 (35U)

#define EDMA3_ERROR_INT_A15                              (14)
#define EDMA3_ERROR_INT_A15_1                            (15)
#define EDMA3_ERROR_INT_M4                               (36)
#define EDMA3_ERROR_INT_M4_1                             (37)

#define EDMA3_CC_REGION_A15                             (0U)
#define EDMA3_CC_REGION_M4                              (1U)

#define MCSPI_MASTERSLAVE_POLLED_MODE_TEST   ('1')
#define MCSPI_MASTERSLAVE_DMA_MODE_TEST      ('2')
#define EXIT(opt)                   (('x' == opt) || ('X' == opt))




#endif /* MCSPI_TEST_RYAN_H_ */
