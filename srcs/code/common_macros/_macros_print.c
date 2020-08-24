// ------------------------------------------------------------------------
// File:    bt_common_bus_macros.c
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
// Note:    
// ------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#include "svdpi.h"
//#include "svdpi_src.h"

#include "_macros_print.h"
#include "_macros_common.h"

int giDebugLevel=0;
/* Value to switch back the print setting if adjust */
int giDebugLevelEntry=0;

uint32_t cPrintModuleInfoFromStruct(char *sModule, sFPGA_MODULE_REVISION_t sFPGA_MODULE_REVISION) {
  uint32_t uiMajor, uiMinor, uiRev;

  
  uiMajor = (sFPGA_MODULE_REVISION.fullrev >> 16) & 0xFF;
  uiMinor = (sFPGA_MODULE_REVISION.fullrev >> 8) & 0xFF;
  uiRev = (sFPGA_MODULE_REVISION.fullrev >> 0) & 0xFF;
  
  printf("%s", defCHAR_LINE_DASHES);
  printf("%s \n", sModule);
  printf("FPGA REV \t= %d.%d.%d \n", uiMajor, uiMinor, uiRev);
  printf("Module ID \t= 0x%x\n",  sFPGA_MODULE_REVISION.id);
  printf("%s", defCHAR_LINE_DASHES);

  return(0);
}


/* Need to make into a macro; compile out for release builds */
void cPrintSetDebugLevelProgramStart(int level) {
        giDebugLevel= level;
        giDebugLevelEntry= level;
}

/* Need to make into a macro; compile out for release builds */
void cPrintSetDebugLevelWarning(void) {
        giDebugLevel= LOG_WARNING;
}


void cPrintRestoreDebugLevel(void) {
        giDebugLevel= giDebugLevelEntry;
}

void cPrintSetDebugLevelShowAll(void) {
        giDebugLevel= LOG_HIDEBUG;
}
