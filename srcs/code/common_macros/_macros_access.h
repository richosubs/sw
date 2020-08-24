#ifndef __MACROS_ACCESS_H
#define __MACROS_ACCESS_H


#ifdef __cplusplus
extern "C" {
#endif



//#define __DEF_CBM_GCC_TERMINAL     	1
#define __DEF_CBM_MICROBLAZE_BUILD 	2


#ifdef	__DEF_CBM_GCC_TERMINAL
	#define fpgaWriteWordC_D32(iAddr, iData) {printf("- FPGA Write \r\n");}
	#define fpgaReadWordC_D32(iAddr, iData) {printf("- FPGA Read  \r\n");}
#elif __DEF_CBM_MICROBLAZE_BUILD
	#define fpgaWriteWordC_D32(iAddr, iData) ((*(uint32_t *)(iAddr))= iData)
	#define fpgaReadWordC_D32(iAddr, oData)  (*oData= *((uint32_t *)(iAddr)))
#endif



#endif // __MACROS_ACCESS_H
