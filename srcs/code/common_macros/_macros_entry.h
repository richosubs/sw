#ifndef __MACROS_ENTRY_H
#define __MACROS_ENTRY_H


#ifdef __cplusplus
extern "C" {
#endif


int gUserEntry;


/* Scanf USER entry stuff */
//#define DEBUG_PRINT_VERIFY_USER(STR)	do{ if((int)VERIFY_USER >= (int)gVerifyUserLevel) xil_printf("*USER::   "); xil_printf(STR); xil_printf("\n\r"); xil_printf("(0 - 1) > "); scanf("%d", &gUserEntry); xil_printf("%d \n\r", gUserEntry); } while( false )
//#define DEBUG_PRINT_VERIFY_USER(STR)    (xil_printf("%d %d %d \r\n", VERIFY_USER, VERIFY_NONE, gVerifyUserLevel))
#define DEBUG_PRINT_VERIFY_USER(STR)            do{ if(VERIFY_USER >= gVerifyUserLevel) { \
                                                                                            xil_printf("*USER::   "); \
                                                                                            xil_printf(STR); \
                                                                                            xil_printf("\n\r"); \
                                                                                            xil_printf("(0 - 1) > "); \
                                                                                            scanf("%d", &gUserEntry); \
                                                                                            xil_printf("%d \n\r", gUserEntry); } \
                                                                                    } while( false )

#define DEBUG_BREAK(...)        		do{ if(DEBUG_BREAK_SWITCH == DEBUG_BREAK_CHAR_ON) 	{ int c; do {DEBUG_PRINT_POUND(); xil_printf("*** "); xil_printf(__VA_ARGS__); DEBUG_PRINT_ALWAYS("-x to continue"); DEBUG_PRINT_POUND(); c=getchar();xil_printf("=%d", c); } while (c != 'x'); }} while(false)

#define DEBUG_PROGRAM_EXIT(...)       	do{ xil_printf("\n\r * Program Exiting * \n\r");  exit(0); } while ( false )


/* Return if on error, used by routines to stop and return an error */
#define DEBUG_RETURN_ON_ERROR(x, ...) 	do{ if((x) != 0) {return(x);}} while(false)



#endif // __MACROS_ENTRY_H
