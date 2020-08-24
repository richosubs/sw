
#ifndef __MOD_FIFO_DMA_H_
#define __MOD_FIFO_DMA_H_


#include "xaxidma.h" // Device driver API for AXI DMA



int mod_fifo_dma_init();


/* -------------------------------------------------------------------------------------
 * 									<TESTS>
 * -------------------------------------------------------------------------------------
 */
int mod_fifo_dma_test(uint32_t uiTEST_SEED);
int mod_fifo_dma_test_polling(uint32_t uiTEST_SEED);


/* -------------------------------------------------------------------------------------
 * 								     <POLLING>
 * -------------------------------------------------------------------------------------
 */
int mod_fifo_dma_test_transfer_mm2s_polling(UINTPTR *sourceBuffer, int bytes);
int mod_fifo_dma_test_transfer_s2mm_polling(UINTPTR *destinationBuffer, int bytes);
int mod_fifo_dma_test_ocm_to_fifo_polling(uint32_t uiTEST_SEED);
int mod_fifo_dma_test_sdram_to_fifo_polling(uint32_t uiTEST_SEED);


/* -------------------------------------------------------------------------------------
 * 										<PRINTS>
 * -------------------------------------------------------------------------------------
 */
void mod_fifo_dma_print_regs(void);


#endif




