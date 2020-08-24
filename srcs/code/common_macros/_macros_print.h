#ifndef __BT_COMMON_BUS_MACROS_H
#define __BT_COMMON_BUS_MACROS_H



#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "_macros_common.h"


#define LOG_HIDEBUG 0 // Lowest Level (Less supressed)
#define LOG_DEBUG   1 // General messages
#define LOG_PARM    2 // Entry / exit functions, with values passed and returned, detailed
#define LOG_ENTRY   3 // log entry - exit to functions
#define LOG_INFO    4 // Informational messages
#define LOG_WARNING 5 // recoverable problem - notification
#define LOG_ERROR   6 // error that can't be recovered from
#define LOG_SEVERE  7 // errors that require program exit
#define LOG_NONE    8 // Highed Level (More Suppressed)


#define VERIFY_USER   0 // User Entry
#define VERIFY_NONE   1 // User Entr


/* Set Levels.
 * (open) A GCC release build parameter needs to be reference to null out the print macros.
 */
#define gDebugLevel       LOG_SEVERE
#define gVerifyUserLevel  VERIFY_NONE


#define   DEBUG_BREAK_CHAR_ON      1
#define   DEBUG_BREAK_CHAR_OFF     0
#define   DEBUG_BREAK_SWITCH       DEBUG_BREAK_CHAR_ON


/* Note: This is a HACK of sorts with the macro's; should just have the defines, set in the
 * compiler; this allows for dynamic changing with defeats the purpose of having the macro's
 * compiled out.
 */
/* Sets the print debug level */
extern int giDebugLevel;
/* Value to switch back the print setting if adjust */
extern int giDebugLevelEntry;


/*
 * --------------------------------------------------------------------------------
 * --------------------------------------------------------------------------------
 *                            Print MACRO's
 * --------------------------------------------------------------------------------
 * --------------------------------------------------------------------------------
 */
// Quick Hack
#define __DEF_CBM_PP_DEBUG 1

#ifdef __DEF_CBM_PP_DEBUG
  // MicroBlaze processor target.  On hardare, using the MDM (MicroBlaze Debug Module)
	//#include "xil_printf.h"
	#include "xil_io.h"
	//extern uint32_t gDebugLevel;
	//extern uint32_t gVerifyUserLevel;


	#define gDEBUG_PRINT_COMMON_ARGS(...)		{do{ xil_printf("-%s-\t", __func__); xil_printf(__VA_ARGS__); xil_printf("\n\r");} while ( false );}

	#define DEBUG_PRINT_DASH(...)              	do{ if(LOG_ENTRY >= giDebugLevel)  {xil_printf("------------------------------------------------------------\n\r");} } while( false )
	#define DEBUG_PRINT_POUND(...)             	do{ if(LOG_ENTRY >= giDebugLevel)  {xil_printf("############################################################\n\r");} } while( false )
	#define DEBUG_PRINT_NEWLINE(...)           	do{ if(LOG_ENTRY >= giDebugLevel)  {xil_printf("\n\r");} } while( false )
	#define DEBUG_PRINT_ALWAYS(...)            	do{                                {xil_printf("      ALWAYS:: "); gDEBUG_PRINT_COMMON_ARGS(__VA_ARGS__)} } while( false )
	#define DEBUG_PRINT_ALWAYS_RAW(...)        	do{                                {gDEBUG_PRINT_COMMON_ARGS(__VA_ARGS__)} } while( false )


	#define DEBUG_PRINT_ALWAYS_STATUS(x, ...)  	do{ {if(x > 0) 	{xil_printf("FAILED"); \
														gDEBUG_PRINT_COMMON_ARGS(__VA_ARGS__)} else \
														{xil_printf("PASSED"); gDEBUG_PRINT_COMMON_ARGS(__VA_ARGS__)} \
													}} while(false)


	#define DEBUG_PRINT_LOG_HIDEBUG(...)   		do{ if(LOG_HIDEBUG >= giDebugLevel) \
													{xil_printf("     hidebug      "); \
													gDEBUG_PRINT_COMMON_ARGS(__VA_ARGS__)} } \
													while( false )


	#define DEBUG_PRINT_LOG_DEBUG(...)     		do{ if(LOG_DEBUG >= giDebugLevel) \
													{xil_printf("      debug       "); \
													gDEBUG_PRINT_COMMON_ARGS(__VA_ARGS__)} } \
													while( false )


	#define DEBUG_PRINT_LOG_DEBUG_REG(ADDR, DATA, STR) 		do{ if(LOG_DEBUG >= giDebugLevel)   {xil_printf("      debug       "); \
																								 xil_printf("Address = 0x%08x ", ADDR); \
																								 xil_printf("Data = 0x%08x \t", DATA); \
																								 xil_printf(STR); \
																								 xil_printf("\n\r"); \
																								} } while( false )

	#define DEBUG_PRINT_LOG_DEBUG_MASK(DATA, MASK, STR)		do{ if(LOG_DEBUG >= giDebugLevel)   {xil_printf("      debug       "); \
																								xil_printf("- Field = 0x%08x ", DATA & MASK); \
																								xil_printf("Mask = 0x%08x \t", MASK); \
																								xil_printf(STR); \
																								xil_printf("\n\r"); \
																								} } while( false )


	#define DEBUG_PRINT_LOG_PARM(...)      	do{ if(LOG_PARM >= giDebugLevel)    {xil_printf("      parm        "); \
												gDEBUG_PRINT_COMMON_ARGS(__VA_ARGS__)} } while( false )

	#define DEBUG_PRINT_LOG_ENTRY(...)     	do{ if(LOG_ENTRY >= giDebugLevel)   {xil_printf("      entry       "); \
												gDEBUG_PRINT_COMMON_ARGS(__VA_ARGS__)} } while( false )

	#define DEBUG_PRINT_LOG_INFO(...)      	do{ if(LOG_INFO >= giDebugLevel)    {xil_printf("      info        "); \
												gDEBUG_PRINT_COMMON_ARGS(__VA_ARGS__)} } while( false )

	#define DEBUG_PRINT_LOG_WARNING(...)   	do{ if(LOG_WARNING >= giDebugLevel) {xil_printf("* WARNING * "); \
												gDEBUG_PRINT_COMMON_ARGS(__VA_ARGS__)} } while( false )

	#define DEBUG_PRINT_LOG_PASSED(...)    	do{ if(LOG_ERROR >= giDebugLevel)   {xil_printf("* PASSED  * "); \
												gDEBUG_PRINT_COMMON_ARGS(__VA_ARGS__)} } while( false )

	#define DEBUG_PRINT_LOG_ERROR(...)     	do{ if(LOG_ERROR >= giDebugLevel)   {xil_printf("* ERROR   * "); \
												gDEBUG_PRINT_COMMON_ARGS(__VA_ARGS__)} } while( false )

	#define DEBUG_PRINT_LOG_SEVERE(...)    	do{ if(LOG_SEVERE >= giDebugLevel)  {xil_printf("* SEVERE  * "); \
												gDEBUG_PRINT_COMMON_ARGS(__VA_ARGS__)} } \
												while( false )

	#define DEBUG_PRINT_ENTER(...)  	  	do{ if(LOG_ENTRY >= giDebugLevel)   {xil_printf("#     ENTER     # "); \
												gDEBUG_PRINT_COMMON_ARGS(__VA_ARGS__)} } \
												while( false )

	#define DEBUG_PRINT_RETURN(...)	 		do{ if(LOG_ENTRY >= giDebugLevel)   {xil_printf("-    RETURN     - "); \
												gDEBUG_PRINT_COMMON_ARGS(__VA_ARGS__)} } \
												while( false )



/*
	#define DEBUG_PRINT_LOG_EQUAL(x,y, ...)  do{ if(LOG_ERROR >= giDebugLevel)  {if(x != y) { \
																					DEBUG_PRINT_LOG_ERROR(__VA_ARGS__); \
																					return(XST_FAILURE); } \
																				else {DEBUG_PRINT_LOG_PASSED(__VA_ARGS__); }}} while(false)
*/

	// # No Return
	#define DEBUG_PRINT_LOG_STATUS(x, ...)  do{ if(LOG_ERROR >= giDebugLevel) 	{if((x) != 0) { \
																					DEBUG_PRINT_LOG_ERROR(__VA_ARGS__); \
																				} \
																				else { \
																					DEBUG_PRINT_LOG_PASSED(__VA_ARGS__); \
																				}}} while(false)


	#define DEBUG_PRINT_LOG_STATUS_RETURN(x, ...)  do{ if(LOG_ERROR >= giDebugLevel) 	{if((x) != 0) { \
																							xil_printf("-   RETURN    - "); \
																							DEBUG_PRINT_LOG_ERROR(__VA_ARGS__); \
																						} \
																						else { \
																							xil_printf("-   RETURN    - "); \
																							DEBUG_PRINT_LOG_PASSED(__VA_ARGS__); \
																						}}} while(false)


	/* No Return, only print when there is an error.  Intent is too keep all the prints to a mininum,
	 * only point out issues for program debug.
	 */
	#define DEBUG_PRINT_LOG_STATUS_CHK_ERR(x, ...)  do{ if(LOG_ERROR >= giDebugLevel) 	{if((x) != 0) { \
																					DEBUG_PRINT_LOG_ERROR(__VA_ARGS__); \
																				}}} while(false)

	// # No Return
	#define DEBUG_PRINT_LOG_SET(x, ...)   	do{ if(LOG_ERROR >= giDebugLevel)   {if((x) == 0) { \
																					DEBUG_PRINT_LOG_ERROR(__VA_ARGS__);} \
																				else {DEBUG_PRINT_LOG_PASSED(__VA_ARGS__); }}} while(false)


	// # No Return
	#define DEBUG_PRINT_LOG_CLR(x, ...)  	do{ if(LOG_ERROR >= giDebugLevel)  {if((x) != 0) { \
																					DEBUG_PRINT_LOG_ERROR(__VA_ARGS__);} \
																				else {DEBUG_PRINT_LOG_PASSED(__VA_ARGS__); }}} while(false)


	// # Only print on failure.  *(out)= Status
	#define DEBUG_PRINT_NULL_PTR(x, out, ...)  	do{ if(LOG_ERROR >= giDebugLevel)   {if(!(x)) {DEBUG_PRINT_LOG_ERROR(__VA_ARGS__); \
																					(*(out)) = XST_FAILURE;} \
																				else {(*(out)) = XST_SUCCESS; } } } while(false)






	#define DEBUG_CHECK_IF_SET(result, x,...)		do{ if(LOG_NONE >= giDebugLevel) { \
														result = (x) != 1 ? XST_FAILURE : XST_SUCCESS; \
													}} while ( false )


	#define DEBUG_CHECK_IF_CLR(result, x,...)		do{ if(LOG_NONE >= giDebugLevel) { \
														result = (x) != 0 ? XST_FAILURE : XST_SUCCESS; \
													}} while ( false )


	#define DEBUG_COMPARE(result, x,y,...)	do{ if(LOG_NONE >= giDebugLevel) { \
												result = (x) > (y) ? XST_FAILURE : (x) == (y) ? XST_SUCCESS : -1; \
												}} while ( false )

	#define DEBUG_COMPARE_TOTAL(status, result, x,y,...)	do{ if(LOG_NONE >= giDebugLevel) { \
																result = (x) == (y) ? XST_SUCCESS : XST_FAILURE; \
																DEBUG_PRINT_LOG_STATUS(result, __VA_ARGS__); \
																if(result) {status+=1;} \
															}} while ( false )


#elif (__DEF_CBM_GCC_TERMINAL |  __DEFINE_MOD_LEVEL_HDL_SIM)



#else

#endif




/*
 * --------------------------------------------------------------------------------
 * --------------------------------------------------------------------------------
 *                                  INLINE MACRO's
 * --------------------------------------------------------------------------------
 * --------------------------------------------------------------------------------
 */

	uint32_t cPrintModuleInfoFromStruct(char *sModule, sFPGA_MODULE_REVISION_t sFPGA_MODULE_REVISION);
	void cPrintSetDebugLevelWarning(void);
	void cPrintRestoreDebugLevel(void);
	void cPrintSetDebugLevelShowAll(void);
	void cPrintSetDebugLevelProgramStart(int level);


#ifdef __cplusplus
}
#endif

#endif // __BT_COMMON_BUS_MACROS_H
