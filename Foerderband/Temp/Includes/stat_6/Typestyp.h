/* Durch Automation Studio generierte Headerdatei*/
/* Nicht bearbeiten! */

#ifndef _BUR_1611657704_7_
#define _BUR_1611657704_7_

#include <bur/plctypes.h>

/* Datentypen und Datentypen von Funktionsblöcken */
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

/* Verwendete IEC Dateien */
__asm__(".ascii \"iecfile \\\"Logical/stat_6/Types.typ\\\" scope \\\"local\\\"\\n\"");

/* Exportierte Bibliotheksfunktionen und Funktionsbausteine */

__asm__(".previous");


#endif /* _BUR_1611657704_7_ */

