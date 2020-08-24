

/* Definitions for peripheral PSU_DDR_0 */
//#define XPAR_PSU_DDR_0_S_AXI_BASEADDR 0x00000000
//#define XPAR_PSU_DDR_0_S_AXI_HIGHADDR 0x7FFFFFFF





#include <stdio.h>
#include <stdlib.h> // Std C functions, e.g. exit()
#include <math.h>   // libm header: sqrt(), cos(), etc
#include "xil_io.h"
#include "xstatus.h"
#include "xparameters.h"
#include "comp_dram.h"
#include "_macros_print.h"




int comp_dram_quick_test() {
	int lStatus = XST_SUCCESS;
	int lResult;
	uint32_t i, add, uiRead;
	uint32_t *lAddrPtr;


	lAddrPtr= XPAR_PSU_DDR_0_S_AXI_BASEADDR;

	// Write
	add= 0;
	for(i=0; i <= XPAR_PSU_DDR_0_S_AXI_HIGHADDR; i=i+add) {
		lAddrPtr= i;

		if(add == 0)
			add=4;
		else
			add= add * 2;

		*lAddrPtr= i;

		DEBUG_PRINT_LOG_DEBUG("Write: Address= %x  Data= %x", lAddrPtr, i);
	}



	// Read
	add= 0;
	for(i=0; i <= XPAR_PSU_DDR_0_S_AXI_HIGHADDR; i=i+add) {
		lAddrPtr= i;

		if(add == 0)
			add=4;
		else
			add= add * 2;

		uiRead= *lAddrPtr;

		DEBUG_COMPARE(lResult, i, uiRead);
		lStatus+=lResult;

		DEBUG_COMPARE_TOTAL(lStatus, lResult, uiRead, i, "Verify: Address= %x  Data= %x  Expected= %x", lAddrPtr, uiRead, i);
	}


	DEBUG_PRINT_LOG_STATUS(lStatus, "DRAM Test Results Errors= %d", lStatus);


	if(0) {
		DEBUG_PRINT_LOG_DEBUG("Read 1: %x", *((u32 *)0X00000000));
		*((u32 *)0X00000000)= 0x11111111;
		*((u32 *)0X00000004)= 0x44444444;
		*((u32 *)0X00000008)= 0x88888888;
		*((u32 *)0X01000000)= 0x11111122;
		*((u32 *)0X02000004)= 0x44444422;
		*((u32 *)0X03000008)= 0x88888822;
		DEBUG_PRINT_LOG_DEBUG("Read 2: %x", *((u32 *)0X00000000));
		DEBUG_PRINT_LOG_DEBUG("Read 2: %x", *((u32 *)0X00000004));
		DEBUG_PRINT_LOG_DEBUG("Read 2: %x", *((u32 *)0X00000008));
		DEBUG_PRINT_LOG_DEBUG("Read 2: %x", *((u32 *)0X01000000));
		DEBUG_PRINT_LOG_DEBUG("Read 2: %x", *((u32 *)0X02000004));
		DEBUG_PRINT_LOG_DEBUG("Read 2: %x", *((u32 *)0X03000008));
	}

	return(lStatus);
}
