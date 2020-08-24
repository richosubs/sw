#ifndef __BT_COMMON_BUS_DRIVERS_H 
#define __BT_COMMON_BUS_DRIVERS_H 


#ifdef __cplusplus
extern "C" {
#endif


#include "_macros_print.h"  
#include "_macros_access.h"

  // ------------------------------------------------------------------------
  //                          <1::C Calls - Reuse>
  // ------------------------------------------------------------------------
  UINT32 cBtWriteToFpga(UINT32 iAddr, UINT32 iData);
  UINT32 cBtReadFromFpga(UINT32 iAddr, UINT32 *oData);
  UINT32 cBtWriteReadVerify(UINT32 iAddr, UINT32 iExpected, UINT32 *oData, UINT32 *oError);
  //
  // ------------------------------------------------------------------------
  //                          <2::C Calls - Reuse>
  // ------------------------------------------------------------------------
  UINT32 cBtSetBit(UINT32 uiAddr, UINT8 uiBit);
  UINT32 cBtClrBit(UINT32 uiAddr, UINT8 uiBit);
  UINT32 cBtSetMask(UINT32 uiAddr, UINT32 uiMask, UINT8 uiBit);
  UINT32 cBtClrMask(UINT32 uiAddr, UINT32 uiMask, UINT8 uiBit);
  //  
  // ------------------------------------------------------------------------
  //                          <3::C Calls - Reuse>
  // ------------------------------------------------------------------------
  BOOL cBtIsBitSet(UINT32 uiAddr, UINT8 uiBit);
  BOOL cBtIsBitClr(UINT32 uiAddr, UINT8 uiBit);
  BOOL cBtIsMaskSet(UINT32 uiAddr, UINT32 uiMask, UINT8 uiBit);
  BOOL cBtIsMaskClr(UINT32 uiAddr, UINT32 uiMask, UINT8 uiBit);
  BOOL cBtIsMaskNonZero(UINT32 uiAddr, UINT32 uiMask, UINT8 uiBit);


// ------------------------------------------------------------------------
// "C" to SystemVerilog
// ------------------------------------------------------------------------
static inline UINT32 btWriteToFpga(UINT32 iAddr, UINT32 iData);












static inline UINT32 btWriteToFpgaA32D32(UINT32 iAddr, UINT32 iData);

static inline UINT32 btReadFromFpga(UINT32 iAddr, UINT32 *oData);
static inline UINT32 btReadFromFpgaA32D32(UINT32 iAddr, UINT32 *oData);


UINT32 btWriteReadVerifyA32D32(UINT32 iAddr, UINT32 iExpected, UINT32 *oError);
UINT32 cbtWriteReadVerifyA32D32(UINT32 iAddr, UINT32 iExpected, UINT32 *oActual);

UINT32 btReadVerifyA32D32(UINT32 iAddr, UINT32 iExpected, UINT32 *oError);
UINT32 cbtReadVerifyA32D32(UINT32 iAddr, UINT32 iExpected, UINT32 *oActual);






// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
//                                <Writes>
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------


static inline UINT32 btWriteToFpga(UINT32 iAddr, UINT32 iData) {
  fpgaWriteWordC_D32(iAddr, iData);
  return(0);
}


static inline UINT32 btWriteToFpgaA32D32(UINT32 iAddr, UINT32 iData) {
  fpgaWriteWordC_D32(iAddr, iData);
  return(0);
}




// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
//                              <Reads>
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------

static inline UINT32 btReadFromFpga(UINT32 iAddr, UINT32 *oData) {
  fpgaReadWordC_D32(iAddr, oData);
  return(0);
}


static inline UINT32 btReadFromFpgaA32D32(UINT32 iAddr, UINT32 *oData) {
  fpgaReadWordC_D32(iAddr, oData);
  return(0);
}






#ifdef __cplusplus
}
#endif

#endif // __BT_COMMON_BUS_DRIVERS_H

