// - ------------------------------------------------------------------
//                              - 'C' Code -
// - ------------------------------------------------------------------

#ifdef __DPI_COMMON_H
#else
#define __DPI_COMMON_H 1


#ifdef __cplusplus
extern "C" {
#endif



#include <stdbool.h>
#include "_macros_print.h"



 
  // Loop waits
  BOOL dpiCommonWaitForTrue(BOOL (*f)(void), uint32_t iLoops);
  BOOL dpiCommonWaitForFalse(BOOL (*f)(void), uint32_t iLoops);
  //
  BOOL dpiCommonWaitForTrueWithSleep(BOOL (*f)(void), uint32_t iLoops, uint32_t iMilliSecSleep);
  BOOL dpiCommonWaitForFalseWithSleep(BOOL (*f)(void), uint32_t iLoops, uint32_t iMilliSecSleep);
  //
  BOOL dpiCommonWaitForTrue_uint32_t(BOOL (*f)(uint32_t), uint32_t a, uint32_t iLoops);
  BOOL dpiCommonWaitForFalse_uint32_t(BOOL (*f)(uint32_t), uint32_t a, uint32_t iLoops);
  //
  BOOL dpiCommonWaitForTrue_uint32_t_UINT8(BOOL (*f)(uint32_t, UINT8), uint32_t a, UINT8 b, uint32_t iLoops);
  BOOL dpiCommonWaitForFalse_uint32_t_UINT8(BOOL (*f)(uint32_t, UINT8), uint32_t a, UINT8 b, uint32_t iLoops);
  //
  BOOL dpiCommonWaitForTrue_uint32_t_uint32_t(BOOL (*f)(uint32_t, uint32_t), uint32_t a, uint32_t b, uint32_t iLoops);
  BOOL dpiCommonWaitForFalse_uint32_t_uint32_t(BOOL (*f)(uint32_t, uint32_t), uint32_t a, uint32_t b, uint32_t iLoops);
  //
  BOOL dpiCommonWaitForTrue_uint32_t_uint32_t_UINT8(BOOL (*f)(uint32_t, uint32_t, UINT8), uint32_t a, uint32_t b, UINT8 c, uint32_t iLoops);
  BOOL dpiCommonWaitForFalse_uint32_t_uint32_t_UINT8s(BOOL (*f)(uint32_t, uint32_t, UINT8), uint32_t a, uint32_t b, UINT8 c, uint32_t iLoops);

  

#ifdef __cplusplus
}
#endif

#endif // __DPI_COMMON_H
