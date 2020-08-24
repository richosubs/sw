/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

/* UG871: Chapter 10, HLS MACC */


#include <stdio.h>
#include "xil_io.h"
#include "xparameters.h"
#include "xHls_macc.h" // Device driver for HLS HW block
#include "mod_hls_macc.h"

/* Interrupt Controller */
#include "xscugic.h" // Processor interrupt controller device driver

#include "_macros_print.h"
XScuGic ScuGic;

/* HLS macc HW instance */
XHls_macc HlsMacc;

/* Define global variables to interface with the interrupt service routine (ISR). */
volatile static int RunHlsMacc = 0;
volatile static int ResultAvailHlsMacc = 0;






/* Flashes 2 x LEDs, simple test to see that the fabric logic is program and running */
int hls_macc_test() {
	int lStatus;
	int oResults, lA, lB, lExpected;

	lStatus = hls_macc_init(&HlsMacc);
	DEBUG_PRINT_LOG_STATUS(lStatus, "HLS_MACC_INIT Initialization");


	hls_macc_test_one(1, 100);
	hls_macc_test_one(-5, 500);
	hls_macc_test_one(3, -888);
	hls_macc_test_one(-33, -213);
	hls_macc_test_one(21, 110);
	hls_macc_test_one(431, 100);
	hls_macc_test_one(4321, 100);

	return(lStatus);
}




int hls_macc_test_one(int x, int y) {
	int lStatus;
	int oResults, lExpected;

	lExpected= x * y;
	hls_macc_run_polling(x, y, &oResults);
	DEBUG_COMPARE(lStatus, lExpected, oResults);
	DEBUG_PRINT_LOG_STATUS(lStatus, "A * B :: %d * %d = %d (Actual) %d (Expected)", x, y, oResults, lExpected);

	return(lStatus);
}





int hls_macc_run_polling(int a, int b, int *oResults) {
	int lStatus= XST_SUCCESS;
	int res_hw;

	//set the input parameters of the HLS block
	XHls_macc_Set_a(&HlsMacc, a);
	XHls_macc_Set_b(&HlsMacc, b);
	XHls_macc_Set_accum_clr(&HlsMacc, 1);

	if (XHls_macc_IsReady(&HlsMacc))
		DEBUG_PRINT_LOG_DEBUG("HLS peripheral is ready. Starting... ");
	else {
		DEBUG_PRINT_LOG_DEBUG("!!! HLS peripheral is not ready! Exiting...");
		exit(-1);
	}

	XHls_macc_Start(&HlsMacc);
	do {
		res_hw = XHls_macc_Get_accum(&HlsMacc);
	}
	while (!XHls_macc_IsReady(&HlsMacc));
	DEBUG_PRINT_LOG_DEBUG("Detected HLS peripheral complete. Result received.");
	DEBUG_PRINT_LOG_DEBUG("a * b = c %d %d %d", a, b, res_hw);

	*oResults= res_hw;

	return(lStatus);
}




/* 5. UG871, page 231.
 * Define a function to wrap all run-once API initialization function calls for
 * the HLS block. */
int hls_macc_init(XHls_macc *hls_maccPtr) {
	XHls_macc_Config *cfgPtr;
	int lStatus;
	cfgPtr = XHls_macc_LookupConfig(XPAR_XHLS_MACC_0_DEVICE_ID);
	if (!cfgPtr) {
		DEBUG_PRINT_LOG_ERROR("Lookup of accelerator configuration failed");
		return XST_FAILURE;
	}
	lStatus = XHls_macc_CfgInitialize(hls_maccPtr, cfgPtr);
	DEBUG_PRINT_LOG_STATUS(lStatus, "Accelerator setup");

	lStatus = hls_macc_setup_interrupt();
	DEBUG_PRINT_LOG_STATUS(lStatus, "Interrupt setup");

	return lStatus;
}


/* 6. UG871, page 232.
 * Define a helper function to wrap the HLS block API calls required to enable its interrupt
 * and start the block. */
void hls_macc_start(void *InstancePtr){
	XHls_macc *pAccelerator = (XHls_macc *)InstancePtr;
	XHls_macc_InterruptEnable(pAccelerator,1);
	XHls_macc_InterruptGlobalEnable(pAccelerator);
	XHls_macc_Start(pAccelerator);
}


void hls_macc_isr(void *InstancePtr){
	XHls_macc *pAccelerator = (XHls_macc *)InstancePtr;
	//Disable the global interrupt
	XHls_macc_InterruptGlobalDisable(pAccelerator);
	//Disable the local interrupt
	XHls_macc_InterruptDisable(pAccelerator,0xffffffff);
	// clear the local interrupt
	XHls_macc_InterruptClear(pAccelerator,1);
	ResultAvailHlsMacc = 1;
	// restart the core if it should run again
	if(RunHlsMacc){
		hls_macc_start(pAccelerator);
	}
}




/*
 * Define a routine to setup the PS interrupt handler and register the HLS
 * peripheral’s ISR.
 */
int hls_macc_setup_interrupt() {
	//This functions sets up the interrupt on the Arm
	int result;
	XScuGic_Config *pCfg = XScuGic_LookupConfig(XPAR_SCUGIC_SINGLE_DEVICE_ID);
	if (pCfg == NULL){
		DEBUG_PRINT_LOG_ERROR("Interrupt Configuration Lookup Failed");
		return XST_FAILURE;
	}

	result = XScuGic_CfgInitialize(&ScuGic,pCfg,pCfg->CpuBaseAddress);
	if(result != XST_SUCCESS){
		return result;
	}

	// self-test
	result = XScuGic_SelfTest(&ScuGic);
	if(result != XST_SUCCESS){
		return result;
	}

	// Initialize the exception handler
	Xil_ExceptionInit();
	// Register the exception handler
	//print("Register the exception handler\n\r");
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
	(Xil_ExceptionHandler)XScuGic_InterruptHandler,&ScuGic);
	//Enable the exception handler
	Xil_ExceptionEnable();
	// Connect the Adder ISR to the exception table
	//print("Connect the Adder ISR to the Exception handler table\n\r");

	/* OPEN: Need to understand how to do an interrupt handler
	 *
	result = XScuGic_Connect(&ScuGic, XPAR_FABRIC_MOD_HLS_MACC_INTERRUPT_INTR,
	(Xil_InterruptHandler)hls_macc_isr,&HlsMacc);
	if(result != XST_SUCCESS){
		return result;
	}

	*/

	/* print("Enable the Adder ISR\n\r");
	XScuGic_Enable(&ScuGic,XPAR_FABRIC_MOD_HLS_MACC_INTERRUPT_INTR);
	*/

	return XST_SUCCESS;
}



