
#ifndef __UTILS_COMPARE_H_
#define __UTILS_COMPARE_H_


//extern inline void utilsCompareBuffersX32(uint32_t *bufferA, uint32_t *bufferB, uint32_t length, int *lStatus) __attribute__((always_inline));

inline void utilsCompareBuffersX32(uint32_t *bufferA, uint32_t *bufferB, uint32_t length, int *lStatus);
inline void utilsCompareBufferWithSeedX32(uint32_t *buffer, uint32_t value, uint32_t length, uint32_t *lStatus);

inline void utilsFillBufferConstantX32(uint32_t *buffer, uint32_t value, uint32_t length);
inline void utilsFillBufferIncrementWithSeedX32(uint32_t *buffer, uint32_t value, uint32_t length);


#endif
