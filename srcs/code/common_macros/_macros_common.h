#ifndef __MACROS_COMMON_H
#define __MACROS_COMMON_H


#ifdef __cplusplus
extern "C" {
#endif


void extern exit(int x);







//*((uint32_t *)(uiPCI_BAR2_BASE_ADDRESS + iAddr));

#define defCHAR_LINE_DASHES "-----------------------------------------------------------"


#define __BIT_CHECK(iDATA, iBIT)  ((iDATA >> iBIT) & 0x000000001)

#define __BIT_MASK_AND(iDATA, iBIT, iMASK)  ((iDATA >> iBIT) & iMASK)
#define __BIT_MASK_OR(iDATA, iBIT, iMASK)  ((iDATA >> iBIT) | iMASK)


#define FPGASWAP32(x) \
    (((x >>24) & 0x000000ff) | \
     ((x >> 8) & 0x0000ff00) | \
     ((x << 8) & 0x00ff0000) | \
     ((x <<24) & 0xff000000) )

#define U8  unsigned char
#define U16 unsigned short
#define U32 unsigned int
#define U64 unsigned long long
#define S16 signed short

#define UINT64 long int

  // Set to values in stdint.h
#define UINT32 uint32_t
#define UINT16 uint16_t
#define UINT8  uint8_t

#define BOOL int

#ifndef TRUE
	#define TRUE  1
#endif

#ifndef FALSE
	#define FALSE 0
#endif


#define BUS_WIDTH_BYTES  8

#define DEF_PASS  0
#define DEF_FAIL  1

#define defPASS  DEF_PASS
#define defFAIL  DEF_FAIL


#define defLengthDebugStr 256


typedef struct {
  UINT8 cm;
  UINT8 major;
  UINT8 minor;
  UINT8 rev;
} sREVISION;


typedef struct {
  unsigned int id;
  unsigned int fullrev;
  unsigned int major;
  unsigned int minor;
  unsigned int rev;
} sFPGA_MODULE_REVISION_t;



#define DEF_SIZEOF_ARRAY(x)  (sizeof(x) / sizeof((x[0]))

#endif // __MACROS_COMMON_H
