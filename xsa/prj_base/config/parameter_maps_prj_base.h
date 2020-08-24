/*
 * Used by prj_base.xsa platforms
 *
 * Alias files.  Maps parameters that VITIS generates for the BSP based on the
 * XSA file to a set parameter.  The BSP-XSA parameters are based on the board
 * design hierachy path that might change.
 *
 */

#ifndef __PARAMETER_MAPS_PRJ_BASE_H_
#define __PARAMETER_MAPS_PRJ_BASE_H_

#include "xparameters.h"

#define XPAR_SCRATCH_DEVICE_ID   XPAR_BASE_MOD_SCRATCH_BRAM_CTRL_DEVICE_ID
#define XPAR_SCRATCH_BASEADDR    XPAR_BASE_MOD_SCRATCH_BRAM_CTRL_S_AXI_BASEADDR

#define XPAR_GPIO_DEVICE_ID   XPAR_BASE_MOD_LED_GPIO_DEVICE_ID
#define XPAR_GPIO_BASEADDR    XPAR_BASE_MOD_LED_GPIO_BASEADDR

#define XPAR_AXIDMA_0_DEVICE_ID
#define XPAR_AXIDMA_0_BASEADDR

#define XPAR_XDMA_FIFO_DEVICE_ID XPAR_DMA_XDMA_DMA_DEVICE_ID
#define XPAR_DMA_XDMA_DMA_BASEADDR




/* Quick remap in case the xparameters change; only need to change here */
#define XPAR_FFT_DMA_ENG_DEVICE_ID 		XPAR_TOP_LOGIC_TOP_MASTER_HP0_FPD_TOP_FFT_DMA_TEST_MOD_FFT_DMA_ENG_DEVICE_ID
#define XPAR_FFT_DMA_ENG_BASEADDR    	XPAR_TOP_LOGIC_TOP_MASTER_HP0_FPD_TOP_FFT_DMA_TEST_MOD_FFT_DMA_ENG_BASEADDR



/* -------------------------------------------------------------------------------------
 *                                    <SDRAM>
 *
 * Definitions for peripheral PSU_DDR_0
 * -------------------------------------------------------------------------------------
 */
#define SDRAM_BASEADDR 					XPAR_PSU_DDR_0_S_AXI_BASEADDR
#define SDRAM_HIGHADDR 					XPAR_PSU_DDR_0_S_AXI_HIGHADDR

#define SDRAM_BRAM_DMA_BUFFER0       	((SDRAM_BASEADDR) + 0x02000000)
#define SDRAM_BRAM_DMA_BUFFER1       	((SDRAM_BASEADDR) + 0x01000000)

#define SDRAM_BRAM_DMA_BUFFER0_WORDS   	(0x000008)
#define SDRAM_BRAM_DMA_BUFFER1_WORDS   	(0x000008)

/* -------------------------------------------------------------------------------------
 *                                 <MOD_FIFO_DMA>
 *
 *
 * -------------------------------------------------------------------------------------
 */
#define XPAR_MOD_FIFO_DMA_ENG_DEVICE_ID 	XPAR_TOP_LOGIC_TOP_MASTER_HP0_FPD_TOP_FIFO_DMA_TEST_MOD_FIFO_DMA_ENG_DEVICE_ID
#define XPAR_MOD_FIFO_DMA_ENG_BASEADDR   	XPAR_TOP_LOGIC_TOP_MASTER_HP0_FPD_TOP_FIFO_DMA_TEST_MOD_FIFO_DMA_ENG_BASEADDR



/* -------------------------------------------------------------------------------------
 *                                 <MOD_BRAM_DMA>
 *
 *     ZYNQ access to PORT-B BRAM.
 * -------------------------------------------------------------------------------------
 */
#define MOD_BRAM_CNTRL_ZYNQ_BASEADDR0 		XPAR_TOP_LOGIC_TOP_MASTER_HP0_FPD_TOP_BRAM_CDMA_TEST_MOD_BRAM_CTRL_ZYNQ_0_S_AXI_BASEADDR
#define MOD_BRAM_CNTRL_ZYNQ_BASEADDR1 		XPAR_TOP_LOGIC_TOP_MASTER_HP0_FPD_TOP_BRAM_CDMA_TEST_MOD_BRAM_CTRL_ZYNQ_1_S_AXI_BASEADDR

#define MOD_BRAM_CNTRL_ZYNQ_HIGHADDR0 		XPAR_TOP_LOGIC_TOP_MASTER_HP0_FPD_TOP_BRAM_CDMA_TEST_MOD_BRAM_CTRL_ZYNQ_0_S_AXI_HIGHADDR
#define MOD_BRAM_CNTRL_ZYNQ_HIGHADDR1 		XPAR_TOP_LOGIC_TOP_MASTER_HP0_FPD_TOP_BRAM_CDMA_TEST_MOD_BRAM_CTRL_ZYNQ_1_S_AXI_HIGHADDR

#define MOD_BRAM_CNTRL_ZYNQ_B0_WORDS  		((MOD_BRAM_CNTRL_ZYNQ_HIGHADDR0 + 1 - MOD_BRAM_CNTRL_ZYNQ_BASEADDR0) / 4)
#define MOD_BRAM_CNTRL_ZYNQ_B1_WORDS    	((MOD_BRAM_CNTRL_ZYNQ_HIGHADDR1 + 1 - MOD_BRAM_CNTRL_ZYNQ_BASEADDR1) / 4)

#define XPAR_MOD_BRAM_CDMA_ENG_DEVICE_ID 	XPAR_TOP_LOGIC_TOP_MASTER_HP0_FPD_TOP_BRAM_CDMA_TEST_MOD_BRAM_CDMA_ENG_DEVICE_ID
#define XPAR_MOD_BRAM_CDMA_ENG_BASEADDR		XPAR_TOP_LOGIC_TOP_MASTER_HP0_FPD_TOP_BRAM_CDMA_TEST_MOD_BRAM_CDMA_ENG_BASEADDR


/* CDMA Engine  access to PORT-A BRAM.  This address is not to be used by the ZYNQ Processor*/
#define MOD_BRAM_CDMA_BASEADDR0 0x80008000
#define MOD_BRAM_CDMA_BASEADDR1 0x80009000




#endif
