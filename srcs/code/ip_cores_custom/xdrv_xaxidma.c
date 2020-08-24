#include <stdio.h>
#include <stdlib.h> // Std C functions, e.g. exit()
#include <math.h>   // libm header: sqrt(), cos(), etc
#include "xil_io.h"
#include "xparameters.h"
#include "xdrv_xaxidma.h"

#include "xaxidma.h" // Device driver API for AXI DMA
#include "_macros_include_all.h"




void xdrv_xaxidma_print_regs(XAxiDma *InstancePtr) {
	uint32_t uiData;
	UINTPTR lAddrPtr;

	DEBUG_PRINT_POUND();

	DEBUG_PRINT_ALWAYS("RegBase       = 0x%08x", InstancePtr->RegBase);
	DEBUG_PRINT_ALWAYS("HasMm2S       = 0x%08x", InstancePtr->HasMm2S);
	DEBUG_PRINT_ALWAYS("HasS2Mm       = 0x%08x", InstancePtr->HasS2Mm);
	DEBUG_PRINT_ALWAYS("Initialized   = 0x%08x", InstancePtr->Initialized);
	DEBUG_PRINT_ALWAYS("HasSg         = 0x%08x", InstancePtr->HasSg);
	DEBUG_PRINT_ALWAYS("TxNumChannels = 0x%08x", InstancePtr->TxNumChannels);
	DEBUG_PRINT_ALWAYS("RxNumChannels = 0x%08x", InstancePtr->RxNumChannels);
	DEBUG_PRINT_ALWAYS("MicroDmaMode  = 0x%08x", InstancePtr->MicroDmaMode);
	DEBUG_PRINT_ALWAYS("AddrWidth     = 0x%08x", InstancePtr->AddrWidth);
	DEBUG_PRINT_NEWLINE("");

	DEBUG_PRINT_DASH();
	DEBUG_PRINT_ALWAYS("***** XAXIDMA_TX_OFFSET");
	/*
	 *                      <XAXIDMA_TX_OFFSET>
	 */
	lAddrPtr= InstancePtr->RegBase + XAXIDMA_TX_OFFSET + XAXIDMA_CR_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_NEWLINE("");
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "MM2S_DMACR");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_CR_RUNSTOP_MASK,"- Run Stop");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_CR_RESET_MASK,"- Reset");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_CR_KEYHOLE_MASK,"- Keyhole");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_CR_CYCLIC_MASK,"- Cyclic");
	//
	lAddrPtr= InstancePtr->RegBase + XAXIDMA_TX_OFFSET + XAXIDMA_SR_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_NEWLINE("");
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "MM2S_DMASR");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_HALTED_MASK,"- halted");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_IDLE_MASK,"- idle");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, 0x08,"- sg");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_ERR_INTERNAL_MASK,"- err int");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_ERR_SLAVE_MASK,"- err slave");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_ERR_DECODE_MASK,"- err decode");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_ERR_SG_INT_MASK,"- err sg int");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_ERR_SG_SLV_MASK,"- err sg slv");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_ERR_SG_DEC_MASK,"- err sg dec");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_ERR_ALL_MASK,"- err all");
	//
	lAddrPtr= InstancePtr->RegBase + XAXIDMA_TX_OFFSET + XAXIDMA_SRCADDR_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_NEWLINE("");
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "SRCADDR");
	//
	lAddrPtr= InstancePtr->RegBase + XAXIDMA_TX_OFFSET + XAXIDMA_DESTADDR_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_NEWLINE("");
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "DESTADDR");
	//
	lAddrPtr= InstancePtr->RegBase + XAXIDMA_TX_OFFSET + XAXIDMA_BUFFLEN_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_NEWLINE("");
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "BUFFLEN");
	//

	DEBUG_PRINT_DASH();
	DEBUG_PRINT_ALWAYS("***** XAXIDMA_RX_OFFSET");
	/*
	 *                      <XAXIDMA_RX_OFFSET>
	 */
	lAddrPtr= InstancePtr->RegBase + XAXIDMA_RX_OFFSET + XAXIDMA_CR_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_NEWLINE("");
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "SS2M_DMACR");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_CR_RUNSTOP_MASK,"- Run Stop");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_CR_RESET_MASK,"- Reset");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_CR_KEYHOLE_MASK,"- Keyhole");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_CR_CYCLIC_MASK,"- Cyclic");
	//
	lAddrPtr= InstancePtr->RegBase + XAXIDMA_RX_OFFSET + XAXIDMA_SR_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_NEWLINE("");
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "SS2M_DMASR");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_HALTED_MASK,"- halted");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_IDLE_MASK,"- idle");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, 0x08,"- sg");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_ERR_INTERNAL_MASK,"- err int");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_ERR_SLAVE_MASK,"- err slave");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_ERR_DECODE_MASK,"- err decode");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_ERR_SG_INT_MASK,"- err sg int");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_ERR_SG_SLV_MASK,"- err sg slv");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_ERR_SG_DEC_MASK,"- err sg dec");
	DEBUG_PRINT_LOG_DEBUG_MASK(uiData, XAXIDMA_ERR_ALL_MASK,"- err all");
	//
	lAddrPtr= InstancePtr->RegBase + XAXIDMA_RX_OFFSET + XAXIDMA_SRCADDR_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_NEWLINE("");
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "SRCADDR");
	//
	lAddrPtr= InstancePtr->RegBase + XAXIDMA_RX_OFFSET + XAXIDMA_DESTADDR_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_NEWLINE("");
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "DESTADDR");
	//
	lAddrPtr= InstancePtr->RegBase + XAXIDMA_RX_OFFSET + XAXIDMA_BUFFLEN_OFFSET;
	fpgaReadWordC_D32(lAddrPtr, &uiData);
	DEBUG_PRINT_NEWLINE("");
	DEBUG_PRINT_LOG_DEBUG_REG(lAddrPtr, uiData, "BUFFLEN");



	DEBUG_PRINT_POUND();
}

