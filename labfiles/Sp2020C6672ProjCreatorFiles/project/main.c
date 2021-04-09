/*
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 *
 *  \brief  Template application main file:
 *          The main code initializes the platform , calls function
 *          to create application tasks and then starts BIOS.
 *          The initialization include Board specific
 *          initialization and initialization of used peripherals.
 *          The application specific task create function used here are
 *          defined in a separate file: app.c.
 */

/* Standard header files */
#include <string.h>

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Clock.h>

/* Board header file */
#include <ti/board/board.h>

/* Local template app header file */
#include "app.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

/* UART Header files */
#include <ti/drv/uart/UART.h>
#include <ti/drv/uart/src/UART_osal.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>

/* McSPI Test Header Files*/
#include "MCSPI_Test_Ryan.h"
#include "mcbspAsSpi_com.h"
#include "COECSL_registers.h"
#include "sharedmem_AM5729.h"

#include <ti/csl/csl_gpio.h>
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#include <ti/board/board.h>
#endif
//#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
//#include <ti/csl/arch/csl_arch.h>

#include "ti/csl/cslr_pwmss.h"
#include "ti/csl/cslr_eqep.h"

#include "projectinclude.h"

#define QEP_MAXVALUE 0xFFFFFFFF
/* general structures/enumerations */
enum eQep_e {
    EQEP1,
    EQEP2,
    EQEP3
};
typedef struct {
    enum eQep_e eq;
    int32_t cpr;
    int32_t pol;
    float res;
    float init_rad_coord;
} eqep_t;
eqep_t eqep1,eqep2,eqep3;

void init_EQEP(eqep_t *eqep, enum eQep_e eq, int32_t cpr, int32_t pol, float init_rad_coord);
float EQEP_read(eqep_t *eqep);

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define UART9_INSTANCE 8
#define XBAR_INST_UART9 CSL_XBAR_INST_DSP1_IRQ_44
#define XBAR_IRQ_UART9 CSL_XBAR_UART9_IRQ

#define UART10_INSTANCE 9
#define XBAR_INST_UART10 CSL_XBAR_INST_DSP1_IRQ_45
#define XBAR_IRQ_UART10 CSL_XBAR_UART10_IRQ

#define UART8_INSTANCE 7
#define XBAR_INST_UART8 CSL_XBAR_INST_DSP1_IRQ_43
#define XBAR_IRQ_UART8 CSL_XBAR_UART8_IRQ



#define uint32_t                unsigned int
#define WR_MEM_32(addr, data)   *(uint32_t*)(addr) =(uint32_t)(data)
#define RD_MEM_32(addr)         *(uint32_t*)(addr)

/* OPP definitions */
#define     OPP_NOM         (0x0)
#define     OPP_OD          (0x1)
#define     OPP_HIGH        (0x2)

#define     SYS_CLK1        (20)

/* DEVICE_TYPE definitions */
#define     DEVICE_AM572X_GP      (0x3)

/* DPLL Definitions */
#define DPLL_TIMEOUT                            5           // DPLL lock/unlock timeout (was 5000)
#define CM_CLKMODE_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS)
#define CM_IDLEST_DPLL(DPLL_BASE_ADDRESS)       RD_MEM_32(DPLL_BASE_ADDRESS + 0x04)
#define CM_AUTOIDLE_DPLL(DPLL_BASE_ADDRESS)     RD_MEM_32(DPLL_BASE_ADDRESS + 0x08)
#define CM_CLKSEL_DPLL(DPLL_BASE_ADDRESS)       RD_MEM_32(DPLL_BASE_ADDRESS + 0x0C)
#define CM_DIV_M2_DPLL(DPLL_BASE_ADDRESS)       RD_MEM_32(DPLL_BASE_ADDRESS + 0x10)
#define CM_DIV_M3_DPLL(DPLL_BASE_ADDRESS)       RD_MEM_32(DPLL_BASE_ADDRESS + 0x14)
#define CM_DIV_H11_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x18)
#define CM_DIV_H12_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x1C)
#define CM_DIV_H13_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x20)
#define CM_DIV_H14_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x24)
#define CM_DIV_H21_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x30)
#define CM_DIV_H22_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x34)
#define CM_DIV_H23_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x38)
#define CM_DIV_H24_DPLL(DPLL_BASE_ADDRESS)      RD_MEM_32(DPLL_BASE_ADDRESS + 0x3C)


/* Instance Base Addresses */
#define CTRL_MODULE_CORE    0x4a002000
#define CKGEN_CM_CORE_AON   0x4a005100
#define MPU_CM_CORE_AON     0x4a005300
#define DSP1_CM_CORE_AON    0x4a005400
#define IPU_CM_CORE_AON     0x4a005500
#define DSP2_CM_CORE_AON    0x4a005600
#define RTC_CM_CORE_AON     0x4a005740
#define VPE_CM_CORE_AON     0x4a005760
#define CKGEN_CM_CORE       0x4a008100
#define COREAON_CM_CORE     0x4a008600
#define CORE_CM_CORE        0x4a008700
#define IVA_CM_CORE         0x4a008f00
#define CAM_CM_CORE         0x4a009000
#define DSS_CM_CORE         0x4a009100
#define GPU_CM_CORE         0x4a009200
#define L3INIT_CM_CORE      0x4a009300
#define L4PER_CM_CORE       0x4a009700
#define CKGEN_PRM           0x4ae06100
#define WKUPAON_CM          0x4ae07800
#define EMU_CM              0x4ae07a00

/* CLKSTCTRL offsets */
#define CORE_CM_CORE__CM_L3MAIN1_CLKSTCTRL                        0x000ul
#define CORE_CM_CORE__CM_IPU2_CLKSTCTRL                           0x200ul
#define CORE_CM_CORE__CM_DMA_CLKSTCTRL                            0x300ul
#define CORE_CM_CORE__CM_EMIF_CLKSTCTRL                           0x400ul
#define CORE_CM_CORE__CM_L4CFG_CLKSTCTRL                          0x600ul
#define COREAON_CM_CORE__CM_COREAON_CLKSTCTRL                     0x00ul
#define DSP1_CM_CORE_AON__CM_DSP1_CLKSTCTRL                       0x00ul
#define DSP2_CM_CORE_AON__CM_DSP2_CLKSTCTRL                       0x00ul
#define DSS_CM_CORE__CM_DSS_CLKSTCTRL                             0x00ul
#define GPU_CM_CORE__CM_GPU_CLKSTCTRL                             0x00ul
#define IPU_CM_CORE_AON__CM_IPU1_CLKSTCTRL                        0x00ul
#define IPU_CM_CORE_AON__CM_IPU_CLKSTCTRL                         0x40ul
#define IVA_CM_CORE__CM_IVA_CLKSTCTRL                             0x00ul
#define CAM_CM_CORE__CM_CAM_CLKSTCTRL                             0x00ul
#define L3INIT_CM_CORE__CM_L3INIT_CLKSTCTRL                       0x00ul
#define L3INIT_CM_CORE__CM_PCIE_CLKSTCTRL                         0xA0ul
#define L3INIT_CM_CORE__CM_GMAC_CLKSTCTRL                         0xC0ul
#define L4PER_CM_CORE__CM_L4PER_CLKSTCTRL                         0x000ul
#define L4PER_CM_CORE__CM_L4PER2_CLKSTCTRL                        0x1FCul
#define L4PER_CM_CORE__CM_L4PER3_CLKSTCTRL                        0x210ul
#define MPU_CM_CORE_AON__CM_MPU_CLKSTCTRL                         0x00ul
#define RTC_CM_CORE_AON__CM_RTC_CLKSTCTRL                         0x00ul
#define VPE_CM_CORE_AON__CM_VPE_CLKSTCTRL                         0x00ul
#define WKUPAON_CM__CM_WKUPAON_CLKSTCTRL                          0x00ul

/* CLKSTCTRL modes */
#define SW_SLEEP        (0x1)
#define SW_WKUP         (0x2)
#define HW_AUTO         (0x3)

#define CLKSTCTRL_TIMEOUT  (300)

/* CLKCTRL Offsets */
#define CAM_CM_CORE__CM_CAM_VIP1_CLKCTRL                            0x020ul
#define CAM_CM_CORE__CM_CAM_VIP2_CLKCTRL                            0x028ul
#define CAM_CM_CORE__CM_CAM_VIP3_CLKCTRL                            0x030ul
#define CORE_CM_CORE__CM_L3MAIN1_L3_MAIN_1_CLKCTRL                  0x020ul
#define CORE_CM_CORE__CM_L3MAIN1_GPMC_CLKCTRL                       0x028ul
#define CORE_CM_CORE__CM_L3MAIN1_MMU_EDMA_CLKCTRL                   0x030ul
#define CORE_CM_CORE__CM_L3MAIN1_MMU_PCIESS_CLKCTRL                 0x048ul
#define CORE_CM_CORE__CM_L3MAIN1_OCMC_RAM1_CLKCTRL                  0x050ul
#define CORE_CM_CORE__CM_L3MAIN1_OCMC_RAM2_CLKCTRL                  0x058ul
#define CORE_CM_CORE__CM_L3MAIN1_OCMC_RAM3_CLKCTRL                  0x060ul
#define CORE_CM_CORE__CM_L3MAIN1_OCMC_ROM_CLKCTRL                   0x068ul
#define CORE_CM_CORE__CM_L3MAIN1_TPCC_CLKCTRL                       0x070ul
#define CORE_CM_CORE__CM_L3MAIN1_TPTC1_CLKCTRL                      0x078ul
#define CORE_CM_CORE__CM_L3MAIN1_TPTC2_CLKCTRL                      0x080ul
#define CORE_CM_CORE__CM_IPU2_IPU2_CLKCTRL                          0x220ul
#define CORE_CM_CORE__CM_DMA_DMA_SYSTEM_CLKCTRL                     0x320ul
#define CORE_CM_CORE__CM_EMIF_DMM_CLKCTRL                           0x420ul
#define CORE_CM_CORE__CM_EMIF_EMIF_OCP_FW_CLKCTRL                   0x428ul
#define CORE_CM_CORE__CM_EMIF_EMIF1_CLKCTRL                         0x430ul
#define CORE_CM_CORE__CM_EMIF_EMIF2_CLKCTRL                         0x438ul
#define CORE_CM_CORE__CM_L4CFG_L4_CFG_CLKCTRL                       0x620ul
#define CORE_CM_CORE__CM_L4CFG_SPINLOCK_CLKCTRL                     0x628ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX1_CLKCTRL                     0x630ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX2_CLKCTRL                     0x648ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX3_CLKCTRL                     0x650ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX4_CLKCTRL                     0x658ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX5_CLKCTRL                     0x660ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX6_CLKCTRL                     0x668ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX7_CLKCTRL                     0x670ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX8_CLKCTRL                     0x678ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX9_CLKCTRL                     0x680ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX10_CLKCTRL                    0x688ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX11_CLKCTRL                    0x690ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX12_CLKCTRL                    0x698ul
#define CORE_CM_CORE__CM_L4CFG_MAILBOX13_CLKCTRL                    0x6A0ul
#define CORE_CM_CORE__CM_L3INSTR_L3_MAIN_2_CLKCTRL                  0x720ul
#define DSS_CM_CORE__CM_DSS_DSS_CLKCTRL                             0x020ul
#define GPU_CM_CORE__CM_GPU_GPU_CLKCTRL                             0x020ul
#define EMU_CM__CM_EMU_MPU_EMU_DBG_CLKCTRL                          0x00Cul
#define IPU_CM_CORE_AON__CM_IPU1_IPU1_CLKCTRL                       0x020ul
#define IPU_CM_CORE_AON__CM_IPU_MCASP1_CLKCTRL                      0x050ul
#define IPU_CM_CORE_AON__CM_IPU_TIMER5_CLKCTRL                      0x058ul
#define IPU_CM_CORE_AON__CM_IPU_TIMER6_CLKCTRL                      0x060ul
#define IPU_CM_CORE_AON__CM_IPU_TIMER7_CLKCTRL                      0x068ul
#define IPU_CM_CORE_AON__CM_IPU_TIMER8_CLKCTRL                      0x070ul
#define IVA_CM_CORE__CM_IVA_IVA_CLKCTRL                             0x020ul
#define IVA_CM_CORE__CM_IVA_SL2_CLKCTRL                             0x028ul
#define L3INIT_CM_CORE__CM_L3INIT_MMC1_CLKCTRL                      0x028ul
#define L3INIT_CM_CORE__CM_L3INIT_MMC2_CLKCTRL                      0x030ul
#define L3INIT_CM_CORE__CM_L3INIT_IEEE1500_2_OCP_CLKCTRL            0x078ul
#define L3INIT_CM_CORE__CM_PCIE_PCIESS1_CLKCTRL                     0x0B0ul
#define L3INIT_CM_CORE__CM_GMAC_GMAC_CLKCTRL                        0x0D0ul
#define L3INIT_CM_CORE__CM_L3INIT_OCP2SCP1_CLKCTRL                  0x0E0ul
#define L3INIT_CM_CORE__CM_L3INIT_OCP2SCP3_CLKCTRL                  0x0E8ul
#define L4PER_CM_CORE__CM_L4PER2_L4_PER2_CLKCTRL                    0x00Cul
#define L4PER_CM_CORE__CM_L4PER3_L4_PER3_CLKCTRL                    0x014ul
#define L4PER_CM_CORE__CM_L4PER_TIMER10_CLKCTRL                     0x028ul
#define L4PER_CM_CORE__CM_L4PER_TIMER11_CLKCTRL                     0x030ul
#define L4PER_CM_CORE__CM_L4PER_TIMER2_CLKCTRL                      0x038ul
#define L4PER_CM_CORE__CM_L4PER_TIMER3_CLKCTRL                      0x040ul
#define L4PER_CM_CORE__CM_L4PER_TIMER4_CLKCTRL                      0x048ul
#define L4PER_CM_CORE__CM_L4PER_TIMER9_CLKCTRL                      0x050ul
#define L4PER_CM_CORE__CM_L4PER_GPIO2_CLKCTRL                       0x060ul
#define L4PER_CM_CORE__CM_L4PER_GPIO3_CLKCTRL                       0x068ul
#define L4PER_CM_CORE__CM_L4PER_GPIO4_CLKCTRL                       0x070ul
#define L4PER_CM_CORE__CM_L4PER_GPIO5_CLKCTRL                       0x078ul
#define L4PER_CM_CORE__CM_L4PER_GPIO6_CLKCTRL                       0x080ul
#define L4PER_CM_CORE__CM_L4PER_I2C1_CLKCTRL                        0x0A0ul
#define L4PER_CM_CORE__CM_L4PER_I2C2_CLKCTRL                        0x0A8ul
#define L4PER_CM_CORE__CM_L4PER_I2C3_CLKCTRL                        0x0B0ul
#define L4PER_CM_CORE__CM_L4PER_I2C4_CLKCTRL                        0x0B8ul
/*Dan Block Added */
#define L4PER_CM_CORE__CM_L4PER2_UART8_CLKCTRL                      0x1E0ul
#define L4PER_CM_CORE__CM_L4PER2_UART9_CLKCTRL                      0x1E8ul
#define L4PER_CM_CORE__CM_L4PER2_PWMSS1_CLKCTRL                     0x0C4ul
#define L4PER_CM_CORE__CM_L4PER2_PWMSS2_CLKCTRL                     0x090ul
#define L4PER_CM_CORE__CM_L4PER2_PWMSS3_CLKCTRL                     0x098ul
/* end Dan Block Added */
#define L4PER_CM_CORE__CM_L4PER_L4_PER1_CLKCTRL                     0x0C0ul
#define L4PER_CM_CORE__CM_L4PER3_TIMER13_CLKCTRL                    0x0C8ul
#define L4PER_CM_CORE__CM_L4PER3_TIMER14_CLKCTRL                    0x0D0ul
#define L4PER_CM_CORE__CM_L4PER3_TIMER15_CLKCTRL                    0x0D8ul
#define L4PER_CM_CORE__CM_L4PER_MCSPI1_CLKCTRL                      0x0F0ul
#define L4PER_CM_CORE__CM_L4PER_MCSPI2_CLKCTRL                      0x0F8ul
#define L4PER_CM_CORE__CM_L4PER_MCSPI3_CLKCTRL                      0x100ul
#define L4PER_CM_CORE__CM_L4PER_MCSPI4_CLKCTRL                      0x108ul
#define L4PER_CM_CORE__CM_L4PER_GPIO7_CLKCTRL                       0x110ul
#define L4PER_CM_CORE__CM_L4PER_GPIO8_CLKCTRL                       0x118ul
#define L4PER_CM_CORE__CM_L4PER_MMC3_CLKCTRL                        0x120ul
#define L4PER_CM_CORE__CM_L4PER_MMC4_CLKCTRL                        0x128ul
#define L4PER_CM_CORE__CM_L4PER3_TIMER16_CLKCTRL                    0x130ul
#define L4PER_CM_CORE__CM_L4PER2_QSPI_CLKCTRL                       0x138ul
#define L4PER_CM_CORE__CM_L4PER_UART1_CLKCTRL                       0x140ul
#define L4PER_CM_CORE__CM_L4PER_UART3_CLKCTRL                       0x150ul
#define MPU_CM_CORE_AON__CM_MPU_MPU_CLKCTRL                         0x020ul
#define MPU_CM_CORE_AON__CM_MPU_MPU_MPU_DBG_CLKCTRL                 0x028ul
#define VPE_CM_CORE_AON__CM_VPE_VPE_CLKCTRL                         0x004ul
#define WKUPAON_CM__CM_WKUPAON_WD_TIMER1_CLKCTRL                    0x028ul
#define WKUPAON_CM__CM_WKUPAON_WD_TIMER2_CLKCTRL                    0x030ul
#define WKUPAON_CM__CM_WKUPAON_GPIO1_CLKCTRL                        0x038ul
#define WKUPAON_CM__CM_WKUPAON_TIMER1_CLKCTRL                       0x040ul
#define WKUPAON_CM__CM_WKUPAON_TIMER12_CLKCTRL                      0x048ul
#define WKUPAON_CM__CM_WKUPAON_UART10_CLKCTRL                       0x080ul

/* CLKCTRL modes */
#define MODE_DISABLED   (0x0)
#define MODE_AUTO       (0x1)
#define MODE_ENABLED    (0x2)

#define CLKCTRL_TIMEOUT  (300)

/* Various register address definitions */
//#define GEL_CM_CLKSEL_CORE              (CKGEN_CM_CORE_AON + 0x000)
//#define GEL_CM_CLKSEL_ABE               (CKGEN_CM_CORE_AON + 0x008)
//#define GEL_CM_DLL_CTRL                 (CKGEN_CM_CORE_AON + 0x010)
//#define GEL_CM_CLKMODE_DPLL_CORE        (CKGEN_CM_CORE_AON + 0x020)
//#define GEL_CM_CLKSEL_DPLL_CORE         (CKGEN_CM_CORE_AON + 0x02C)
//#define GEL_CM_CLKMODE_DPLL_MPU         (CKGEN_CM_CORE_AON + 0x060)
//#define GEL_CM_CLKMODE_DPLL_IVA         (CKGEN_CM_CORE_AON + 0x0A0)
//#define GEL_CM_CLKMODE_DPLL_ABE         (CKGEN_CM_CORE_AON + 0x0E0)
//#define GEL_CM_CLKMODE_DPLL_DDR         (CKGEN_CM_CORE_AON + 0x110)
//#define GEL_CM_CLKMODE_DPLL_DSP         (CKGEN_CM_CORE_AON + 0x134)
//#define GEL_CM_CLKMODE_DPLL_GMAC        (CKGEN_CM_CORE_AON + 0x1A8)
//#define GEL_CM_CLKMODE_DPLL_GPU         (CKGEN_CM_CORE_AON + 0x1D8)
//#define GEL_CM_CLKMODE_DPLL_PER         (CKGEN_CM_CORE     + 0x040)
//#define GEL_CM_CLKMODE_DPLL_PCIE_REF    (CKGEN_CM_CORE     + 0x100)
//#define GEL_CM_SYS_CLKSEL               (CKGEN_PRM         + 0x010)

#define GEL_CTRL_CORE_CONTROL_IO_2      (CTRL_MODULE_CORE  + 0x558)



/**********************************************************************
 *
 *  FUNCTIONS
 *
 **********************************************************************/
void prcm_set_dss_mode(uint32_t module_base, uint32_t module_offset, uint32_t mode);
void prcm_set_proc_mode(uint32_t module_base, uint32_t module_offset, uint32_t mode);
void prcm_set_ipu1_mode(uint32_t module_base, uint32_t module_offset, uint32_t mode);
void prcm_set_module_mode(uint32_t module_base, uint32_t module_offset, uint32_t mode, uint32_t extrabits, uint32_t extrabitsMask);
void prcm_set_clkdomain_state(uint32_t module_base, uint32_t module_offset, uint32_t state);


void AM572x_PRCM_Module_AllEnable_Config(void)
{

    /* PRCM clock domain state setting functions */
    prcm_set_clkdomain_state(CAM_CM_CORE,       CAM_CM_CORE__CM_CAM_CLKSTCTRL,          SW_WKUP );
    prcm_set_clkdomain_state(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_CLKSTCTRL,      SW_WKUP );
    prcm_set_clkdomain_state(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER2_CLKSTCTRL,     SW_WKUP );
    prcm_set_clkdomain_state(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER3_CLKSTCTRL,     SW_WKUP );
    prcm_set_clkdomain_state(L3INIT_CM_CORE,    L3INIT_CM_CORE__CM_L3INIT_CLKSTCTRL,    SW_WKUP );
    prcm_set_clkdomain_state(L3INIT_CM_CORE,    L3INIT_CM_CORE__CM_GMAC_CLKSTCTRL,      SW_WKUP );
    prcm_set_clkdomain_state(CORE_CM_CORE,      CORE_CM_CORE__CM_EMIF_CLKSTCTRL,        SW_WKUP );
    prcm_set_clkdomain_state(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_CLKSTCTRL,       SW_WKUP );
    prcm_set_clkdomain_state(CORE_CM_CORE,      CORE_CM_CORE__CM_DMA_CLKSTCTRL,         SW_WKUP );
    prcm_set_clkdomain_state(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_CLKSTCTRL,     SW_WKUP );
    prcm_set_clkdomain_state(CORE_CM_CORE,      CORE_CM_CORE__CM_IPU2_CLKSTCTRL,        SW_WKUP );
    prcm_set_clkdomain_state(COREAON_CM_CORE,   COREAON_CM_CORE__CM_COREAON_CLKSTCTRL,  SW_WKUP );
    prcm_set_clkdomain_state(DSS_CM_CORE,       DSS_CM_CORE__CM_DSS_CLKSTCTRL,          SW_WKUP );
    prcm_set_clkdomain_state(IPU_CM_CORE_AON,   IPU_CM_CORE_AON__CM_IPU1_CLKSTCTRL,     SW_WKUP );
    prcm_set_clkdomain_state(IPU_CM_CORE_AON,   IPU_CM_CORE_AON__CM_IPU_CLKSTCTRL,      SW_WKUP );
    prcm_set_clkdomain_state(RTC_CM_CORE_AON,   RTC_CM_CORE_AON__CM_RTC_CLKSTCTRL,      SW_WKUP );
    prcm_set_clkdomain_state(VPE_CM_CORE_AON,   VPE_CM_CORE_AON__CM_VPE_CLKSTCTRL,      SW_WKUP );
    prcm_set_clkdomain_state(WKUPAON_CM,        WKUPAON_CM__CM_WKUPAON_CLKSTCTRL,       SW_WKUP );
    prcm_set_clkdomain_state(MPU_CM_CORE_AON,   MPU_CM_CORE_AON__CM_MPU_CLKSTCTRL,      SW_WKUP );
    prcm_set_clkdomain_state(DSP1_CM_CORE_AON,  DSP1_CM_CORE_AON__CM_DSP1_CLKSTCTRL,    SW_WKUP );
    prcm_set_clkdomain_state(DSP2_CM_CORE_AON,  DSP2_CM_CORE_AON__CM_DSP2_CLKSTCTRL,    SW_WKUP );
    prcm_set_clkdomain_state(IVA_CM_CORE,       IVA_CM_CORE__CM_IVA_CLKSTCTRL,          SW_WKUP );

    /* PRCM Generic module mode setting functions */
    prcm_set_module_mode(CAM_CM_CORE,       CAM_CM_CORE__CM_CAM_VIP1_CLKCTRL,               MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CAM_CM_CORE,       CAM_CM_CORE__CM_CAM_VIP2_CLKCTRL,               MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CAM_CM_CORE,       CAM_CM_CORE__CM_CAM_VIP3_CLKCTRL,               MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_DMA_DMA_SYSTEM_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_EMIF_DMM_CLKCTRL,              MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_EMIF_EMIF1_CLKCTRL,            MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_EMIF_EMIF2_CLKCTRL,            MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_EMIF_EMIF_OCP_FW_CLKCTRL,      MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3INSTR_L3_MAIN_2_CLKCTRL,     MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_GPMC_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_L3_MAIN_1_CLKCTRL,     MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_MMU_EDMA_CLKCTRL,      MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_MMU_PCIESS_CLKCTRL,    MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_OCMC_RAM1_CLKCTRL,     MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_OCMC_RAM2_CLKCTRL,     MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_OCMC_RAM3_CLKCTRL,     MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_OCMC_ROM_CLKCTRL,      MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_TPCC_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_TPTC1_CLKCTRL,         MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L3MAIN1_TPTC2_CLKCTRL,         MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_L4_CFG_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX1_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX10_CLKCTRL,       MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX11_CLKCTRL,       MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX12_CLKCTRL,       MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX13_CLKCTRL,       MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX2_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX3_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX4_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX5_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX6_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX7_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX8_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_MAILBOX9_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(CORE_CM_CORE,      CORE_CM_CORE__CM_L4CFG_SPINLOCK_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );

    /*
    prcm_set_module_mode(IPU_CM_CORE_AON,   IPU_CM_CORE_AON__CM_IPU_MCASP1_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    */

    prcm_set_module_mode(IPU_CM_CORE_AON,   IPU_CM_CORE_AON__CM_IPU_TIMER5_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(IPU_CM_CORE_AON,   IPU_CM_CORE_AON__CM_IPU_TIMER6_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(IPU_CM_CORE_AON,   IPU_CM_CORE_AON__CM_IPU_TIMER7_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(IPU_CM_CORE_AON,   IPU_CM_CORE_AON__CM_IPU_TIMER8_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L3INIT_CM_CORE,    L3INIT_CM_CORE__CM_L3INIT_MMC1_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L3INIT_CM_CORE,    L3INIT_CM_CORE__CM_L3INIT_MMC2_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L3INIT_CM_CORE,    L3INIT_CM_CORE__CM_GMAC_GMAC_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER2_L4_PER2_CLKCTRL,       MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER3_L4_PER3_CLKCTRL,       MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER3_TIMER13_CLKCTRL,       MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER3_TIMER14_CLKCTRL,       MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER3_TIMER15_CLKCTRL,       MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER3_TIMER16_CLKCTRL,       MODE_ENABLED,   0x00000000, 0x00000000  );


    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO2_CLKCTRL,          MODE_ENABLED,      0x00000000, 0x00000000  );
    /*
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO3_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO4_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO5_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO6_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO7_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_GPIO8_CLKCTRL,          MODE_AUTO,      0x00000000, 0x00000000  );
    */

    /*
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_I2C1_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_I2C2_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_I2C3_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_I2C4_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_L4_PER1_CLKCTRL,        MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_MCSPI1_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_MMC3_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_MMC4_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_TIMER10_CLKCTRL,        MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_TIMER11_CLKCTRL,        MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_TIMER2_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_TIMER3_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_TIMER4_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_TIMER9_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    */

    /* Dan Block Added */
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_MCSPI3_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_MCSPI4_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER2_UART8_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER2_UART9_CLKCTRL,           MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER2_PWMSS1_CLKCTRL,        MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER2_PWMSS2_CLKCTRL,        MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER2_PWMSS3_CLKCTRL,        MODE_ENABLED,   0x00000000, 0x00000000  );

    /* End Dan Block Added */

    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER2_QSPI_CLKCTRL,          MODE_ENABLED,   0x05000000, 0x07000000  );

    /*
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_UART1_CLKCTRL,          MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(L4PER_CM_CORE,     L4PER_CM_CORE__CM_L4PER_UART3_CLKCTRL,          MODE_ENABLED,   0x00000000, 0x00000000  );
    */

    prcm_set_module_mode(MPU_CM_CORE_AON,   MPU_CM_CORE_AON__CM_MPU_MPU_CLKCTRL,            MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(VPE_CM_CORE_AON,   VPE_CM_CORE_AON__CM_VPE_VPE_CLKCTRL,            MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(WKUPAON_CM,        WKUPAON_CM__CM_WKUPAON_GPIO1_CLKCTRL,           MODE_AUTO,      0x00000000, 0x00000000  );
    prcm_set_module_mode(WKUPAON_CM,        WKUPAON_CM__CM_WKUPAON_TIMER1_CLKCTRL,          MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(WKUPAON_CM,        WKUPAON_CM__CM_WKUPAON_TIMER12_CLKCTRL,         MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(WKUPAON_CM,        WKUPAON_CM__CM_WKUPAON_WD_TIMER1_CLKCTRL,       MODE_ENABLED,   0x00000000, 0x00000000  );
    prcm_set_module_mode(WKUPAON_CM,        WKUPAON_CM__CM_WKUPAON_WD_TIMER2_CLKCTRL,       MODE_ENABLED,   0x00000000, 0x00000000  );

    /* Dan Block Added */
    prcm_set_module_mode(WKUPAON_CM,        WKUPAON_CM__CM_WKUPAON_UART10_CLKCTRL,       MODE_ENABLED,   0x00000000, 0x00000000  );
    /*  End Dan Block Added */

    /* PRCM Specialized module mode setting functions */
    prcm_set_proc_mode(IVA_CM_CORE,         IVA_CM_CORE__CM_IVA_SL2_CLKCTRL,                MODE_AUTO                   );
    prcm_set_proc_mode(IVA_CM_CORE,         IVA_CM_CORE__CM_IVA_IVA_CLKCTRL,                MODE_AUTO                   );
    prcm_set_proc_mode(CORE_CM_CORE,        CORE_CM_CORE__CM_IPU2_IPU2_CLKCTRL,             MODE_AUTO                   );
    prcm_set_dss_mode(DSS_CM_CORE,          DSS_CM_CORE__CM_DSS_DSS_CLKCTRL,                MODE_ENABLED                );
    prcm_set_ipu1_mode(IPU_CM_CORE_AON,     IPU_CM_CORE_AON__CM_IPU1_IPU1_CLKCTRL,          MODE_AUTO                   );


}

void prcm_set_dss_mode(uint32_t module_base, uint32_t module_offset, uint32_t mode)
{
    uint32_t reg_val;
    uint32_t timeout = CLKCTRL_TIMEOUT;

    /* DESHDCP Clock ENABLE for DSS */
    WR_MEM_32(GEL_CTRL_CORE_CONTROL_IO_2, RD_MEM_32(GEL_CTRL_CORE_CONTROL_IO_2) | 0x1);

    reg_val = RD_MEM_32(module_base + module_offset);
    reg_val = (reg_val & ~0x3) | 0x00003F00 | mode;
    WR_MEM_32(module_base + module_offset, reg_val);

    while(((RD_MEM_32(module_base + module_offset) & 0x00030000) != 0) && (timeout>0))
    {
        timeout--;
    }
}

void prcm_set_proc_mode(uint32_t module_base, uint32_t module_offset, uint32_t mode)
{
    uint32_t reg_val;
    uint32_t timeout = CLKCTRL_TIMEOUT;

    reg_val = RD_MEM_32(module_base + module_offset);
    reg_val = (reg_val & ~0x3) | mode;
    WR_MEM_32(module_base + module_offset, reg_val);

    while(((RD_MEM_32(module_base + module_offset) & 0x00030000) == 0x00030000) && (timeout>0))
    {
        timeout--;
    }
}

void prcm_set_ipu1_mode(uint32_t module_base, uint32_t module_offset, uint32_t mode)
{
    uint32_t reg_val;
    uint32_t timeout = CLKCTRL_TIMEOUT;

    reg_val = RD_MEM_32(module_base + module_offset);
    reg_val = (reg_val & ~0x3) | 0x01000000 | mode;
    WR_MEM_32(module_base + module_offset, reg_val);

    while(((RD_MEM_32(module_base + module_offset) & 0x00030000) == 0x00030000) && (timeout>0))
    {
        timeout--;
    }
}

void prcm_set_module_mode(uint32_t module_base, uint32_t module_offset, uint32_t mode, uint32_t extrabits, uint32_t extrabitsMask)
{
    uint32_t reg_val;
    uint32_t timeout = CLKCTRL_TIMEOUT;

    reg_val = RD_MEM_32(module_base + module_offset) & ~(extrabitsMask | 0x00000003);
    WR_MEM_32(module_base+module_offset, (reg_val | (extrabits & extrabitsMask) | (mode & 0x3)));

    while(((RD_MEM_32(module_base + module_offset) & 0x00030000) != 0) && (timeout>0))
    {
        timeout--;
    }

}

void prcm_set_clkdomain_state(uint32_t module_base, uint32_t module_offset, uint32_t state)
{
    uint32_t reg_val;
    //uint32_t timeout = CLKSTCTRL_TIMEOUT;

    reg_val = RD_MEM_32(module_base+module_offset);
    WR_MEM_32(module_base+module_offset, ((reg_val & ~(0x3)) | (state & 0x3)));

    /*
    Dan Block This was commented out also in the gel file Don't know why
    while( ((RD_MEM_32(module_base + module_offset) & 0x100) != 0x100) && (timeout>0) )
    {
        timeout--;
    }
    */
}


volatile int delaycount = 5000000;
void Watchdog_disable(void)
{
    /* Enable clock */
    WR_MEM_32(0x4AE07830, 0x02);

    // Need a delay here before checking and disabling
    while(delaycount > 0) {
        delaycount--;
    }

    /* Check that module is Idle */
    while (((*(int *)0x4AE07830) & 0x20000));

    /* Disable  watchdog 2 */
    /* Wait until reset complete */
    while (!((*(int *)0x4AE14014) & 0x01));

    /* Disable watchdog timer */
    WR_MEM_32(0x4AE14048, 0x0000AAAA);

    while (((*(int *)0x4AE14034) & 0x10));

    /* Disable 32Khz watchdog timer */
    WR_MEM_32(0x4AE14048, 0x00005555);

    while (((*(int *)0x4AE14034) & 0x10));

}


void initForGPIO2Interrupt(void);
uint32_t gpio_base_address = SOC_GPIO2_BASE;
uint32_t gpio_pin          = 25;
uint32_t interrupt_num     = 56; // Try 56 first either 56 or 25 ??;
//uint32_t xbar_cfg_required = 0; ??
#define IRQ_XBAR_CFG_REQUIRED 1
#define IRQ_XBAR_CPU_ID       CSL_XBAR_IRQ_CPU_ID_DSP1
#define IRQ_XBAR_INST_NO      CSL_XBAR_INST_DSP1_IRQ_56
#define IRQ_XBAR_INDEX        CSL_XBAR_GPIO2_IRQ_1


/* ========================================================================== */
/*                          Internal Function Declarations                    */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
UART_Handle uart10_handle;
UART_Handle uart9_handle;
UART_Handle uart8_handle;

/* UART parameters structure polled mode*/
const UART_Params user_params_uart10 = {
    UART_MODE_BLOCKING,     /* readMode */
    UART_MODE_BLOCKING,     /* writeMode */
    SemaphoreP_WAIT_FOREVER,/* readTimeout */
    SemaphoreP_WAIT_FOREVER,/* writeTimeout */
    NULL,                  /* readCallback */
    NULL,                 /* writeCallback */
    UART_RETURN_NEWLINE,  /* readReturnMode */
    UART_DATA_BINARY,       /* readDataMode */
    UART_DATA_BINARY,       /* writeDataMode */
    UART_ECHO_OFF,         /* readEcho */
    115200,               /* baudRate */
    UART_LEN_8,           /* dataLength */
    UART_STOP_ONE,        /* stopBits */
    UART_PAR_NONE         /* parityType */
};

/* UART parameters structure polled mode*/
const UART_Params user_params_uart9 = {
    UART_MODE_BLOCKING,     /* readMode */
    UART_MODE_BLOCKING,     /* writeMode */
    SemaphoreP_WAIT_FOREVER,/* readTimeout */
    SemaphoreP_WAIT_FOREVER,/* writeTimeout */
    NULL,                  /* readCallback */
    NULL,                 /* writeCallback */
    UART_RETURN_NEWLINE,  /* readReturnMode */
    UART_DATA_BINARY,       /* readDataMode */
    UART_DATA_BINARY,       /* writeDataMode */
    UART_ECHO_OFF,         /* readEcho */
    115200,               /* baudRate */
    UART_LEN_8,           /* dataLength */
    UART_STOP_ONE,        /* stopBits */
    UART_PAR_NONE         /* parityType */
};

/* UART parameters structure polled mode*/
const UART_Params user_params_uart8 = {
    UART_MODE_BLOCKING,     /* readMode */
    UART_MODE_BLOCKING,     /* writeMode */
    SemaphoreP_WAIT_FOREVER,/* readTimeout */
    SemaphoreP_WAIT_FOREVER,/* writeTimeout */
    NULL,                  /* readCallback */
    NULL,                 /* writeCallback */
    UART_RETURN_NEWLINE,  /* readReturnMode */
    UART_DATA_BINARY,       /* readDataMode */
    UART_DATA_BINARY,       /* writeDataMode */
    UART_ECHO_OFF,         /* readEcho */
    115200,               /* baudRate */
    UART_LEN_8,           /* dataLength */
    UART_STOP_ONE,        /* stopBits */
    UART_PAR_NONE         /* parityType */
};


//=====================McSPI //
extern uint8_t           lastTransferComplete;
extern uint32_t          gChNum;
extern uint8_t           dataFromSlave;
extern uint32_t           rxBuffer[McSPI_DATA_COUNT + 10];
extern uint32_t           txBuffer[McSPI_DATA_COUNT + 10];

extern uint32_t          *p_rx;
extern uint32_t          *p_tx;

//extern uint32_t           CS0dataToSend[McSPI_DATA_COUNT+10];
//extern uint32_t           CS1dataToSend[McSPI_DATA_COUNT+10];
//extern uint32_t           CS2dataToSend[McSPI_DATA_COUNT+10];
//extern uint32_t           CS3dataToSend[McSPI_DATA_COUNT+10];
//extern uint32_t           CS0dataReceived[McSPI_DATA_COUNT+10];
//extern uint32_t           CS1dataReceived[McSPI_DATA_COUNT+10];
//extern uint32_t           CS2dataReceived[McSPI_DATA_COUNT+10];
//extern uint32_t           CS3dataReceived[McSPI_DATA_COUNT+10];

extern mcbspL138_com CS0dataToSend;
extern mcbspL138_com CS1dataToSend;
extern mcbspL138_com CS2dataToSend;
extern mcbspL138_com CS3dataToSend;

extern mcbsp28x_com CS0dataReceived;
extern mcbsp28x_com CS1dataReceived;
extern mcbsp28x_com CS2dataReceived;
extern mcbsp28x_com CS3dataReceived;

extern uint8_t           length;
extern uint8_t           CS0size;
extern uint8_t           CS1size;
extern uint8_t           CS2size;
extern uint8_t           CS3size;

//MCSPI Test Ryan
void McSPISetUp(uint32_t base_address, uint8_t InterruptMode);
void McSPIStartTransfer(uint32_t base_address, uint8_t InterruptMode);
void McSPIInitializeBuffers(void);
void sampleDelay(int32_t delay);
void McSPIMSPolledModeTransfer(uint32_t base_address);
void McSPIMSInterruptModeTransfer(uint32_t base_address);
//End MCSPI Test Ryan

/**********************************************************************
 ************************** Function prototypes ***********************
 **********************************************************************/
void appExitFunction(Int argument);
void peripheralInit(void);

char input = '\n';
char buffPointer[1000];
char echoPrompt[] = "\n\ruart driver example test:\n\rEnter some data or press the esc \n\r";
char echoPrompt1[] = "D ";
uint32_t Dan_gpio2_25 = 0;
uint32_t Dan_NumGPIO2Ints = 0;
int Dan_count = 0;
int Dan_stringsize = 0;

uint32_t DanIntStatusBefore = 0;
uint32_t DanRawIntBefore = 0;
uint32_t DanIntStatusAfter = 0;
uint32_t DanRawIntAfter = 0;

uint32_t DanEnc1Raw = 0;
char sendbuff[200];
void uart_test(void)
{
    UART_Params      uart10_params;
    UART_Params      uart9_params;
    UART_Params      uart8_params;
    float enc1 = 0.0;
    float enc2 = 0.0;
    float enc3 = 0.0;

//    int32_t count;
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_DSP1,XBAR_INST_UART10,XBAR_IRQ_UART10);
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_DSP1,XBAR_INST_UART9,XBAR_IRQ_UART9);
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_DSP1,XBAR_INST_UART8,XBAR_IRQ_UART8);

    UART_init();
    uart10_params = user_params_uart10;
    uart9_params = user_params_uart9;
    uart8_params = user_params_uart8;
    uart10_handle = UART_open(UART10_INSTANCE, &uart10_params);
    uart9_handle = UART_open(UART9_INSTANCE, &uart9_params);
    uart8_handle = UART_open(UART8_INSTANCE, &uart8_params);


    UART_writePolling(uart10_handle,echoPrompt,sizeof(echoPrompt));
    UART_writePolling(uart9_handle,echoPrompt,sizeof(echoPrompt));
    UART_writePolling(uart8_handle,echoPrompt,sizeof(echoPrompt));

    while(1)
       {

        Dan_gpio2_25 = GPIOPinRead(gpio_base_address, gpio_pin);
        enc1 = EQEP_read(&eqep1);
        enc2 = EQEP_read(&eqep2);
        enc3 = EQEP_read(&eqep3);


        //        count=UART_read(uart_handle,buffPointer,1000);
        //        UART_write(uart_handle,&input,1U);
        ///        UART_write(uart_handle,echoPrompt1,sizeof(echoPrompt1));
        //       UART_write(uart_handle,buffPointer,count);

        Dan_stringsize = sprintf(sendbuff,"%x %x B1 %.4f,B2 %.4f,P2_25=0x%x %.4f %d %.4f %.4f\n\r",CS0dataReceived.data.validcode,CS0dataReceived.data.flags,CS0dataReceived.data.ADC[1]*3.0/4095.0,CS0dataReceived.data.ADC[3]*3.0/4095.0,Dan_gpio2_25,enc1,DanEnc1Raw,enc2,enc3);

        //UART_writePolling(uart10_handle,echoPrompt1,sizeof(echoPrompt1));
        //UART_writePolling(uart9_handle,echoPrompt1,sizeof(echoPrompt1));
        //UART_writePolling(uart8_handle,echoPrompt1,sizeof(echoPrompt1));
        GPIO_write(GPIO_DAN_LED1, GPIO_PIN_VAL_HIGH);
        UART_writePolling(uart10_handle,sendbuff,Dan_stringsize);
        GPIO_write(GPIO_DAN_LED1, GPIO_PIN_VAL_LOW);
        UART_writePolling(uart9_handle,sendbuff,Dan_stringsize);
        UART_writePolling(uart8_handle,sendbuff,Dan_stringsize);
        Dan_count++;

        Task_sleep(1000);
       }
}


/* init_EQEP(): initialize quadrature encoder pulse QEP
 *
 * parameters:
 *    eqep   = address pointer to QEP structure
 *    eq    = EQEP 1 or 2
 *    cpr   = encoder's rated counts per revolution
 *    init_rad_coord = initial radian coordinate for 0 encoder count
 *
 */
void init_EQEP(eqep_t *eqep, enum eQep_e eq, int cpr, int pol, float init_rad_coord)
{

    uint32_t EQEP1_CTL_addr = CSL_DSP_PWMSS1_IEQEP_REGS+CSL_EQEP_QEPCTL;
    uint32_t EQEP1_CAPCTL_addr = CSL_DSP_PWMSS1_IEQEP_REGS+CSL_EQEP_QCAPCTL;
    uint32_t EQEP1_DECCTL_addr = CSL_DSP_PWMSS1_IEQEP_REGS+CSL_EQEP_QDECCTL;
    uint32_t EQEP1_POSCTL_addr = CSL_DSP_PWMSS1_IEQEP_REGS+CSL_EQEP_QPOSCTL;
    uint32_t EQEP1_EINT_addr = CSL_DSP_PWMSS1_IEQEP_REGS+CSL_EQEP_QEINT;
    uint32_t EQEP1_QPOSMAX_addr = CSL_DSP_PWMSS1_IEQEP_REGS+CSL_EQEP_QPOSMAX;

    uint32_t EQEP2_CTL_addr = CSL_DSP_PWMSS2_IEQEP_REGS+CSL_EQEP_QEPCTL;
    uint32_t EQEP2_CAPCTL_addr = CSL_DSP_PWMSS2_IEQEP_REGS+CSL_EQEP_QCAPCTL;
    uint32_t EQEP2_DECCTL_addr = CSL_DSP_PWMSS2_IEQEP_REGS+CSL_EQEP_QDECCTL;
    uint32_t EQEP2_POSCTL_addr = CSL_DSP_PWMSS2_IEQEP_REGS+CSL_EQEP_QPOSCTL;
    uint32_t EQEP2_EINT_addr = CSL_DSP_PWMSS2_IEQEP_REGS+CSL_EQEP_QEINT;
    uint32_t EQEP2_QPOSMAX_addr = CSL_DSP_PWMSS2_IEQEP_REGS+CSL_EQEP_QPOSMAX;

    uint32_t EQEP3_CTL_addr = CSL_DSP_PWMSS3_IEQEP_REGS+CSL_EQEP_QEPCTL;
    uint32_t EQEP3_CAPCTL_addr = CSL_DSP_PWMSS3_IEQEP_REGS+CSL_EQEP_QCAPCTL;
    uint32_t EQEP3_DECCTL_addr = CSL_DSP_PWMSS3_IEQEP_REGS+CSL_EQEP_QDECCTL;
    uint32_t EQEP3_POSCTL_addr = CSL_DSP_PWMSS3_IEQEP_REGS+CSL_EQEP_QPOSCTL;
    uint32_t EQEP3_EINT_addr = CSL_DSP_PWMSS3_IEQEP_REGS+CSL_EQEP_QEINT;
    uint32_t EQEP3_QPOSMAX_addr = CSL_DSP_PWMSS3_IEQEP_REGS+CSL_EQEP_QPOSMAX;

    eqep->eq = eq;
    eqep->cpr = 4*cpr;
    eqep->init_rad_coord = init_rad_coord;
    eqep->res = (2*M_PI)/(eqep->cpr);
    eqep->pol = pol;


    // select event manager
    switch (eq) {

    case EQEP1:

        //EQep1Regs.QEPCTL.bit.QPEN = 0;  // make sure qep reset
        HWREGH(EQEP1_CTL_addr) &= ~0x8;

        //EQep1Regs.QEPCTL.bit.SWI = 1;   // Initialize Position counter to zero
        HWREGH(EQEP1_CTL_addr) |= 0x80;

        //EQep1Regs.QDECCTL.bit.QSRC = 0;  // Quadrature count mode
        HWREGH(EQEP1_DECCTL_addr) &= ~0xC000;

        //EQep1Regs.QPOSCTL.all = 0x0;   // Disable eQep Position Compare
        HWREGH(EQEP1_POSCTL_addr) = 0x0;

        //EQep1Regs.QCAPCTL.all = 0x0;  // Disable eQep Capture
        HWREGH(EQEP1_CAPCTL_addr) = 0x0;

        //EQep1Regs.QEINT.all = 0x0;  // Disable all eQep interrupts
        HWREGH(EQEP1_EINT_addr) = 0x0;

        //EQep1Regs.QPOSMAX = 0xFFFFFFFF;
        HWREG(EQEP1_QPOSMAX_addr) = 0xFFFFFFFF;


        //EQep1Regs.QEPCTL.bit.FREE_SOFT = 2;  // EQep uneffected by emulation suspend
        HWREGH(EQEP1_CTL_addr) &= ~0x4000;
        HWREGH(EQEP1_CTL_addr) |= 0x8000;

        //EQep1Regs.QEPCTL.bit.QPEN = 1; // Enable EQep
        HWREGH(EQEP1_CTL_addr) |= 0x8;

        break;

    case EQEP2:


        //EQep1Regs.QEPCTL.bit.QPEN = 0;  // make sure qep reset
        HWREGH(EQEP2_CTL_addr) &= ~0x8;

        //EQep1Regs.QEPCTL.bit.SWI = 1;   // Initialize Position counter to zero
        HWREGH(EQEP2_CTL_addr) |= 0x80;

        //EQep1Regs.QDECCTL.bit.QSRC = 0;  // Quadrature count mode
        HWREGH(EQEP2_DECCTL_addr) &= ~0xC000;

        //EQep1Regs.QPOSCTL.all = 0x0;   // Disable eQep Position Compare
        HWREGH(EQEP2_POSCTL_addr) = 0x0;

        //EQep1Regs.QCAPCTL.all = 0x0;  // Disable eQep Capture
        HWREGH(EQEP2_CAPCTL_addr) = 0x0;

        //EQep1Regs.QEINT.all = 0x0;  // Disable all eQep interrupts
        HWREGH(EQEP2_EINT_addr) = 0x0;

        //EQep1Regs.QPOSMAX = 0xFFFFFFFF;
        HWREG(EQEP2_QPOSMAX_addr) = 0xFFFFFFFF;


        //EQep1Regs.QEPCTL.bit.FREE_SOFT = 2;  // EQep uneffected by emulation suspend
        HWREGH(EQEP2_CTL_addr) &= ~0x4000;
        HWREGH(EQEP2_CTL_addr) |= 0x8000;

        //EQep1Regs.QEPCTL.bit.QPEN = 1; // Enable EQep
        HWREGH(EQEP2_CTL_addr) |= 0x8;

        break;
    case EQEP3:

        //EQep1Regs.QEPCTL.bit.QPEN = 0;  // make sure qep reset
        HWREGH(EQEP3_CTL_addr) &= ~0x8;

        //EQep1Regs.QEPCTL.bit.SWI = 1;   // Initialize Position counter to zero
        HWREGH(EQEP3_CTL_addr) |= 0x80;

        //EQep1Regs.QDECCTL.bit.QSRC = 0;  // Quadrature count mode
        HWREGH(EQEP3_DECCTL_addr) &= ~0xC000;

        //EQep1Regs.QPOSCTL.all = 0x0;   // Disable eQep Position Compare
        HWREGH(EQEP3_POSCTL_addr) = 0x0;

        //EQep1Regs.QCAPCTL.all = 0x0;  // Disable eQep Capture
        HWREGH(EQEP3_CAPCTL_addr) = 0x0;

        //EQep1Regs.QEINT.all = 0x0;  // Disable all eQep interrupts
        HWREGH(EQEP3_EINT_addr) = 0x0;

        //EQep1Regs.QPOSMAX = 0xFFFFFFFF;
        HWREG(EQEP3_QPOSMAX_addr) = 0xFFFFFFFF;


        //EQep1Regs.QEPCTL.bit.FREE_SOFT = 2;  // EQep uneffected by emulation suspend
        HWREGH(EQEP3_CTL_addr) &= ~0x4000;
        HWREGH(EQEP3_CTL_addr) |= 0x8000;

        //EQep1Regs.QEPCTL.bit.QPEN = 1; // Enable EQep
        HWREGH(EQEP3_CTL_addr) |= 0x8;

        break;

    }
}

/* EQEP_read(): read QEP encoder's position in radians
 *
 * parameters:
 *    eqep   = address pointer to an initialized QEP structure
 *
 * return: encoder position in radians
 */
float EQEP_read(eqep_t *eqep)
{
    uint32_t raw = 0;
    int32_t signed_raw = 0;
    uint32_t EQEP1_POSCNT_addr = CSL_DSP_PWMSS1_IEQEP_REGS+CSL_EQEP_QPOSCNT;
    uint32_t EQEP2_POSCNT_addr = CSL_DSP_PWMSS2_IEQEP_REGS+CSL_EQEP_QPOSCNT;
    uint32_t EQEP3_POSCNT_addr = CSL_DSP_PWMSS3_IEQEP_REGS+CSL_EQEP_QPOSCNT;

    // read raw value
    switch (eqep->eq) {
    case EQEP1:
        //raw = EQep1Regs.QPOSCNT;
        raw = HWREG(EQEP1_POSCNT_addr);
        DanEnc1Raw = raw;
        break;
    case EQEP2:
        //raw = EQep2Regs.QPOSCNT;
        raw = HWREG(EQEP2_POSCNT_addr);
        break;
    case EQEP3:
        //raw = EQep3Regs.QPOSCNT;
        raw = HWREG(EQEP3_POSCNT_addr);
        break;
    }

    if (raw >= QEP_MAXVALUE/2) {
        signed_raw = raw - QEP_MAXVALUE;
    } else {
        signed_raw = raw;
    }

    return ((eqep->pol)*(eqep->res)*signed_raw + eqep->init_rad_coord);
}


/**
 *  @brief Function main : Main application function
 *  @retval              : 0: success ; -1: fail
 */
int main(void)
{
    Board_initCfg boardCfg;
    int status;

    Watchdog_disable();
    AM572x_PRCM_Module_AllEnable_Config();

    /* Add exit function */
    System_atexit(appExitFunction);

    /* First step here is board specific initialization
     * Note that the Board_init is specific to the
     * platform. If running on a newly custom platform
     * the Board library need to be ported and customized
     * for the new platform.
     * See Details of customizing the board library in the
     * PDK/Processor SDK User guide */
    /* Set Board initialization flags: */
    boardCfg =
#ifndef SBL_BOOT
         /* Enabling Board Pinmux, clock when using without SBL boot
          * to act as stand alone application.
          */
         BOARD_INIT_PINMUX_CONFIG |
         BOARD_INIT_MODULE_CLOCK;// |
#endif
         /* The UART_STDIO initializes the default UART port on the board
          *  and support stdio like UART_printf which is used by appPrint
          */
         /* Dan Block Commented out
          BOARD_INIT_UART_STDIO;
         */



    /* Initialize Board */
    status = Board_init(boardCfg);
    if (status != BOARD_SOK) {
//        appPrint("\n Error: Board_init failed: error %d", status);
    }
//    appPrint("\n Board Init complete");


    /* Second step to Initialize peripherals */
    peripheralInit();
    // EQEP1A E1,3_28, EQEP1B G2 3_29
    init_EQEP(&eqep1,EQEP1,1250,1,0.0);
    // EQEP2A F4 4_6, EQEP2B C1 4_7
    init_EQEP(&eqep2,EQEP2,1250,1,0.0);
    // EQEP1A AC7 6_31, EQEP1B AC6 7_0
    init_EQEP(&eqep3,EQEP3,1250,1,0.0);
    initForGPIO2Interrupt();
    //McSPISetUp(MCSPI3_BASE_ADDRESS, 0);     //Set up MCSPI3 with interrupt functionality disabled
    McSPISetUp(MCSPI3_BASE_ADDRESS, 1);     //Set up MCSPI3 with interrupt functionality disabled

    //McSPISetup(MCSPI4_BASE_ADDRESS, 1);     //Set up MCSPI4 with interrupt functionality enabled

    /* Third step is to create Application tasks */
//    appTasksCreate();

    /* Fourth step is to Start BIOS */
    BIOS_start();
    return (0);
}

/**
 *  @brief Function appExitFunction : Just prints end of application
 *             This function is plugged into BIOS to run on exit.
 *  @retval              : 0: success ; -1: fail
 */
void appExitFunction(Int argument)
{
//   appPrint("\n Template app ended\n");
}

/**
 *  @brief Function peripheralInit : Initializes peripherals needed by
 *             application
 *  @retval              : None
 */
void peripheralInit(void) {
    /* UART initialization: This is redundant as it is already done
     * as part of Board_init. Included here for completion */
//    UART_init();
//    appPrint("\n Uart Init complete");

    /* I2C initialization */
//    I2C_init();
//    appPrint("\n I2C Init complete");

    /* GPIO initialization */
    GPIO_init();
//    appPrint("\n Gpio Init complete");

    /* MCSPI initialization */
    MCSPI_init();
//    appPrint("\n MCSPI Init complete");

    /* Add any additional peripherals to be initialized here */

//    appPrint("\n ======== Peripheral Initialization complete ========\n");

}



float angle = M_PI;
float tanvalue = 0;
long Dan_NumF28335Swi = 0;
//void F28335_GpioInt(void) {
//    GPIO_write(GPIO_DAN_LED4, GPIO_PIN_VAL_HIGH);
//    Dan_NumF28335Swi++;
//    tanvalue = tan(angle);
//    angle = angle + M_PI/6.0;
//    if(lastTransferComplete){
//        McSPIInitializeBuffers();//This is a self defined function that will populate the CS0data, CS1data, CS2data, CS3data, CS0size... etc.
//        McSPIStartTransfer(MCSPI3_BASE_ADDRESS, 0);
//
//    }
//
//    GPIO_write(GPIO_DAN_LED4, GPIO_PIN_VAL_LOW);
//}

//SWI function with SPI3 interrupts posted when transmission complete
void F28335_GpioInt(void) {
    GPIO_write(GPIO_DAN_LED4, GPIO_PIN_VAL_HIGH);
    Dan_NumF28335Swi++;
    tanvalue = tan(angle);
    angle = angle + M_PI/6.0;

    GPIO_write(GPIO_DAN_LED4, GPIO_PIN_VAL_LOW);
}

void gpioIsr(void)
{
//    volatile uint32_t gpio_pin_value = 0;

    GPIO_write(GPIO_DAN_LED0, GPIO_PIN_VAL_HIGH);
    DanIntStatusBefore =  GPIOPinIntStatus(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);
    DanRawIntBefore =  GPIORawIntStatus(gpio_base_address, GPIO_INT_LINE_1, 0xffffffff);
    /*Disable interrupt*/
//    GPIOPinIntDisable(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);

    Dan_NumGPIO2Ints++;

    if(lastTransferComplete){
        McSPIInitializeBuffers();//This is a self defined function that will populate the CS0data, CS1data, CS2data, CS3data, CS0size... etc.
        McSPIStartTransfer(MCSPI3_BASE_ADDRESS, 1);

    }

    /*Read pin*/
//    gpio_pin_value = GPIOPinRead(gpio_base_address, gpio_pin);

    GPIOPinIntClear(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);

    /*Enable interrupt interrupt*/
//    GPIOPinIntEnable(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);
    DanIntStatusAfter =  GPIOPinIntStatus(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);
    DanRawIntAfter =  GPIORawIntStatus(gpio_base_address, GPIO_INT_LINE_1, 0xffffffff);
    GPIO_write(GPIO_DAN_LED0, GPIO_PIN_VAL_LOW);
}


void configurGpioInterrupt()
{
// Not sure if I need this
#if IRQ_XBAR_CFG_REQUIRED
    /* XBar configuration */
    CSL_xbarIrqConfigure(IRQ_XBAR_CPU_ID,IRQ_XBAR_INST_NO,IRQ_XBAR_INDEX);
    // Here also setting up McSPI4 XBAR.  Probably should be moved to SPI init
    CSL_xbarIrqConfigure(IRQ_XBAR_CPU_ID,CSL_XBAR_INST_DSP1_IRQ_74,CSL_XBAR_MCSPI4_IRQ);

    // Here also setting up McSPI3 XBAR.  Probably should be moved to SPI init
    CSL_xbarIrqConfigure(IRQ_XBAR_CPU_ID,CSL_XBAR_INST_DSP1_IRQ_62,CSL_XBAR_MCSPI3_IRQ);

#endif
//    Intc_Init();
//    Intc_IntEnable(interrupt_num);

//    Intc_IntRegister(interrupt_num, (IntrFuncPtr) gpioIsr, (void *) 0);
//    Intc_IntPrioritySet(interrupt_num, 1, 0);

//    Intc_SystemEnable(interrupt_num);
}

void initForGPIO2Interrupt(void)
{

//    padconfig_PrcmEnable();

//    UARTConfigPuts(uartBaseAddr, "\r\nGPIO Input interrupt App", -1);
//    UARTConfigPuts(uartBaseAddr, "\r\nGenerate interrupt based on input value on GPIO pin", -1);
//    UARTConfigPuts(uartBaseAddr, "\r\nUse GPIO2 pin 25.", -1);
//    UARTConfigPuts(uartBaseAddr, "\r\nTo Drive the value on pin to LOW connect to ground", -1);
//    UARTConfigPuts(uartBaseAddr, "\r\nDefault value on the pin is High", -1);

    /* User Interface*/
//    UARTConfigPuts(uartBaseAddr, "\r\nEnter type of test", -1);
//    UARTConfigPuts(uartBaseAddr, "\r\n1. GPIO_INT_TYPE_LEVEL_LOW", -1);
//    UARTConfigPuts(uartBaseAddr, "\r\n2. GPIO_INT_TYPE_LEVEL_HIGH ", -1);
//    UARTConfigPuts(uartBaseAddr, "\r\n3. GPIO_INT_TYPE_FALL_EDGE", -1);
//    UARTConfigPuts(uartBaseAddr, "\r\n4. GPIO_INT_TYPE_RISE_EDGE ", -1);
//    UARTConfigPuts(uartBaseAddr, "\r\nEnter value(1, 2, 3 or 4) : ", -1);
//    UARTConfigGets(uartBaseAddr, &testType, 1);

    /*Configure interrupt controller*/
    configurGpioInterrupt();

    // set no IDLE Mode for GPIO2
    *(unsigned int *)0x48055010 = ((*(unsigned int *)0x48055010) & ~0x18) | 0x8;
    /*Reset GPIO*/
//    GPIOModuleReset(gpio_base_address);

    /*Enable GPIO*/
//    GPIOModuleEnable(gpio_base_address);

    /*Configure and enable debouncing feature*/
//    GPIODebounceTimeConfig(gpio_base_address, 0xFF); Works well for switch
//    GPIODebounceFuncControl(gpio_base_address, gpio_pin,
//                            GPIO_DEBOUNCE_FUNC_ENABLE);

    GPIODebounceTimeConfig(gpio_base_address, 0x0);  // Use zero for HWI

    GPIODebounceFuncControl(gpio_base_address, gpio_pin,
                            GPIO_DEBOUNCE_FUNC_DISABLE);

//    if ('1' == testType)
//    {
//        GPIOIntTypeSet(gpio_base_address, gpio_pin,
//                       GPIO_INT_TYPE_LEVEL_LOW);
//        strcpy(uartOutput, "\r\nGPIO: Low  Level detected. Pin value = ");
//    }
//    else if ('2' == testType)
//   {
//        GPIOIntTypeSet(gpio_base_address, gpio_pin,
//                       GPIO_INT_TYPE_LEVEL_HIGH);
//        strcpy(uartOutput, "\r\nGPIO: Default High Level detected. Pin value = ");
//    }
//    else if ('3' == testType)
//    {
        GPIOIntTypeSet(gpio_base_address, gpio_pin,GPIO_INT_TYPE_FALL_EDGE);
//        strcpy(uartOutput, "\r\nGPIO: Falling edge detected. Pin value = ");
//    }
//    else
//    {
//        GPIOIntTypeSet(gpio_base_address, gpio_pin,
//                       GPIO_INT_TYPE_RISE_EDGE);
//        strcpy(uartOutput, "\r\nGPIO: Rising edge detected. Pin value = ");
//    }

    /* Set pin direction as input*/
    GPIODirModeSet(gpio_base_address, gpio_pin, GPIO_DIR_INPUT);

    /*Clear interrupt*/
    GPIOPinIntDisable(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);
    GPIOPinIntClear(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);

    /*Enable interrupt*/
//#warn  Put in when I want to try interrupts
    GPIOPinIntEnable(gpio_base_address, GPIO_INT_LINE_1, gpio_pin);

}

void CallBIOSTick(void) {
    Clock_tick();
}




//---------------------McSPI----------------------
void McSPI3_ISR(void){
    GPIO_write(GPIO_DAN_LED5, GPIO_PIN_VAL_HIGH);
    McSPIIntDisable(MCSPI3_BASE_ADDRESS, 0xFFFF);

    int i = 0;
    if(length == 1){                                                            //if all words in a channel have been sent
        *p_rx++ = McSPIReceiveData(MCSPI3_BASE_ADDRESS, gChNum);                //receive the last word

        for(i=0; i<McSPI_DATA_COUNT; i++){                                   //populate the receive data array and the next channel's send data array
            CS0dataReceived.darray[i] = rxBuffer[i];
        }
        lastTransferComplete = 1;                                       //transmission over
        Swi_post(SWI_F28335_GpioInt);

    }
    else{                                                                   //if it wasnt the last word on a channel, just receive the data and transmit the next word
        //The receive buffer is full
        *p_rx++ = McSPIReceiveData(MCSPI3_BASE_ADDRESS, gChNum);



        McSPIIntStatusClear(MCSPI3_BASE_ADDRESS,0x04<<(gChNum*4));
        McSPIIntEnable(MCSPI3_BASE_ADDRESS, 0x04<<(gChNum*4));         //enable only the interrupt on CSx
        McSPITransmitData(MCSPI3_BASE_ADDRESS, (uint32_t) (*p_tx++), gChNum);
        length--;
    }
    GPIO_write(GPIO_DAN_LED5, GPIO_PIN_VAL_LOW);
}



void McSPI4_ISR(void){
    McSPIIntDisable(MCSPI4_BASE_ADDRESS, 0xFFFF);

    int i = 0;
    if(length == 1){                                                            //if all words in a channel have been sent
        *p_rx++ = McSPIReceiveData(MCSPI4_BASE_ADDRESS, gChNum);                //receive the last word
        if(gChNum == 0){                                                        //if channel = 0
           for(i=0; i<McSPI_DATA_COUNT; i++){                                   //populate the receive data array and the next channel's send data array
               txBuffer[i] = CS1dataToSend.darray[i];
               CS0dataReceived.darray[i] = rxBuffer[i];
           }
           gChNum = 1;                                                          //next channel
           length = CS1size;
           p_tx    = txBuffer;
           p_rx    = rxBuffer;
           McSPIIntStatusClear(MCSPI4_BASE_ADDRESS,0x04<<(gChNum*4));
           McSPIIntEnable(MCSPI4_BASE_ADDRESS, 0x04<<(gChNum*4));         //enable only the interrupt on CS1
           McSPITransmitData(MCSPI4_BASE_ADDRESS, (uint32_t) (*p_tx++), gChNum);    //transmit the first word on channel 1
        }
        else if(gChNum == 1){//same as channel 0
            for(i=0; i<McSPI_DATA_COUNT; i++){
                txBuffer[i] = CS2dataToSend.darray[i];
                CS1dataReceived.darray[i] = rxBuffer[i];
            }
            gChNum = 2;
            length = CS2size;
            p_tx    = txBuffer;
            p_rx    = rxBuffer;
            McSPIIntStatusClear(MCSPI4_BASE_ADDRESS,0x04<<(gChNum*4));
            McSPIIntEnable(MCSPI4_BASE_ADDRESS, 0x04<<(gChNum*4));         //enable only the interrupt on CS2
            McSPITransmitData(MCSPI4_BASE_ADDRESS, (uint32_t) (*p_tx++), gChNum);
         }
        else if(gChNum == 2){//same as channel 0
            for(i=0; i<McSPI_DATA_COUNT; i++){
                txBuffer[i] = CS3dataToSend.darray[i];
                CS2dataReceived.darray[i] = rxBuffer[i];
            }
            gChNum = 3;
            length = CS3size;
            p_tx    = txBuffer;
            p_rx    = rxBuffer;
            McSPIIntStatusClear(MCSPI4_BASE_ADDRESS,0x04<<(gChNum*4));
            McSPIIntEnable(MCSPI4_BASE_ADDRESS, 0x04<<(gChNum*4));         //enable only the interrupt on CS3
            McSPITransmitData(MCSPI4_BASE_ADDRESS, (uint32_t) (*p_tx++), gChNum);
         }
        else if(gChNum == 3){                                               //this is the last channel
            for(i=0; i<McSPI_DATA_COUNT; i++){
                CS3dataReceived.darray[i] = rxBuffer[i];                           //populate the receive data array
            }
            lastTransferComplete = 1;                                       //transmission over
        }


    }
    else{                                                                   //if it wasnt the last word on a channel, just receive the data and transmit the next word
        //The receive buffer is full
            *p_rx++ = McSPIReceiveData(MCSPI4_BASE_ADDRESS, gChNum);



            McSPIIntStatusClear(MCSPI4_BASE_ADDRESS,0x04<<(gChNum*4));
            McSPIIntEnable(MCSPI4_BASE_ADDRESS, 0x04<<(gChNum*4));         //enable only the interrupt on CSx
            McSPITransmitData(MCSPI4_BASE_ADDRESS, (uint32_t) (*p_tx++), gChNum);
            length--;
    }

}
