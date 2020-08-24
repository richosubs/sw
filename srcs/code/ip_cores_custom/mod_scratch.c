#include <stdio.h>
#include <stdlib.h> // Std C functions, e.g. exit()
#include <math.h>   // libm header: sqrt(), cos(), etc

//#include "platform.h"

#include "xstatus.h"
#include "xil_io.h"
#include "parameter_maps_prj_base.h"
#include "xil_io.h"

#include "mod_scratch.h"
#include "_macros_include_all.h"



#define SCRATCH_DELAY 10000000



Mod_Scratch_Config Mod_Scratch_ConfigTable[] =
{
	{
			XPAR_SCRATCH_DEVICE_ID,
			XPAR_SCRATCH_BASEADDR
	}
};


Mod_Scratch instModScratch;


uint32_t *guiAddressPointer;

int Mod_Scratch_Initialize(Mod_Scratch *InstancePtr, u16 DeviceId) {
	int lStatus= XST_SUCCESS;
	DEBUG_PRINT_ENTER("");

	Mod_Scratch_Config *ConfigPtr;

	/*
	 * Assert arguments
	 */
	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr= &Mod_Scratch_ConfigTable[0];

	lStatus= Mod_Scratch_CfgInitialize(InstancePtr, ConfigPtr, ConfigPtr->BaseAddress);

	return(lStatus);
}


int Mod_Scratch_CfgInitialize(Mod_Scratch *InstancePtr, Mod_Scratch_Config *Config, UINTPTR EffectiveAddr) {
	int lStatus= XST_SUCCESS;
	/* Assert arguments */

	Xil_AssertNonvoid(InstancePtr != NULL);

	/* Set some default values. */
	InstancePtr->BaseAddress = EffectiveAddr;

	/*
	 * Indicate the instance is now ready to use, initialized without error
	 */
	InstancePtr->IsReady = XIL_COMPONENT_IS_READY;
	return(lStatus);
}



int mod_scratch_init(void) {
	int lStatus= XST_SUCCESS;

    lStatus= Mod_Scratch_Initialize(&instModScratch, XPAR_SCRATCH_DEVICE_ID);
    DEBUG_PRINT_LOG_STATUS_CHK_ERR(lStatus, "MOD SCRATCH Initialization");

	DEBUG_PRINT_LOG_STATUS_RETURN(lStatus, "");

	return(lStatus);
	}



int mod_scratch_write(uint32_t uiData) {
	int lStatus= XST_SUCCESS;

	fpgaWriteWordC_D32(instModScratch.BaseAddress + REG_MOD_SCRATCH_TEST_RW, uiData);
	DEBUG_PRINT_LOG_DEBUG("WRITE: Address= %x Data= %x", instModScratch.BaseAddress, uiData);

    fpgaReadWordC_D32(instModScratch.BaseAddress + REG_MOD_SCRATCH_TEST_RW, \
    		&instModScratch.regScratch);
    DEBUG_PRINT_LOG_DEBUG("READ:  Address= %x Data= %x", instModScratch.BaseAddress, instModScratch.regScratch);

    DEBUG_COMPARE(lStatus, uiData, instModScratch.regScratch);

	return(lStatus);
}




int mod_scratch_read(void) {
	int lStatus= XST_SUCCESS;

    fpgaReadWordC_D32(instModScratch.BaseAddress + REG_MOD_SCRATCH_TEST_RW, \
    		&instModScratch.regScratch);

    fpgaReadWordC_D32(instModScratch.BaseAddress + REG_MOD_SCRATCH_COMP_ID_RO, \
			&instModScratch.regReadOnly1);

    fpgaReadWordC_D32(instModScratch.BaseAddress + REG_MOD_SCRATCH_REV_ID_RO, \
			&instModScratch.regReadOnly2);

    fpgaReadWordC_D32(instModScratch.BaseAddress + REG_MOD_SCRATCH_FIFO_DMA_TEST_WRITE_COUNT, \
			&instModScratch.regFifoDmaTestWrCountRO);

    fpgaReadWordC_D32(instModScratch.BaseAddress + REG_MOD_SCRATCH_FIFO_DMA_TEST_READ_COUNT, \
			&instModScratch.regFifoDmaTestRdCountRO);

    fpgaReadWordC_D32(instModScratch.BaseAddress + REG_MOD_SCRATCH_FIFO_DMA_TEST_STATUS, \
			&instModScratch.regFifoDmaTestStatusRO);


    return(lStatus);
}



int mod_scratch_print(void) {
	int lStatus= XST_SUCCESS;

	DEBUG_PRINT_DASH();
    DEBUG_PRINT_ENTER("");
	DEBUG_PRINT_DASH();

	mod_scratch_read();

    DEBUG_PRINT_ALWAYS("REG_MOD_SCRATCH_TEST_RW: Address= %x Data= %x", XPAR_SCRATCH_BASEADDR+REG_MOD_SCRATCH_TEST_RW, \
    		instModScratch.regScratch);

    DEBUG_PRINT_ALWAYS("REG_MOD_SCRATCH_COMP_ID_RO: Address= %x Data= %x", XPAR_SCRATCH_BASEADDR+REG_MOD_SCRATCH_COMP_ID_RO, \
    		instModScratch.regReadOnly1);

    DEBUG_PRINT_ALWAYS("REG_MOD_SCRATCH_REV_ID_RO: Address= %x Data= %x", XPAR_SCRATCH_BASEADDR+REG_MOD_SCRATCH_REV_ID_RO, \
    		instModScratch.regReadOnly2);

    DEBUG_PRINT_ALWAYS("REG_MOD_SCRATCH_FIFO_DMA_TEST_WRITE_COUNT: Address= %x Data= %x", XPAR_SCRATCH_BASEADDR+REG_MOD_SCRATCH_FIFO_DMA_TEST_WRITE_COUNT, \
    		instModScratch.regFifoDmaTestWrCountRO);

    DEBUG_PRINT_ALWAYS("REG_MOD_SCRATCH_FIFO_DMA_TEST_READ_COUNT: Address= %x Data= %x", XPAR_SCRATCH_BASEADDR+REG_MOD_SCRATCH_FIFO_DMA_TEST_READ_COUNT, \
    		instModScratch.regFifoDmaTestRdCountRO);

    DEBUG_PRINT_ALWAYS("REG_MOD_SCRATCH_FIFO_DMA_TEST_STATUS: Address= %x Data= %x", XPAR_SCRATCH_BASEADDR+REG_MOD_SCRATCH_FIFO_DMA_TEST_STATUS, \
    		instModScratch.regFifoDmaTestStatusRO);

    DEBUG_PRINT_ALWAYS("-AE         = %x", MASK_RMSFD_STATUS_AE(instModScratch.regFifoDmaTestStatusRO));
    DEBUG_PRINT_ALWAYS("-PE         = %x", MASK_RMSFD_STATUS_PE(instModScratch.regFifoDmaTestStatusRO));
    DEBUG_PRINT_ALWAYS("-AF         = %x", MASK_RMSFD_STATUS_AF(instModScratch.regFifoDmaTestStatusRO));
    DEBUG_PRINT_ALWAYS("-PF         = %x", MASK_RMSFD_STATUS_PF(instModScratch.regFifoDmaTestStatusRO));
    DEBUG_PRINT_ALWAYS("-MM2S_RESET = %x", MASK_RMSFD_STATUS_MM2S_RESET(instModScratch.regFifoDmaTestStatusRO));
    DEBUG_PRINT_ALWAYS("-S2MM_RESET = %x", MASK_RMSFD_STATUS_S2MM_RESET(instModScratch.regFifoDmaTestStatusRO));

    return(lStatus);
}




int mod_scratch_test(uint32_t uiLoop) {
	int lStatus= XST_SUCCESS;
	//uint32_t uiRead;
	volatile uint32_t Delay;
	volatile uint32_t lCountUp= 0;

	while (lCountUp < uiLoop) {
		mod_scratch_write(lCountUp);
		for (Delay = 0; Delay < SCRATCH_DELAY; Delay++);

		mod_scratch_print();
		for (Delay = 0; Delay < SCRATCH_DELAY; Delay++);

		lCountUp++;
	}
	return(lStatus);
}



