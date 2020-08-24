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
// OCM_CFG
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

/* UG871: Chapter 10, HLS MACC
 *
 * Note: To build, C math library (libm) must be in the linker setting; see UG871, page 243,
 * Specify C/C++ Build Setting
 * */


#include <stdio.h>
#include <stdlib.h> // Std C functions, e.g. exit()
#include <math.h>   // libm header: sqrt(), cos(), etc
#include "xil_io.h"
#include "_parameter_maps.h"
#include "mod_hls_fft.h"

#include "xaxidma.h"      // Device driver API for AXI DMA

#include "_macros_print.h"
#include "_macros_entry.h"

#include "xdrv_xaxidma.h" // Extended Device driver API for AXI DMA





// Define the length of the (real input) FFT data.
// <NOTE> : This needs to match what is in the core !
// --------------------------------------------------------------------------------------------------------
// C:\Users\richo\workspace\_xilinx2020_Tutorials\ug871-design-files\Using_IP_with_Zynq\lab2\arm_src
//    - UG871 : V2019.v
// --------------------------------------------------------------------------------------------------------
#define REAL_FFT_LEN  1024

// Define a type to hold complex FFT output (real) spectral data
typedef struct {
   short re;
   short im;
} complex16;


// Declare a XAxiDma object instance
XAxiDma *axiDmaPtr;
XAxiDma_Config *CfgPtr;

int mod_hls_fft_test() {
	int lStatus= XST_SUCCESS;
	int lResult= XST_SUCCESS;
	int i, j;
	static short realdata[4*REAL_FFT_LEN];
	volatile static complex16 realspectrum[REAL_FFT_LEN/2];

	DEBUG_PRINT_DASH();
	DEBUG_PRINT_DASH();
	DEBUG_PRINT_DASH();
	DEBUG_PRINT_DASH();
	DEBUG_PRINT_DASH();

	lStatus= mod_hls_fft_init_dma(axiDmaPtr);

	for (i = 0; i < 4; i++)
		mod_hls_fft_generate_waveform(realdata + i * REAL_FFT_LEN, REAL_FFT_LEN);

	DEBUG_PRINT_LOG_DEBUG("%x ", realdata[0]);
	DEBUG_PRINT_LOG_DEBUG("%x ", realdata[1]);
	DEBUG_PRINT_LOG_DEBUG("%x ", realdata[2]);
	DEBUG_PRINT_LOG_DEBUG("%x ", realdata[3]);

	DEBUG_PRINT_LOG_DEBUG("%x ", (u32)realdata);


	DEBUG_BREAK("Check out the address of the data to burst");

	// *IMPORTANT* - flush contents of 'realdata' from data cache to memory
	// before DMA. Otherwise DMA is likely to get stale or uninitialized data
   Xil_DCacheFlushRange((unsigned)realdata[0], 4 * REAL_FFT_LEN * sizeof(short));
   // DMA enough data to push out first result data set completely

   //lStatus= XAxiDma_Selftest(axiDmaPtr);
   //DEBUG_PRINT_ALWAYS_STATUS(lStatus, "::Self Test  %d", lStatus);


   XAxiDma_Reset(axiDmaPtr);

   lResult= XAxiDma_ResetIsDone(axiDmaPtr);
   DEBUG_PRINT_LOG_SET(lResult, "::Reset Is Done");

   lResult= XAxiDma_Busy(axiDmaPtr, XAXIDMA_DMA_TO_DEVICE);
   DEBUG_PRINT_LOG_CLR(lResult, "::DMA Not Busy");
   lResult= XAxiDma_Busy(axiDmaPtr, XAXIDMA_DMA_TO_DEVICE);
   DEBUG_PRINT_LOG_CLR(lResult, "::DMA Not Busy");
   lResult= XAxiDma_Busy(axiDmaPtr, XAXIDMA_DMA_TO_DEVICE);
   DEBUG_PRINT_LOG_CLR(lResult, "::DMA Not Busy");

   //lStatus+= DEBUG_PRINT_LOG_BIT_SET(XAxiDma_ResetIsDone(axiDmaPtr), "::Reset Is Done");
  // lStatus+= DEBUG_PRINT_LOG_BIT_CLR(XAxiDma_Busy(axiDmaPtr), "::DMA Not Busy");

   //lStatus= XAxiDma_Busy(axiDmaPtr, XAXIDMA_DMA_TO_DEVICE);
   //DEBUG_PRINT_ALWAYS_STATUS(lStatus, "::DMA Busy     %d", lStatus);

   //u32 XAxiDma_SimpleTransfer(XAxiDma *InstancePtr, UINTPTR BuffAddr, u32 Length, int Direction);
   DEBUG_BREAK("Trigger ILA");

   while(1) {
	   DEBUG_PRINT_DASH();
	   DEBUG_PRINT_LOG_DEBUG("1: Sending a DMA Transfer Address= %x", (u32)realdata[0]);
	   DEBUG_PRINT_DASH();
	   mod_hls_fft_print_dma();
	   //lStatus = XAxiDma_SimpleTransfer(axiDmaPtr, (u32)realdata, 4 * REAL_FFT_LEN * sizeof(short), XAXIDMA_DMA_TO_DEVICE);
	   lStatus = XAxiDma_SimpleTransfer(axiDmaPtr, (u32)0x00000000, 4 * REAL_FFT_LEN * sizeof(short), XAXIDMA_DMA_TO_DEVICE);
	   DEBUG_PRINT_ALWAYS_STATUS(lStatus, "::DMA Transfer PS->PL %d", lStatus);
	   lResult= XAxiDma_ResetIsDone(axiDmaPtr);
	   DEBUG_PRINT_LOG_SET(lResult, "::Reset Is Done");
	   lResult= XAxiDma_Busy(axiDmaPtr, XAXIDMA_DMA_TO_DEVICE);
	   DEBUG_PRINT_LOG_CLR(lResult, "::DMA Not Busy");



	   DEBUG_PRINT_DASH();
	   DEBUG_PRINT_LOG_DEBUG("2: Sending a DMA Transfer Address= %x", (u32)realdata);
	   DEBUG_PRINT_DASH();
	   mod_hls_fft_print_dma();
	   //lStatus = XAxiDma_SimpleTransfer(axiDmaPtr, (u32)realdata, 4 * REAL_FFT_LEN * sizeof(short), XAXIDMA_DMA_TO_DEVICE);
	   lStatus = XAxiDma_SimpleTransfer(axiDmaPtr, (u32)0x00000000, 4 * REAL_FFT_LEN * sizeof(short), XAXIDMA_DMA_TO_DEVICE);
	   DEBUG_PRINT_ALWAYS_STATUS(lStatus, "::DMA Transfer: PS->PL %d", lStatus);
	   lResult= XAxiDma_ResetIsDone(axiDmaPtr);
	   DEBUG_PRINT_LOG_SET(lResult, "::Reset Is Done");
	   lResult= XAxiDma_Busy(axiDmaPtr, XAXIDMA_DMA_TO_DEVICE);
	   DEBUG_PRINT_LOG_CLR(lResult, "::DMA Not Busy");

	   DEBUG_PRINT_DASH();
	   mod_hls_fft_print_dma();
   }

   if(0) {
	   xil_printf("%x \r\n", (u32*)realdata);
	   xil_printf("%x \r\n", (u32)realdata[0]);
	   xil_printf("%x \r\n", &realdata[0]);
	   return(0);
   }

   if(1) {
	   // Setup DMA from PL to PS memory using AXI DMA's 'simple' transfer mode
	   lStatus = XAxiDma_SimpleTransfer(axiDmaPtr, (u32)realspectrum, REAL_FFT_LEN / 2 * sizeof(complex16), XAXIDMA_DEVICE_TO_DMA);
	   DEBUG_PRINT_ALWAYS_STATUS(lStatus, "::DMA Transfer: PL->PS %d", lStatus);
	   mod_hls_fft_print_dma();

	   Xil_DCacheInvalidateRange((unsigned)realspectrum,
	   		REAL_FFT_LEN / 2 * sizeof(complex16));

	   for (j = 0; j < REAL_FFT_LEN / 2; j++) {
	   	// Convert the fixed point (s.15) values into floating point values
		   float real = (float)realspectrum[j].re / 32767.0f;
		   float imag = (float)realspectrum[j].im / 32767.0f;
		   float mag = sqrtf(real * real + imag * imag);
		   printf("Energy detected in bin %3d - ",j);
		   printf("{%8.5f, %8.5f}; mag = %8.5f\n\r", real, imag, mag);
		   if (mag > 0.00390625f) {
			   printf("Energy detected in bin %3d - ",j);
			   printf("{%8.5f, %8.5f}; mag = %8.5f\n\r", real, imag, mag);
		   }
	   }
	   return(0);
   }

   // Do multiple DMA xfers from the RealFFT core's output stream and
   // display data for bins with significant energy. After the first frame,
   // there should only be energy in bins around the frequencies specified
   // in the generate_waveform() function - currently bins 191~193 only
   for (i = 0; i < 8; i++) {
	   // Setup DMA from PL to PS memory using AXI DMA's 'simple' transfer mode
	   lStatus = XAxiDma_SimpleTransfer(axiDmaPtr, (u32)realspectrum, REAL_FFT_LEN / 2 * sizeof(complex16), XAXIDMA_DEVICE_TO_DMA);
	   DEBUG_PRINT_ALWAYS_STATUS(lStatus, "::DMA Transfer %d", i);
	   // Poll the AXI DMA core
	   do {
		   lStatus = XAxiDma_Busy(axiDmaPtr, XAXIDMA_DEVICE_TO_DMA);
		   DEBUG_PRINT_ALWAYS_STATUS(lStatus, "::DMA Busy");
	   } while(lStatus);
	   // Data cache must be invalidated for 'realspectrum' buffer after DMA
	   Xil_DCacheInvalidateRange((unsigned)realspectrum,
	   		REAL_FFT_LEN / 2 * sizeof(complex16));
	   // DMA another frame of data to PL
	   if (!XAxiDma_Busy(axiDmaPtr, XAXIDMA_DMA_TO_DEVICE))
		   lStatus = XAxiDma_SimpleTransfer(axiDmaPtr, (u32)realdata, REAL_FFT_LEN * sizeof(short), XAXIDMA_DMA_TO_DEVICE);
	   printf("\n\rFrame received:\n\r");
	   // Detect energy in spectral data above a set threshold
	   for (j = 0; j < REAL_FFT_LEN / 2; j++) {
	   	// Convert the fixed point (s.15) values into floating point values
		   float real = (float)realspectrum[j].re / 32767.0f;
		   float imag = (float)realspectrum[j].im / 32767.0f;
		   float mag = sqrtf(real * real + imag * imag);
		   if (mag > 0.00390625f) {
			   printf("Energy detected in bin %3d - ",j);
			   printf("{%8.5f, %8.5f}; mag = %8.5f\n\r", real, imag, mag);
		   }
	   }
	   printf("End of frame.\n\r");
	   fflush(stdout);
   }




	return(0);
}


// XPAR_MOD_AXI_DMA_BASEADDR
int mod_hls_fft_init_dma(){
   int lStatus= XST_SUCCESS;
   int lResult;
   // Get pointer to DMA configuration
   CfgPtr = XAxiDma_LookupConfig(XPAR_FFT_DMA_ENG_DEVICE_ID);
   DEBUG_PRINT_NULL_PTR(CfgPtr, &lResult, "XAxiDma_LookupConfig");

   // Initialize the DMA handle
   lStatus = XAxiDma_CfgInitialize(axiDmaPtr, CfgPtr);
   DEBUG_PRINT_LOG_STATUS(lStatus, "DMA setup");

   //check for scatter gather mode - this example must have simple mode only
   if(XAxiDma_HasSg(axiDmaPtr)){
	   DEBUG_PRINT_LOG_ERROR("DMA in SG Mode.  Need to reconfig DMA Core");
	   return XST_FAILURE;
   }
   else {
	   DEBUG_PRINT_LOG_PASSED("DMA not in SG Mode");
   }

   //disable the interrupts
   DEBUG_PRINT_LOG_PASSED("DMA disable interrupts");
   XAxiDma_IntrDisable(axiDmaPtr, XAXIDMA_IRQ_ALL_MASK,XAXIDMA_DEVICE_TO_DMA);
   XAxiDma_IntrDisable(axiDmaPtr, XAXIDMA_IRQ_ALL_MASK,XAXIDMA_DMA_TO_DEVICE);

   mod_hls_fft_print_dma();
   return XST_SUCCESS;
}


void mod_hls_fft_generate_waveform(short *signal_buf, int num_samples) {
	const float cycles_per_win = 192.0f;
	const float phase = 0.0f;
	const float ampl = 0.9f;
	int i;
	for (i = 0; i < num_samples; i++) {
		float sample = ampl * cosf((i * 2 * M_PI * cycles_per_win / (float)num_samples) + phase);
		sample= i;

		signal_buf[i] = (short)(32767.0f * sample);

		signal_buf[i] = (short)sample;
	}

	if(1) {
		DEBUG_PRINT_LOG_DEBUG("Number Samples: %x", num_samples);
		DEBUG_PRINT_LOG_DEBUG("Address: %x", signal_buf[0]);
		DEBUG_PRINT_LOG_DEBUG("Address: %x", signal_buf[1]);
		DEBUG_PRINT_LOG_DEBUG("Address: %x", signal_buf[2]);
		DEBUG_PRINT_LOG_DEBUG("Address: %x", signal_buf[3]);
		DEBUG_PRINT_LOG_DEBUG("Address: %x", *signal_buf);
		DEBUG_PRINT_LOG_DEBUG("Address: %x", signal_buf);
		DEBUG_PRINT_LOG_DEBUG("Address: %x", *((short *)0XFFFDF0B8));
	}
}



void mod_hls_fft_print_dma(void) {
    DEBUG_PRINT_DASH();
    DEBUG_PRINT_ENTER("");
	DEBUG_PRINT_DASH();

	xdrv_xaxidma_print_regs(axiDmaPtr);
}

