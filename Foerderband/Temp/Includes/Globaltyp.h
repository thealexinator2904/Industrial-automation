/* Durch Automation Studio generierte Headerdatei*/
/* Nicht bearbeiten! */

#ifndef _BUR_1611657704_1_
#define _BUR_1611657704_1_

#include <bur/plctypes.h>

/* Datentypen und Datentypen von Funktionsblöcken */
typedef enum error_codes
{	KEIN_ERROR,
	MOTOR_LAEUFT_ZU_LANGE,
	KEINE_DRUCKLUFT,
	ERROR_ANTRIEB
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

/* Verwendete IEC Dateien */
__asm__(".ascii \"iecfile \\\"Logical/Global.typ\\\" scope \\\"global\\\"\\n\"");

/* Exportierte Bibliotheksfunktionen und Funktionsbausteine */

__asm__(".previous");


#endif /* _BUR_1611657704_1_ */

