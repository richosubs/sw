
#ifndef __MOD_XDMA_FIFO_H_
#define __MOD_XDMA_FIFO_H_


#include "xaxidma.h" // Device driver API for AXI DMA



int mod_xdma_fifo_init();


/* -------------------------------------------------------------------------------------
 * 									<TESTS>
 * -------------------------------------------------------------------------------------
 */
int mod_xdma_fifo_test(uint32_t uiTEST_SEED);
int mod_xdma_fifo_test_polling(uint32_t uiTEST_SEED);


/* -------------------------------------------------------------------------------------
 * 								     <POLLING>
 * -------------------------------------------------------------------------------------
 */
int mod_xdma_fifo_test_transfer_mm2s_polling(UINTPTR *sourceBuffer, int bytes);
int mod_xdma_fifo_test_transfer_s2mm_polling(UINTPTR *destinationBuffer, int bytes);
int mod_xdma_fifo_test_ocm_to_fifo_polling(uint32_t uiTEST_SEED);
int mod_xdma_fifo_test_sdram_to_fifo_polling(uint32_t uiTEST_SEED);


/* -------------------------------------------------------------------------------------
 * 										<PRINTS>
 * -------------------------------------------------------------------------------------
 */
void mod_xdma_fifo_print_regs(void);


#endif




