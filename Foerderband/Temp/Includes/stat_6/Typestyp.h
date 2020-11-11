/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _BUR_1605105052_7_
#define _BUR_1605105052_7_

#include <bur/plctypes.h>

/* Datatypes and datatypes of function blocks */
typedef enum states_stat6
{	PROCESS_PIC,
	WORK_DONE,
	TAKE_PIC,
	ERROR_STAT6,
	WAIT
} states_stat6;

typedef enum error_codes_stat6
{	NO_ERROR,
	SHIT_PIC
} error_codes_stat6;






__asm__(".section \".plc\"");

/* Used IEC files */
__asm__(".ascii \"iecfile \\\"Logical/stat_6/Types.typ\\\" scope \\\"local\\\"\\n\"");

/* Exported library functions and function blocks */

__asm__(".previous");


#endif /* _BUR_1605105052_7_ */

