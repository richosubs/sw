
#include <stdio.h>
#include <stdlib.h> // Std C functions, e.g. exit()
#include <math.h>   // libm header: sqrt(), cos(), etc
#include "xil_io.h"
#include "xparameters.h"
#include "mod_xdma_fifo.h"

#include "xaxidma.h"        // Device driver API for AXI DMA

#include "_macros_print.h"
#include "_macros_entry.h"

#include "_utils_compare.h"

#include "parameter_maps_prj_base.h"

#include "xdrv_xaxidma.h"   // Extended Routines for xaxidma


/* Quick remap in case the xparameters change; only need to change here */


// Declare a XAxiDma object instance
static XAxiDma axiDmaPtr;
//static XAxiDma_Config *CfgDmaPtr;


/*
 * Allocates memory on OCM space.  Linker needs to be set correctly to
 * have the "data section" in the OCM.
 *
 * Currently I also placed the heap & stack in the OCM.  malloc will place memory there,
 * however, don't use malloc, want static assigned memory only.
 */
#define DEF_MAX_WORDS 32
#define DEF_MAX_BYTES 4 * DEF_MAX_WORDS

static uint32_t gFIFO_SourceBuffer[DEF_MAX_WORDS];
static uint32_t gFIFO_DestinationBuffer[DEF_MAX_WORDS];


int mod_xdma_fifo_init() {
	XAxiDma_Config *CfgDmaPtr;
	int lStatus= XST_SUCCESS;
	int lResult;
	// Get pointer to DMA configuration
	CfgDmaPtr = XAxiDma_LookupConfig(XPAR_XDMA_FIFO_DEVICE_ID);
	DEBUG_PRINT_NULL_PTR(CfgDmaPtr, &lResult, "XAxiDma_LookupConfig");
	DEBUG_RETURN_ON_ERROR(lResult);

	// Initialize the DMA handle
	lStatus+= XAxiDma_CfgInitialize(&axiDmaPtr, CfgDmaPtr);
	DEBUG_PRINT_LOG_STATUS_CHK_ERR(lStatus, "DMA setup");

	// Check for scatter gather mode - this example must have simple mode only.  The mode is generated
	// when the core is generated; for the AXI_DMA, I don't see a software switch to change modes
	// as the CDMA has; I might have missed that.
	lStatus+= XAxiDma_HasSg(&axiDmaPtr);
	DEBUG_PRINT_LOG_STATUS_CHK_ERR(XAxiDma_HasSg(&axiDmaPtr), \
			"DMA in SG Mode.  Need to reconfig DMA Core");


	if(axiDmaPtr.Initialized == 0) {
		DEBUG_PRINT_ALWAYS("Driver Not Initialized, Hard exit for ddebug");
		lStatus++;
		exit(0);
	}
	//disable the interrupts
	//DEBUG_PRINT_LOG_PASSED("DMA disable interrupts");
	XAxiDma_IntrDisable(&axiDmaPtr, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrDisable(&axiDmaPtr, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);

	DEBUG_PRINT_LOG_STATUS_RETURN(lStatus, "");

	if(0) {
		// Checking initialized; debug; lost it later for some reason ?
		DEBUG_PRINT_ALWAYS("**********************************");
		DEBUG_PRINT_ALWAYS("FIFO DMA    %p", &axiDmaPtr);
		DEBUG_PRINT_ALWAYS("FIFO DMA  	%x", axiDmaPtr.RegBase);
		DEBUG_PRINT_ALWAYS("FIFO DMA 	%x", axiDmaPtr.Initialized);
		DEBUG_PRINT_ALWAYS("FIFO DMA    %p", &CfgDmaPtr);
		DEBUG_PRINT_ALWAYS("FIFO DMA    %p", &axiDmaPtr.RegBase);
		DEBUG_PRINT_ALWAYS("FIFO DMA    0x%08x", axiDmaPtr.RegBase);
		DEBUG_PRINT_ALWAYS("**********************************");

		mod_xdma_fifo_print_regs();

		exit(0);
	}
	//mod_xdma_fifo_print_regs();



//	Xil_DCacheFlushRange((UINTPTR)&axiDmaPtr, sizeof(XAxiDma));
	//Xil_DCacheFlushRange((UINTPTR)&CfgDmaPtr, sizeof(XAxiDma_Config));

	return(lStatus);
}




/* -------------------------------------------------------------------------------------
 * 									<TESTS>
 * -------------------------------------------------------------------------------------
 */
int mod_xdma_fifo_test(uint32_t uiTEST_SEED) {
   int lStatus= XST_SUCCESS;

   DEBUG_PRINT_DASH();
   DEBUG_PRINT_ENTER("");
   DEBUG_PRINT_DASH();

   lStatus+= mod_xdma_fifo_test_polling(uiTEST_SEED);

   DEBUG_PRINT_LOG_STATUS_RETURN(lStatus, "");

   return(lStatus);
}





int mod_xdma_fifo_test_polling(uint32_t uiTEST_SEED) {
   int lStatus= XST_SUCCESS;

   DEBUG_PRINT_DASH();
   DEBUG_PRINT_ENTER("");
   DEBUG_PRINT_DASH();

   lStatus+= mod_xdma_fifo_test_ocm_to_fifo_polling(uiTEST_SEED);

   lStatus+= mod_xdma_fifo_test_sdram_to_fifo_polling(uiTEST_SEED);

   DEBUG_PRINT_DASH();
   DEBUG_PRINT_LOG_STATUS_RETURN(lStatus, "");
   DEBUG_PRINT_DASH();

   return(lStatus);
}



int mod_xdma_fifo_test_ocm_to_fifo_polling(uint32_t uiTEST_SEED) {
	   int lStatus= XST_SUCCESS;
	   int i;
	   int lLoop= 10;
	   int lLength= DEF_MAX_BYTES;

	   DEBUG_PRINT_DASH();
	   DEBUG_PRINT_ENTER("");
	   DEBUG_PRINT_DASH();

	   cPrintSetDebugLevelWarning();

	   /* 1. Set buffer in program memory to transfer */
	   utilsFillBufferIncrementWithSeedX32((UINTPTR)gFIFO_SourceBuffer, uiTEST_SEED + 0x10000000, lLength/4);

	   /* 2. MM2S : PS->PL transfer into PL FIFO */
	   lStatus+= mod_xdma_fifo_test_transfer_mm2s_polling((UINTPTR)&gFIFO_SourceBuffer, lLength);

	   /* 3. S2MM : PL->PS transfer */
	   lStatus+= mod_xdma_fifo_test_transfer_s2mm_polling((UINTPTR)&gFIFO_DestinationBuffer, lLength);

	   /* 4. Verify Results */
	   utilsCompareBufferWithSeedX32((UINTPTR)&gFIFO_DestinationBuffer, uiTEST_SEED + 0x10000000, lLength/4, &lStatus);

	   cPrintRestoreDebugLevel();

	   DEBUG_PRINT_LOG_INFO("OCM %x %x", &gFIFO_SourceBuffer, &gFIFO_DestinationBuffer);

	   return(lStatus);
}




int mod_xdma_fifo_test_sdram_to_fifo_polling(uint32_t uiTEST_SEED) {
	   int lStatus= XST_SUCCESS;
	   int i;
	   int lLoop= 10;
	   int lLength= SDRAM_BRAM_DMA_BUFFER0_WORDS * 4;

	   DEBUG_PRINT_DASH();
	   DEBUG_PRINT_ENTER("");
	   DEBUG_PRINT_DASH();

	   cPrintSetDebugLevelWarning();

	   /* Set up the source buffer with data; clear the destination */
	   utilsFillBufferIncrementWithSeedX32((UINTPTR)SDRAM_BRAM_DMA_BUFFER0, uiTEST_SEED + 0x80000000, lLength/4);
	   //utilsFillBufferConstantX32((UINTPTR)gFIFO_DestinationBuffer, 0x00000000, lLength/4);

	   lStatus+= mod_xdma_fifo_test_transfer_mm2s_polling((UINTPTR)SDRAM_BRAM_DMA_BUFFER0, lLength);

	   lStatus+= mod_xdma_fifo_test_transfer_s2mm_polling((UINTPTR)SDRAM_BRAM_DMA_BUFFER1, lLength);

	   utilsCompareBufferWithSeedX32((UINTPTR)SDRAM_BRAM_DMA_BUFFER1, uiTEST_SEED + 0x80000000, lLength/4, &lStatus);

	   cPrintRestoreDebugLevel();

	   DEBUG_PRINT_LOG_INFO("DDR %x %x", SDRAM_BRAM_DMA_BUFFER0, SDRAM_BRAM_DMA_BUFFER1);

	   return(lStatus);
}



/* -------------------------------------------------------------------------------------
 * 								     <POLLING>
 * -------------------------------------------------------------------------------------
 */


/*
 * Followed PG021 V7.1: LogiCore IP AXI DMA v7.1 (page 70, Direct Register Mode (Simple DMA, Non-SG)
 */
int mod_xdma_fifo_test_transfer_mm2s_polling(UINTPTR *sourceBuffer, int bytes) {
	   int lStatus= XST_SUCCESS;
	   int i;
	   int lLoop= 10;

	   DEBUG_PRINT_DASH();
	   DEBUG_PRINT_ENTER("");
	   DEBUG_PRINT_DASH();

		/* Need to flush the cache, read why again */
		Xil_DCacheFlushRange((UINTPTR)sourceBuffer, bytes);

		/* Check that the DMA is available */
		do {
			if(XAxiDma_Busy(&axiDmaPtr, XAXIDMA_DMA_TO_DEVICE))
				lLoop--;
	 	   		if(lLoop ==0) {
	 	   		   DEBUG_PRINT_LOG_ERROR("XAxiDma_Busy prior to sending DMA");
	 	   		   return(XST_FAILURE);
		   	   }
		   else
			   lLoop= 0;
	   } while(lLoop > 0);


		/*
		 * MM2S = TX = Transmit
		 */
		XAxiDma_WriteReg(axiDmaPtr.RegBase,
				XAXIDMA_TX_OFFSET + XAXIDMA_CR_OFFSET,
				XAXIDMA_CR_RUNSTOP_MASK);


		XAxiDma_WriteReg(axiDmaPtr.RegBase,
				XAXIDMA_TX_OFFSET + XAXIDMA_SRCADDR_OFFSET,
				LOWER_32_BITS(sourceBuffer));


		if(1) {
			XAxiDma_WriteReg(axiDmaPtr.RegBase,
					XAXIDMA_TX_OFFSET + XAXIDMA_BUFFLEN_OFFSET,
					bytes);
		}


		DEBUG_PRINT_LOG_STATUS_RETURN(lStatus, "");

		return(lStatus);
}



/*
 * Followed PG021 V7.1: LogiCore IP AXI DMA v7.1 (page 70, Direct Register Mode (Simple DMA, Non-SG)
 */
int mod_xdma_fifo_test_transfer_s2mm_polling(UINTPTR *destinationBuffer, int bytes) {
	   int lStatus= XST_SUCCESS;
	   int i;
	   int lLoop= 10;

	   DEBUG_PRINT_DASH();
	   DEBUG_PRINT_ENTER("");
	   DEBUG_PRINT_DASH();


		/* Check that the DMA is available */
		do {
			if(XAxiDma_Busy(&axiDmaPtr, XAXIDMA_DEVICE_TO_DMA))
				lLoop--;
	 	   		if(lLoop ==0) {
	 	   		   DEBUG_PRINT_LOG_ERROR("XAxiDma_Busy prior to sending DMA");
	 	   		   return(XST_FAILURE);
		   	   }
		   else
			   lLoop= 0;
	   } while(lLoop > 0);

		/* Need to flush the cache, read why again */
	   // (open) : Might not be needed.
	   //Xil_DCacheFlushRange((UINTPTR)destinationBuffer, bytes);

		/*
		 * S2MM = RX = Receive
		 */
	   XAxiDma_WriteReg(axiDmaPtr.RegBase,
				XAXIDMA_RX_OFFSET + XAXIDMA_CR_OFFSET,
				XAXIDMA_CR_RUNSTOP_MASK);


	   XAxiDma_WriteReg(axiDmaPtr.RegBase,
				XAXIDMA_RX_OFFSET + XAXIDMA_DESTADDR_OFFSET,
				LOWER_32_BITS(destinationBuffer));


	   if(1) {
			XAxiDma_WriteReg(axiDmaPtr.RegBase,
					XAXIDMA_RX_OFFSET + XAXIDMA_BUFFLEN_OFFSET,
					bytes);
		}

		DEBUG_PRINT_LOG_STATUS_RETURN(lStatus, "");

		return(lStatus);
}




/* -------------------------------------------------------------------------------------
 * 										<PRINTS>
 * -------------------------------------------------------------------------------------
 */
void mod_xdma_fifo_print_regs(void) {
    DEBUG_PRINT_DASH();
    DEBUG_PRINT_ENTER("");
	DEBUG_PRINT_DASH();

	DEBUG_PRINT_ALWAYS("FIFO DMA    %p", &axiDmaPtr);
	DEBUG_PRINT_ALWAYS("FIFO DMA    %p", &axiDmaPtr.RegBase);
	DEBUG_PRINT_ALWAYS("FIFO DMA    0x%08x", axiDmaPtr.RegBase);

	xdrv_xaxidma_print_regs(&axiDmaPtr);
}

