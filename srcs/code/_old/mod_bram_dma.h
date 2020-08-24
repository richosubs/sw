
#ifndef __MOD_BRAM_DMA_H_
#define __MOD_BRAM_DMA_H_


#include "xaxicdma.h" // Device driver API for AXI DMA



int mod_bram_dma_init();


/* Test */
int mod_bram_dma_test();
int mod_bram_dma_test_polling(uint32_t uiTests);
int mod_bram_dma_test_interrupt();


/* Polling */
int mod_bram_dma_transfer_polling(UINTPTR *ptrFrom, UINTPTR *ptrTo, int bytes);
int mod_bram_dma_test_ocm_to_ocm_test_polling();
int mod_bram_dma_test_ocm_to_bram_test_polling();
int mod_bram_dma_test_bram_to_bram_test_polling();
int mod_bram_dma_test_bram_to_sdram_test_polling();
int mod_bram_dma_test_sdram_to_bram_test_polling();


/* Interrupt */
int mod_bram_dma_transfer_interrupt(UINTPTR *ptrFrom, UINTPTR *ptrTo, int bytes);
int mod_bram_dma_test_ocm_to_ocm_test_interrupt();

/* BRAM ZYNQ Direct Access */
int mod_bram_dma_zynq_access_test();
int mod_bram_dma_zynq_mem_clear();


/* Prints */
void mod_bram_dma_print_regs(void);
void mod_bram_dma_print_buffers(void);

#endif

