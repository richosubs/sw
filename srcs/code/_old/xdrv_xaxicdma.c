#include <stdio.h>
#include <stdlib.h> // Std C functions, e.g. exit()
#include <math.h>   // libm header: sqrt(), cos(), etc
#include "xil_io.h"
#include "xparameters.h"
#include "xdrv_xaxicdma.h"

#include "xaxicdma.h" // Device driver API for AXI DMA
#include "_macros_include_all.h"



void xdrv_xaxicdma_print_regs(XAxiCdma *InstancePtr) {
	uint32_t uiData;
	UINTPTR lAddrPtr;

	cPrintSetDebugLevelShowAll();

	DEBUG_PRINT_POUND();

	DEBUG_PRINT_ALWAYS("RegBase         = 0x%08x", InstancePtr->BaseAddr);
	DEBUG_PRINT_ALWAYS("Initialized     = 0x%08x", InstancePtr->Initialized);
	DEBUG_PRINT_ALWAYS("SimpleOnlyBuild = 0x%08x", InstancePtr->SimpleOnlyBuild);
	DEBUG_PRINT_ALWAYS("HasDRE          = 0x%08x", InstancePtr->HasDRE);
	DEBUG_PRINT_ALWAYS("IsLite          = 0x%08x", InstancePtr->IsLite);
	DEBUG_PRINT_ALWAYS("WordLength      = 0x%08x", InstancePtr->WordLength);
	DEBUG_PRINT_ALWAYS("MaxTransLen     = 0x%08x", InstancePtr->MaxTransLen);
	DEBUG_PRINT_ALWAYS("SimpleNotDone   = 0x%08x", InstancePtr->SimpleNotDone);
	DEBUG_PRINT_ALWAYS("SGWaiting       = 0x%08x", InstancePtr->SGWaiting);
	DEBUG_PRINT_NEWLINE("");


	lAddrPtr= InstancePtr->BaseAddr + XAXICDMA_CR_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "CDMA Control Register");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXICDMA_CR_RESET_MASK, "- Reset");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXICDMA_CR_SGMODE_MASK, "- SG Mode");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXICDMA_CR_KHOLE_RD_MASK, "- Keyhole RD");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXICDMA_CR_KHOLE_WR_MASK, "- Keyhole WR");


	lAddrPtr= InstancePtr->BaseAddr + XAXICDMA_SR_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "CDMA Status Register");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXICDMA_SR_IDLE_MASK, "- Idle");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXICDMA_SR_SGINCLD_MASK, "- SGIncld");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXICDMA_SR_ERR_INTERNAL_MASK, "- DMAIntErr");



	lAddrPtr= InstancePtr->BaseAddr + XAXICDMA_CDESC_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "CDMA Current Descriptor Pointer Register");

	lAddrPtr= InstancePtr->BaseAddr + XAXICDMA_CDESC_MSB_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "CDMA Current Descriptor Pointer MSB Register");


	lAddrPtr= InstancePtr->BaseAddr + XAXICDMA_TDESC_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "CDMA Tail Descriptor Pointer Register");


	lAddrPtr= InstancePtr->BaseAddr + XAXICDMA_TDESC_MSB_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "XCDMA Tail Descriptor Pointer MSB Register");


	lAddrPtr= InstancePtr->BaseAddr + XAXICDMA_SRCADDR_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "XCDMA Source Address Register");


	lAddrPtr= InstancePtr->BaseAddr + XAXICDMA_SRCADDR_MSB_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "XCDMA Source Address MSB Register");


	lAddrPtr= InstancePtr->BaseAddr + XAXICDMA_DSTADDR_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "XCDMA Destination Address Register");


	lAddrPtr= InstancePtr->BaseAddr + XAXICDMA_DSTADDR_MSB_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "XCDMA Destination Address MSB Register");


	lAddrPtr= InstancePtr->BaseAddr + XAXICDMA_BTT_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "XCDMA Bytes To Transfer Register");

	cPrintRestoreDebugLevel();

	DEBUG_PRINT_POUND();
}


  /**< Datamover internal err */
