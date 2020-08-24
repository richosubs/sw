#include <stdio.h>
#include <stdlib.h> // Std C functions, e.g. exit()
#include <math.h>   // libm header: sqrt(), cos(), etc

//#include "platform.h"

#include "xstatus.h"
#include "xil_io.h"

#include "_utils_compare.h"

#include "_macros_include_all.h"




void utilsCompareBuffersX32(uint32_t *bufferA, uint32_t *bufferB, uint32_t length, int *lStatus) {
	int i;

	for(i=0; i < length; i++) {

		if(0) {
			DEBUG_PRINT_ALWAYS("Data Mismatch %d 0x%08x 0x%08x", i, bufferA, bufferB);
			DEBUG_PRINT_ALWAYS("Data Mismatch %d 0x%08x 0x%08x", i, *bufferA, *bufferB);
		}

		if(*bufferA != *bufferB) {
			DEBUG_PRINT_LOG_ERROR("Data Mismatch %d 0x%08x 0x%08x", i, *bufferA, *bufferB);
			bufferA++;
			bufferB++;
			(*lStatus)++;
		}
	}
}



void utilsCompareBufferWithSeedX32(uint32_t *buffer, uint32_t value, uint32_t length, uint32_t *lStatus) {
	int i;

	//DEBUG_PRINT_ALWAYS("Address= 0x%08x", buffer);

	for(i=0; i < length; i++) {

		if(*buffer != value) {
			DEBUG_PRINT_LOG_ERROR("Data Mismatch Address= 0x%08x Actual= 0x%08x Expected= 0x%08x %d", buffer, *buffer, value, *lStatus);
			buffer++;
			value++;
			(*lStatus)++;
		}
	}
}




void utilsFillBufferConstantX32(uint32_t *buffer, uint32_t value, uint32_t length) {
	int i;

	for(i=0; i < length; i++) {
		*buffer= value;
		buffer++;
	}
}



void utilsFillBufferIncrementWithSeedX32(uint32_t *buffer, uint32_t value, uint32_t length) {
	int i;

	for(i=0; i < length; i++) {
		*buffer= value;
		buffer++;
		value++;
	}
}
