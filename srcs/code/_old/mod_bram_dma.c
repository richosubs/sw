/*
 * Example of simple poll on GITHUB
 * https://github.com/Xilinx/embeddedsw/blob/master/XilinxProcessorIPLib/drivers/axicdma/examples/xaxicdma_example_simple_poll.c
 *
 */


#include <stdio.h>
#include <stdlib.h> // Std C functions, e.g. exit()
#include <math.h>   // libm header: sqrt(), cos(), etc
#include "xil_io.h"
#include "xparameters.h"
#include "mod_bram_dma.h"

#include "xaxicdma.h" // Device driver API for AXI DMA

#include "_macros_print.h"
#include "_macros_entry.h"
#include "_macros_access.h"

#include "_parameter_maps.h"

#include "_utils_compare.h"

#include "xdrv_xaxicdma.h"


#include "mod_fifo_dma.h"



/* 3 x defines from the xilinx example */
#define BUFFER_BYTESIZE		64	/* Length of the buffers for DMA
					 * transfer
					 */

#define NUMBER_OF_TRANSFERS	4	/* Number of transfers to do in this
					 * test
					 */

#define RESET_LOOP_COUNT	10	/* Number of times to check reset is
					 * done
					 */


// Declare a XAxiDma object instance
static XAxiCdma axiCdmaPtr;
//static XAxiCdma_Config *CfgCdmaPtr;

/*
 * Allocates memory on OCM space.
 */
#define DEF_MAX_WORDS 1024
#define DEF_MAX_BYTES (4 * DEF_MAX_WORDS)
static uint32_t gOCM_SourceBuffer[DEF_MAX_WORDS];
static uint32_t gOCM_DestinationBuffer[DEF_MAX_WORDS];


int mod_bram_dma_init() {
	XAxiCdma_Config *CfgCdmaPtr;
	int lStatus= XST_SUCCESS;
	int lResult;

	// Get pointer to DMA configuration
	CfgCdmaPtr = XAxiCdma_LookupConfig(XPAR_MOD_BRAM_CDMA_ENG_DEVICE_ID);
	DEBUG_PRINT_NULL_PTR(CfgCdmaPtr, &lResult, "XAxiCDma_LookupConfig");
	DEBUG_RETURN_ON_ERROR(lResult);

	// Initialize the DMA handle
	lStatus = XAxiCdma_CfgInitialize(&axiCdmaPtr, CfgCdmaPtr, CfgCdmaPtr->BaseAddress);
	//axiCdmaPtr->BaseAddr= CfgCdmaPtr->BaseAddress;



	DEBUG_PRINT_LOG_STATUS_CHK_ERR(lStatus, "DMA setup");

	if(0) {
		DEBUG_PRINT_ALWAYS("********************* BRAM ********************* ");
		DEBUG_PRINT_ALWAYS("BRAM DMA %p", &axiCdmaPtr);
		DEBUG_PRINT_ALWAYS("BRAM DMA %x", axiCdmaPtr.BaseAddr);
		DEBUG_PRINT_ALWAYS("BRAM DMA %x", axiCdmaPtr.Initialized);
		DEBUG_PRINT_ALWAYS("BRAM DMA %p", &CfgCdmaPtr);
		DEBUG_PRINT_ALWAYS("BRAM DMA %p", &CfgCdmaPtr->BaseAddress);
		DEBUG_PRINT_ALWAYS("BRAM DMA %p", CfgCdmaPtr->BaseAddress);

		mod_bram_dma_print_regs();

		exit(0);
	}

	//disable the interrupts
	//DEBUG_PRINT_LOG_PASSED("DMA disable interrupts");
	/* Disable interrupts, we use polling mode
	 */
	XAxiCdma_IntrDisable(&axiCdmaPtr, XAXICDMA_XR_IRQ_ALL_MASK);
	//XAxiCdma_IntrDisable(&axiCdmaPtr, XAXICDMA_IRQ_ALL_MASK, XAXICDMA_DEVICE_TO_DMA);
	//XAxiCdma_IntrDisable(&axiCdmaPtr, XAXICDMA_IRQ_ALL_MASK, XAXICDMA_DMA_TO_DEVICE);

	Xil_DCacheFlushRange((UINTPTR)&axiCdmaPtr, sizeof(XAxiCdma));
	Xil_DCacheFlushRange((UINTPTR)&CfgCdmaPtr, sizeof(XAxiCdma_Config));

	DEBUG_PRINT_LOG_STATUS_RETURN(lStatus, "");
	return(lStatus);
}




/* -------------------------------------------------------------------------------------
 * 									<TESTS>
 * -------------------------------------------------------------------------------------
 */
int mod_bram_dma_test() {
   int lStatus= XST_SUCCESS;

   DEBUG_PRINT_DASH();
   DEBUG_PRINT_ENTER("");
   DEBUG_PRINT_DASH();

   //mod_bram_dma_print_regs();

   //DEBUG_BREAK("Trigger ILA");

   lStatus+= mod_bram_dma_test_polling(0x010);

   //mod_bram_dma_print_regs();

   lStatus+= mod_bram_dma_test_interrupt();

   DEBUG_PRINT_LOG_STATUS_RETURN(lStatus, "");

   return(lStatus);
}




int mod_bram_dma_test_interrupt() {
   int lStatus= XST_SUCCESS;

   DEBUG_PRINT_DASH();
   DEBUG_PRINT_ENTER("");
   DEBUG_PRINT_DASH();

   DEBUG_PRINT_LOG_STATUS_RETURN(lStatus, "");

   return(lStatus);
}




int mod_bram_dma_test_polling(uint32_t uiTests) {
   int lStatus= XST_SUCCESS;

   DEBUG_PRINT_DASH();
   DEBUG_PRINT_ENTER("");
   DEBUG_PRINT_DASH();

   if(__BIT_CHECK(uiTests, 0)) {
	   lStatus+= mod_bram_dma_zynq_access_test();
   	   DEBUG_PRINT_DASH();
   	   //DEBUG_PRINT_ALWAYS("xxxxxxxxxxxxxxx   Status %d", lStatus);
   }

   //mod_bram_dma_print_regs();

   if(__BIT_CHECK(uiTests, 1)) {
	   lStatus+= mod_bram_dma_test_ocm_to_ocm_test_polling();
	   DEBUG_PRINT_DASH();
	   //DEBUG_PRINT_ALWAYS("xxxxxxxxxxxxxxx   Status %d", lStatus);
   }

   //mod_bram_dma_print_regs();

   if(__BIT_CHECK(uiTests, 2)) {
	   lStatus+= mod_bram_dma_test_ocm_to_bram_test_polling();
	   DEBUG_PRINT_DASH();
   }

   if(__BIT_CHECK(uiTests, 3)) {
	   lStatus+= mod_bram_dma_test_bram_to_bram_test_polling();
	   DEBUG_PRINT_DASH();
   }

   // Fails
   if(__BIT_CHECK(uiTests, 4)) {
	   lStatus+= mod_bram_dma_test_bram_to_sdram_test_polling();
	   DEBUG_PRINT_DASH();
   }

   if(__BIT_CHECK(uiTests, 5)) {
	   lStatus+= mod_bram_dma_test_sdram_to_bram_test_polling();
	   DEBUG_PRINT_DASH();
   }

   //DEBUG_PRINT_ALWAYS("xxxxxxxxxxxxxxx   Status %d", lStatus);
   DEBUG_PRINT_LOG_STATUS_RETURN(lStatus, "");

   return(lStatus);
}




/* -------------------------------------------------------------------------------------
 * 								     <POLLING>
 * -------------------------------------------------------------------------------------
 */
int mod_bram_dma_transfer_polling(UINTPTR *sourceBuffer, UINTPTR *destinationBuffer, int bytes) {
	int lStatus= XST_SUCCESS;
	int lLoop= 10;

	DEBUG_PRINT_DASH();
	DEBUG_PRINT_ENTER("");
	DEBUG_PRINT_DASH();

	//DEBUG_PRINT_ALWAYS("Source Address= 0x%08x Destination Address= 0x%08x", (UINTPTR)sourceBuffer, (UINTPTR)destinationBuffer);

	/* Need to flush the cache, read why again */
	Xil_DCacheFlushRange((UINTPTR)sourceBuffer, bytes);
	Xil_DCacheFlushRange((UINTPTR)destinationBuffer, bytes);

	/* Check that the CDMA is available */
	do {
		if(XAxiCdma_IsBusy(&axiCdmaPtr)) {
			lLoop--;
 	   		if(lLoop ==0) {
 	   		   DEBUG_PRINT_LOG_ERROR("XAxiCdma_IsBusy prior to sending DMA, will exit and not send");
 	   		   return(XST_FAILURE);
	   	   }
		}
	   else {
		   //DEBUG_PRINT_LOG_INFO("XAxiCdma_IsIdle prior to sending DMA, will send DMA now.");
		   lLoop= 0;
	   }
   } while(lLoop > 0);

	/* Set up the DMA and start it */
	XAxiCdma_SwitchMode(&axiCdmaPtr, XAXICDMA_SIMPLE_MODE);

	XAxiCdma_WriteReg(axiCdmaPtr.BaseAddr,
					XAXICDMA_SRCADDR_OFFSET,
					LOWER_32_BITS(sourceBuffer));

	XAxiCdma_WriteReg(axiCdmaPtr.BaseAddr,
				XAXICDMA_DSTADDR_OFFSET,
				LOWER_32_BITS(destinationBuffer));

	/*
	 * UPPER 32 bits = 0 ?
	XAxiCdma_WriteReg(axiCdmaPtr.BaseAddr,
				XAXICDMA_SRCADDR_OFFSET,
					LOWER_32_BITS(sourceBuffer));

	XAxiCdma_WriteReg(axiCdmaPtr.BaseAddr,
				XAXICDMA_DSTADDR_OFFSET,
				LOWER_32_BITS(destinationBuffer));
	*/

	/* Triggers */
	XAxiCdma_WriteReg(axiCdmaPtr.BaseAddr,
			XAXICDMA_BTT_OFFSET,
			bytes);


	/*
	 * wait til the DMA is not busy, completed
	 */

	//open: need better time delay
	lLoop=100;
	do {
		   if(XAxiCdma_IsBusy(&axiCdmaPtr)) {
			   lLoop--;
			   DEBUG_PRINT_LOG_INFO("XAxiCdma_IsBusy still after DMA sent %d", lLoop);
		   	   if(lLoop == 0) {
		   		   DEBUG_PRINT_LOG_ERROR("XAxiCdma_IsBusy still after DMA sent");
		   		   mod_bram_dma_print_regs();
		   		   return(XST_FAILURE);
		   	   }
		   }
		   else {
			   //DEBUG_PRINT_LOG_PASSED("XAxiCdma_IsBusy is idle, DMA completed %d", lLoop);
			   lLoop= 0;
		   }
	   } while(lLoop > 0);


	DEBUG_PRINT_LOG_STATUS_RETURN(lStatus, "");

	return(lStatus);
}




/*
 * gOCM_SourceBuffer -> gOCM_DestinationBuffer
 */
int mod_bram_dma_test_ocm_to_ocm_test_polling() {
	int lStatus= XST_SUCCESS;
	//int i;
	int lLength= 16; //DEF_MAX_BYTES;

	DEBUG_PRINT_DASH();
	DEBUG_PRINT_ENTER("");
	DEBUG_PRINT_DASH();


	/* Set up the source buffer with data; clear the destination */
	utilsFillBufferIncrementWithSeedX32((UINTPTR)gOCM_SourceBuffer, 0x06000000, lLength / 4);
	//utilsFillBufferConstantX32((UINTPTR)gOCM_DestinationBuffer, 0x00000002, lLength / 4);

	lStatus+= mod_bram_dma_transfer_polling(&gOCM_SourceBuffer, &gOCM_DestinationBuffer, lLength);

	/* Compare results of the buffers only if the DMA indicates it completed. */
//	if(lStatus == XST_SUCCESS) {
		utilsCompareBufferWithSeedX32((uint32_t)&gOCM_DestinationBuffer, 0x06000000, lLength/4, &lStatus);
	//	utilsCompareBufferWithSeedX32((UINTPTR)&gOCM_SourceBuffer, 0x06000000, lLength/4, &lStatus);
//	}

	DEBUG_PRINT_ALWAYS("Status %d", lStatus);
	//exit(0);
	//DEBUG_PRINT_LOG_STATUS_RETURN(lStatus, "");

	return(lStatus);
}




/*
 * - gOCM_SourceBuffer -> MOD_BRAM_CNTRL_BASEADDR0
 */
int mod_bram_dma_test_ocm_to_bram_test_polling() {
	int lStatus= XST_SUCCESS;
	//int i;
	int lLength= DEF_MAX_BYTES;

	DEBUG_PRINT_DASH();
	DEBUG_PRINT_ENTER("");
	DEBUG_PRINT_DASH();

	/* Set up the source buffer with data; clear the destination */
	utilsFillBufferIncrementWithSeedX32((UINTPTR)gOCM_SourceBuffer, 0x05000000, lLength / 4);
	utilsFillBufferConstantX32((uint32_t)MOD_BRAM_CNTRL_ZYNQ_BASEADDR0, 0x00000000, lLength / 4);

	mod_bram_dma_transfer_polling((uint32_t)&gOCM_SourceBuffer, (uint32_t)MOD_BRAM_CDMA_BASEADDR0, lLength);

	/* Compare results of the buffers */
	utilsCompareBufferWithSeedX32((UINTPTR)MOD_BRAM_CNTRL_ZYNQ_BASEADDR0, 0x05000000, lLength/4, &lStatus);

	DEBUG_PRINT_LOG_STATUS_RETURN(lStatus, "");

	return(lStatus);
}





/*
 * - MOD_BRAM_CNTRL_BASEADDR0 -> MOD_BRAM_CNTRL_BASEADDR1
 */
int mod_bram_dma_test_bram_to_bram_test_polling() {
	int lStatus= XST_SUCCESS;
	//int i;
	int lLength= MOD_BRAM_CNTRL_ZYNQ_B0_WORDS * 4;

	DEBUG_PRINT_DASH();
	DEBUG_PRINT_ENTER("");
	DEBUG_PRINT_DASH();

	/* Set up the source buffer with data; clear the destination */
	utilsFillBufferIncrementWithSeedX32((uint32_t)MOD_BRAM_CNTRL_ZYNQ_BASEADDR0, 0x04000000, lLength / 4);
	utilsFillBufferIncrementWithSeedX32((UINTPTR)MOD_BRAM_CNTRL_ZYNQ_BASEADDR1, 0x01200000, MOD_BRAM_CNTRL_ZYNQ_B1_WORDS);

	/* Note: For the DMA, use the address that is mapped to the CDMA engine */
	mod_bram_dma_transfer_polling((UINTPTR)MOD_BRAM_CDMA_BASEADDR0, (UINTPTR)MOD_BRAM_CDMA_BASEADDR1, lLength);

	/* Processor compare results of the buffers; use the ZYNQ address map */
	utilsCompareBufferWithSeedX32((UINTPTR)MOD_BRAM_CNTRL_ZYNQ_BASEADDR1, 0x04000000, lLength/4, &lStatus);

	DEBUG_PRINT_LOG_STATUS_RETURN(lStatus, "");

	return(lStatus);
}





/*
 * - MOD_BRAM_CNTRL_BASEADDR0 -> SDRAM_BUFFER0
 */
int mod_bram_dma_test_bram_to_sdram_test_polling() {
	int lStatus= XST_SUCCESS;
	//int i;
	int lLength= MOD_BRAM_CNTRL_ZYNQ_B0_WORDS * 4;
	lLength= 8;

	DEBUG_PRINT_DASH();
	DEBUG_PRINT_ENTER("");
	DEBUG_PRINT_DASH();

	/* Set up the source buffer with data; clear the destination */
	utilsFillBufferIncrementWithSeedX32((UINTPTR)MOD_BRAM_CNTRL_ZYNQ_BASEADDR0, 0x03000000, lLength / 4);
	utilsFillBufferConstantX32((UINTPTR)SDRAM_BRAM_DMA_BUFFER0, 0x0000DEAD, SDRAM_BRAM_DMA_BUFFER0_WORDS);

	/* Note: For the DMA, use the address that is mapped to the CDMA engine */
	mod_bram_dma_transfer_polling((UINTPTR)MOD_BRAM_CDMA_BASEADDR0, (UINTPTR)SDRAM_BRAM_DMA_BUFFER0, lLength);

	/* Processor compare results of the buffers; use the ZYNQ address map */
	utilsCompareBufferWithSeedX32((UINTPTR)SDRAM_BRAM_DMA_BUFFER0, 0x03000000, lLength/4, &lStatus);

	DEBUG_PRINT_LOG_STATUS_RETURN(lStatus, "");

	return(lStatus);
}



/*
 * - SDRAM_BUFFER0 -> MOD_BRAM_CNTRL_BASEADDR0
 */
int mod_bram_dma_test_sdram_to_bram_test_polling() {
	int lStatus= XST_SUCCESS;
	//int i;
	int lLength= MOD_BRAM_CNTRL_ZYNQ_B0_WORDS * 4;

	DEBUG_PRINT_DASH();
	DEBUG_PRINT_ENTER("");
	DEBUG_PRINT_DASH();

	/* Set up the source buffer with data; clear the destination */
	utilsFillBufferIncrementWithSeedX32((UINTPTR)SDRAM_BRAM_DMA_BUFFER0, 0x02000000, lLength / 4);
	utilsFillBufferConstantX32((UINTPTR)MOD_BRAM_CNTRL_ZYNQ_BASEADDR0, 0x00000000, MOD_BRAM_CNTRL_ZYNQ_B0_WORDS);

	/* Note: For the DMA, use the address that is mapped to the CDMA engine */
	mod_bram_dma_transfer_polling((UINTPTR)SDRAM_BRAM_DMA_BUFFER0, (UINTPTR)MOD_BRAM_CDMA_BASEADDR0, lLength);

	if(0) {
		/* Inject Error by changing the FROM buffer prior to the compare. */
		fpgaWriteWordC_D32(MOD_BRAM_CNTRL_ZYNQ_BASEADDR0, 0xDEADBEEF);
	}

	utilsCompareBufferWithSeedX32((uint32_t)MOD_BRAM_CNTRL_ZYNQ_BASEADDR0, 0x02000000, lLength/4, &lStatus);

	DEBUG_PRINT_LOG_STATUS_RETURN(lStatus, "");

	return(lStatus);
}



/* -------------------------------------------------------------------------------------
 *
 *                               BRAM ZYNQ Direct Access
 *
 * -------------------------------------------------------------------------------------
 */

/*
 * NON DMA usage.
 * Simple test to see if the ZYNQ can access the CDMA BRAM via PORT-B of the memory, will
 * do peek/poke access across an AXI-LITE interface to PORT-B.
 *
 * The CDMA engine has access to PORT-A.
 */

int mod_bram_dma_zynq_access_test() {
	int lStatus= XST_SUCCESS;
	//int lResult;
	//uint32_t i;
	//uint32_t uiExpected0, uiExpected1;
	//uint32_t uiActual0, uiActual1;

	DEBUG_PRINT_DASH();
	DEBUG_PRINT_ENTER("*****");
	DEBUG_PRINT_DASH();

	/* Fill some values in the BRAMS */
	utilsFillBufferIncrementWithSeedX32((uint32_t)MOD_BRAM_CNTRL_ZYNQ_BASEADDR0, 0x01100000, MOD_BRAM_CNTRL_ZYNQ_B0_WORDS);
	utilsFillBufferIncrementWithSeedX32((UINTPTR)MOD_BRAM_CNTRL_ZYNQ_BASEADDR1, 0x01200000, MOD_BRAM_CNTRL_ZYNQ_B1_WORDS);

	utilsCompareBufferWithSeedX32((UINTPTR)MOD_BRAM_CNTRL_ZYNQ_BASEADDR0, 0x01100000, MOD_BRAM_CNTRL_ZYNQ_B0_WORDS, &lStatus);
	utilsCompareBufferWithSeedX32((UINTPTR)MOD_BRAM_CNTRL_ZYNQ_BASEADDR1, 0x01200000, MOD_BRAM_CNTRL_ZYNQ_B1_WORDS, &lStatus);

	DEBUG_PRINT_LOG_STATUS_RETURN(lStatus, "");

	return(lStatus);
}


/*
 * NON DMA usage.
 * ZYNQ clear the DMA memory buffers.  Used to clear memory prior to a DMA test.
 * (open) : Might be a good place to understand and use the DMA internal to the ZYNC processors.
 */
int mod_bram_dma_zynq_mem_clear() {
	int lStatus= XST_SUCCESS;
	//uint32_t i;

	DEBUG_PRINT_DASH();
	DEBUG_PRINT_ENTER("*****");
	DEBUG_PRINT_DASH();

	/* Fill some values in the BRAMS */
	utilsFillBufferConstantX32((UINTPTR)MOD_BRAM_CNTRL_ZYNQ_BASEADDR0, 0x00000000, MOD_BRAM_CNTRL_ZYNQ_B0_WORDS);
	utilsFillBufferConstantX32((UINTPTR)MOD_BRAM_CNTRL_ZYNQ_BASEADDR1, 0x00000000, MOD_BRAM_CNTRL_ZYNQ_B1_WORDS);

	utilsFillBufferConstantX32((UINTPTR)SDRAM_BRAM_DMA_BUFFER0, 0x00000000, SDRAM_BRAM_DMA_BUFFER0_WORDS);
	utilsFillBufferConstantX32((UINTPTR)SDRAM_BRAM_DMA_BUFFER1, 0x00000000, SDRAM_BRAM_DMA_BUFFER1_WORDS);

	return(lStatus);
}




/* -------------------------------------------------------------------------------------
 * 										<PRINTS>
 * -------------------------------------------------------------------------------------
 */
void mod_bram_dma_print_regs(void) {
    DEBUG_PRINT_DASH();
    DEBUG_PRINT_ENTER("");
	DEBUG_PRINT_DASH();

	xdrv_xaxicdma_print_regs(&axiCdmaPtr);
}




void mod_bram_dma_print_buffers(void) {
	//int lStatus= XST_SUCCESS;
	uint32_t i;
	uint32_t uiActual;

    DEBUG_PRINT_DASH();
    DEBUG_PRINT_ENTER("");
	DEBUG_PRINT_DASH();

	/* Need to flush the cache, read why again */
	//Xil_DCacheFlushRange((UINTPTR)sourceBuffer, bytes);
	//Xil_DCacheFlushRange((UINTPTR)destinationBuffer, bytes);

	DEBUG_PRINT_ALWAYS("MOD_BRAM_CNTRL_ZYNQ_BASEADDR0");
	for(i=MOD_BRAM_CNTRL_ZYNQ_BASEADDR0; i < (MOD_BRAM_CNTRL_ZYNQ_BASEADDR0 + 8 * 4); i=i+4) {
		fpgaReadWordC_D32(i, &uiActual);
		DEBUG_PRINT_ALWAYS("Address= 0x%08x Data= 0x%08x", i, uiActual);
	}


	DEBUG_PRINT_ALWAYS("MOD_BRAM_CNTRL_ZYNQ_BASEADDR1");
	for(i=MOD_BRAM_CNTRL_ZYNQ_BASEADDR1; i < (MOD_BRAM_CNTRL_ZYNQ_BASEADDR1 + 8 * 4); i=i+4) {
		fpgaReadWordC_D32(i, &uiActual);
		DEBUG_PRINT_ALWAYS("Address= 0x%08x Data= 0x%08x", i, uiActual);
	}


	DEBUG_PRINT_ALWAYS("SDRAM_BRAM_DMA_BUFFER0");
	for(i=SDRAM_BRAM_DMA_BUFFER0; i < (SDRAM_BRAM_DMA_BUFFER0 + 8 * 4); i=i+4) {
		fpgaReadWordC_D32(i, &uiActual);
		DEBUG_PRINT_ALWAYS("Address= 0x%08x Data= 0x%08x", i, uiActual);
	}


	DEBUG_PRINT_ALWAYS("SDRAM_BRAM_DMA_BUFFER1");
	for(i=SDRAM_BRAM_DMA_BUFFER1; i < (SDRAM_BRAM_DMA_BUFFER1 + 8 * 4); i=i+4) {
		fpgaReadWordC_D32(i, &uiActual);
		DEBUG_PRINT_ALWAYS("Address= 0x%08x Data= 0x%08x", i, uiActual);
	}

}



