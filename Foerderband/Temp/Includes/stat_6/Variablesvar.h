/* Durch Automation Studio generierte Headerdatei*/
/* Nicht bearbeiten! */

#ifndef _BUR_1611659299_1_
#define _BUR_1611659299_1_

#include <bur/plctypes.h>

/* Constants */
#ifdef _REPLACE_CONST
 #define timer_picture_time 100U
#else
 _LOCAL_CONST unsigned short timer_picture_time;
#endif


/* Variablen */
_BUR_LOCAL unsigned char state;
_BUR_LOCAL plcbit new_pic;
_BUR_LOCAL unsigned char shit_pic_cnt;
_BUR_LOCAL unsigned char nice_pic_cnt;
_BUR_LOCAL plcbit DI_Kamera_00;
_BUR_LOCAL plcbit DI_Kamera_02;
_BUR_LOCAL plcbit DI_Kamera_01;
_BUR_LOCAL plcbit DO_Kamera_Trigger;
_BUR_LOCAL struct TON timer_picture;





__asm__(".section \".plc\"");

/* Verwendete IEC Dateien */
__asm__(".ascii \"iecfile \\\"Logical/stat_6/Variables.var\\\" scope \\\"local\\\"\\n\"");
__asm__(".ascii \"iecfile \\\"Logical/Libraries/standard/standard.fun\\\" scope \\\"global\\\"\\n\"");

/* Exportierte Bibliotheksfunktionen und Funktionsbausteine */

__asm__(".previous");


#endif /* _BUR_1611659299_1_ */

