#ifndef __MOD_SCRATCH_H_
#define __MOD_SCRATCH_H_


#include "xparameters.h"




//#define BASE_ADDRESS_MOD_SCRATCH  XPAR_MOD_SCRATCH_AXI_BRAM_CTRL_S_AXI_BASEADDR
typedef struct {
	u16 DeviceId;		 	/* Unique ID  of device */
	UINTPTR BaseAddress;	/* Device base address */
} Mod_Scratch_Config;




typedef struct {
	UINTPTR BaseAddress;	/* Device base address */
	u32 IsReady;	  	    /* Device is initialized and ready */
	uint32_t regScratch;
	uint32_t regReadOnly1;
	uint32_t regReadOnly2;
	uint32_t regFifoDmaTestWrCountRO;
	uint32_t regFifoDmaTestRdCountRO;
	uint32_t regFifoDmaTestStatusRO;
} Mod_Scratch;





#define REG_MOD_SCRATCH_TEST_RW      				0x00
#define REG_MOD_SCRATCH_COMP_ID_RO   				0x04
#define REG_MOD_SCRATCH_REV_ID_RO    				0x08

#define REG_MOD_SCRATCH_FIFO_DMA_TEST_WRITE_COUNT 	0x10
#define REG_MOD_SCRATCH_FIFO_DMA_TEST_READ_COUNT 	0x14
#define REG_MOD_SCRATCH_FIFO_DMA_TEST_STATUS 		0x18
#define MASK_RMSFD_STATUS_AE(data)                 	(((data) >> 0) & 0x01)
#define MASK_RMSFD_STATUS_PE(data)                  (((data) >> 1) & 0x01)
#define MASK_RMSFD_STATUS_AF(data)                  (((data) >> 2) & 0x01)
#define MASK_RMSFD_STATUS_PF(data)                  (((data) >> 3) & 0x01)
#define MASK_RMSFD_STATUS_MM2S_RESET(data)          (((data) >> 4) & 0x01)
#define MASK_RMSFD_STATUS_S2MM_RESET(data)          (((data) >> 5) & 0x01)


int Mod_Scratch_Initialize(Mod_Scratch *InstancePtr, u16 DeviceId);
int Mod_Scratch_CfgInitialize(Mod_Scratch *InstancePtr, Mod_Scratch_Config *Config, UINTPTR EffectiveAddr);


int mod_scratch_init(void);
int mod_scratch_write(uint32_t uiData);
int mod_scratch_read(void);
int mod_scratch_print(void);
int mod_scratch_test(uint32_t uiLoop);

#endif
