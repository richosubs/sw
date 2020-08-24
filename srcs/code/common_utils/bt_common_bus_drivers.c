// ------------------------------------------------------------------------
// File:    bt_common_bus_drivers.c
//
// Summary: Layer between the "C" code and the FPGA.
//
//          1. Common task calls to call FPGA Verilog BFM.
//
//          2. Supports FPS BFM
//               - Path: mod_lib_shared/models/fps_lbus/bt_fps_lbus/
//
//          3. Supports AMCC BFM
//               - Path: mod_lib_shared/models/amcc_bus/bt_amcc_bus/
//
//
// Note:    In 
// ------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#include "svdpi.h"
//#include "svdpi_src.h"

#include "bt_common_bus_drivers.h" 

#include "_macros_print.h"
#include "dpi_common.h"




  // ------------------------------------------------------------------------
  //                          <1::C Calls - Reuse>
  // ------------------------------------------------------------------------
UINT32 cBtWriteToFpga(UINT32 iAddr, UINT32 iData) {
  btWriteToFpgaA32D32(iAddr, iData);
  return(0);
}


UINT32 cBtReadFromFpga(UINT32 iAddr, UINT32 *oData) {
  btReadFromFpgaA32D32(iAddr, oData);
  return(0);
}

// (open) : need to complete verify
UINT32 cBtWriteReadVerify(UINT32 iAddr, UINT32 iExpected, UINT32 *oData, UINT32 *oError) {

  btReadFromFpgaA32D32(iAddr, oData);
 
  return(0);
}



  // ------------------------------------------------------------------------
  //                          <2::C Calls - Reuse>
  // ------------------------------------------------------------------------
UINT32 cBtSetBit(UINT32 uiAddr, UINT8 uiBit) {
  UINT32 uiData, uiSet;

  btReadFromFpgaA32D32(uiAddr, &uiData);
  
  uiSet = (0x00000001 << uiBit);
  uiData = uiSet | uiData;
  btWriteToFpgaA32D32(uiAddr, uiData); 

  return(0);
}


UINT32 cBtClrBit(UINT32 uiAddr, UINT8 uiBit) {
  UINT32 uiData, uiSet;

  btReadFromFpgaA32D32(uiAddr, &uiData);
  
  uiSet = ~(1 << uiBit);
  uiData = uiSet & uiData;
  btWriteToFpgaA32D32(uiAddr, uiData); 

  return(0);
}


UINT32 cBtSetMask(UINT32 uiAddr, UINT32 uiMask, UINT8 uiBit) {
  UINT32 uiData, uiSet;

  btReadFromFpgaA32D32(uiAddr, &uiData);
  
  uiSet = (uiMask << uiBit);
  uiData = uiSet | uiData;
  btWriteToFpgaA32D32(uiAddr, uiData); 

  return(0);
}


UINT32 cBtClrMask(UINT32 uiAddr, UINT32 uiMask, UINT8 uiBit) {
  UINT32 uiData, uiSet;

  btReadFromFpgaA32D32(uiAddr, &uiData);
  
  uiSet= ~(uiMask << uiBit);
  uiData = uiSet & uiData;
  btWriteToFpgaA32D32(uiAddr, uiData); 

  return(0);
}


  // ------------------------------------------------------------------------
  //                          <3::C Calls - Reuse>
  // ------------------------------------------------------------------------
BOOL cBtIsBitSet(UINT32 uiAddr, UINT8 uiBit) {
  UINT32 uiData, uiSet;

  btReadFromFpgaA32D32(uiAddr, &uiData);
  
  uiSet = (0x00000001 << uiBit);
  uiData = uiSet & uiData;

  if(uiData == uiSet)
    return(true);
  else
    return(false);
}


BOOL cBtIsBitClr(UINT32 uiAddr, UINT8 uiBit) {
  UINT32 uiData, uiSet;

  btReadFromFpgaA32D32(uiAddr, &uiData);
  
  //DEBUG_PRINT_LOG_HIDEBUG("Address %08x Data %08x Bit %d %s", uiAddr, uiData, uiBit, __func__);

  uiSet = (0x00000001 << uiBit);
  uiData = uiSet & uiData;
  
  if(uiData == 0)
    return(true);
  else
    return(false);
}


BOOL cBtIsMaskSet(UINT32 uiAddr, UINT32 uiMask, UINT8 uiBit) {
  UINT32 uiData, uiSet;

  btReadFromFpgaA32D32(uiAddr, &uiData);
  
  uiSet = (uiMask << uiBit);
  uiData = uiSet & uiData;
  
  if(uiData == uiSet)
    return(true);
  else
    return(false);

  return(0);
}


BOOL cBtIsMaskClr(UINT32 uiAddr, UINT32 uiMask, UINT8 uiBit) {
  UINT32 uiData, uiSet;

  btReadFromFpgaA32D32(uiAddr, &uiData);
  
  uiSet = (uiMask << uiBit);
  uiData = uiSet & uiData;
  
  if(uiData == 0)
    return(true);
  else
    return(false);

  return(0);
}


BOOL cBtIsMaskNonZero(UINT32 uiAddr, UINT32 uiMask, UINT8 uiBit) {
  UINT32 uiData, uiSet;

  btReadFromFpgaA32D32(uiAddr, &uiData);
  
  uiSet = (uiMask << uiBit);
  uiData = uiSet & uiData;
  
  if(uiData != 0)
    return(true);
  else
    return(false);

  return(0);
}








// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
//                 'C' to SystemVerilog interfaces.
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
//                                <Writes>
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------

/*
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
*/



// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
//                            <Write-Read Verify>
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------


/* In order to support DPI (HDL verification), return value via oError; always return
 * zero from call else HDL-verifcation will crash; I don't know a way around that.
 */
UINT32 btWriteReadVerifyA32D32(UINT32 iAddr, UINT32 iExpected, UINT32 *oError) {
  UINT32 rData;

  btWriteToFpgaA32D32(iAddr, iExpected);
  btReadFromFpgaA32D32(iAddr, &rData);

  if(iExpected == rData)
    *oError = 0; // Pass
  else
    *oError = 1; // Fail

  return(0);
}


UINT32 cbtWriteReadVerifyA32D32(UINT32 iAddr, UINT32 iExpected, UINT32 *oActual) {
  btWriteToFpgaA32D32(iAddr, iExpected);
  btReadFromFpgaA32D32(iAddr, oActual);

  if(iExpected == *oActual)
	  return(0);
  else
	  return(1);
}



// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
//                            <Read-Verify>
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------


UINT32 btReadVerifyA32D32(UINT32 iAddr, UINT32 iExpected, UINT32 *oError) {
  //char cBuff[defLengthDebugStr];
  UINT32 rData;

  btReadFromFpgaA32D32(iAddr, &rData);

  //sprintf(cBuff, "bt_common_bus_driver:btReadVerifyA32D32 %x %x \n", iExpected, rData);
  //dpiCommonGlbPrint(cBuff);

  if(iExpected == rData)
    *oError = 0; // Pass
  else
    *oError = 1; // Fail

  return(0);
}



UINT32 cbtReadVerifyA32D32(UINT32 iAddr, UINT32 iExpected, UINT32 *oActual) {
  btReadFromFpgaA32D32(iAddr, oActual);

  if(iExpected == *oActual)
	  return(0);
  else
	  return(1);

  return(0);
}
















