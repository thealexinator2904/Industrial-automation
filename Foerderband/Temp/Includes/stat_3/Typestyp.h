/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _BUR_1603808081_7_
#define _BUR_1603808081_7_

#include <bur/plctypes.h>

/* Datatypes and datatypes of function blocks */
typedef enum hubzylinderstates
{	UP,
	DWN,
	DONT_MOVE
} hubzylinderstates;

typedef enum states
{	WAIT,
	SENKEN,
	HALTEN,
	HEBEN,
	FERTIG,
	ERROR_STAT3
} states;

typedef enum error_codes_stat3
{	KEIN_ERROR_STAT3,
	KEINE_FRONTSCHALE_STAT3
} error_codes_stat3;






__asm__(".section \".plc\"");

/* Used IEC files */
__asm__(".ascii \"iecfile \\\"Logical/stat_3/Types.typ\\\" scope \\\"local\\\"\\n\"");

/* Exported library functions and function blocks */

__asm__(".previous");


#endif /* _BUR_1603808081_7_ */

