/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _BUR_1603808081_1_
#define _BUR_1603808081_1_

#include <bur/plctypes.h>

/* Datatypes and datatypes of function blocks */
typedef enum error_codes
{	KEIN_ERROR,
	MOTOR_LAEUFT_ZU_LANGE,
	KEINE_DRUCKLUFT
} error_codes;

typedef enum programm_states
{	EMER_HALT,
	INIT,
	STOP,
	GO_PRE_WORK,
	DETECT,
	WORK,
	GO_AFT_WORK,
	WAIT_TO_LET_GO,
	LET_GO,
	MANUAL,
	ERROR
} programm_states;

typedef enum koppel_state
{	RTR,
	RTT,
	BUSY
} koppel_state;






__asm__(".section \".plc\"");

/* Used IEC files */
__asm__(".ascii \"iecfile \\\"Logical/Global.typ\\\" scope \\\"global\\\"\\n\"");

/* Exported library functions and function blocks */

__asm__(".previous");


#endif /* _BUR_1603808081_1_ */

