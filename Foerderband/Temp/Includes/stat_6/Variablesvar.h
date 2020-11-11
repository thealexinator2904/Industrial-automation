/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _BUR_1605105052_8_
#define _BUR_1605105052_8_

#include <bur/plctypes.h>

/* Constants */
#ifdef _REPLACE_CONST
 #define timer_picture_time 1000U
#else
 _LOCAL_CONST unsigned short timer_picture_time;
#endif


/* Variables */
_BUR_LOCAL unsigned char shit_pic_cnt;
_BUR_LOCAL unsigned char nice_pic_cnt;
_BUR_LOCAL plcbit DI_Kamera_00;
_BUR_LOCAL plcbit DI_Kamera_02;
_BUR_LOCAL plcbit DI_Kamera_01;
_BUR_LOCAL plcbit DO_Kamera_Trigger;
_BUR_LOCAL struct TON timer_picture;





__asm__(".section \".plc\"");

/* Used IEC files */
__asm__(".ascii \"iecfile \\\"Logical/stat_6/Variables.var\\\" scope \\\"local\\\"\\n\"");
__asm__(".ascii \"iecfile \\\"Logical/Libraries/standard/standard.fun\\\" scope \\\"global\\\"\\n\"");

/* Exported library functions and function blocks */

__asm__(".previous");


#endif /* _BUR_1605105052_8_ */

