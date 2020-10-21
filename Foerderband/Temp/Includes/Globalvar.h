/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _BUR_1603281521_1_
#define _BUR_1603281521_1_

#include <bur/plctypes.h>

/* Constants */
#ifdef _REPLACE_CONST
 #define timer_2s_time 2000
 #define timer_error_time 12000
 #define timer_error_stopper_time 200
#else
 _GLOBAL_CONST signed short timer_2s_time;
 _GLOBAL_CONST signed short timer_error_time;
 _GLOBAL_CONST signed short timer_error_stopper_time;
#endif


/* Variables */
_GLOBAL plcbit DO_Greifer_close;
_GLOBAL plcbit DO_Greifer_open;
_GLOBAL plcbit DO_phi_180;
_GLOBAL plcbit DO_phi_0;
_GLOBAL plcbit DI_werkstueck;
_GLOBAL plcbit DI_Stau;
_GLOBAL plcbit DI_phi_4;
_GLOBAL plcbit DI_Greifer_closed;
_GLOBAL plcbit DI_Greifer_open;
_GLOBAL plcbit DI_phi_180;
_GLOBAL plcbit DI_phi_0;
_GLOBAL plcbit DO_Hubzylinder_auf_stat3;
_GLOBAL plcbit DO_Hubzylinder_ab_stat3;
_GLOBAL plcbit DI_Frontschale_vorhanden;
_GLOBAL plcbit DI_Hubzylinder_oben_stat3;
_GLOBAL plcbit DI_Hubzylinder_unten_stat3;
_GLOBAL plcbit DO_Bohrer2;
_GLOBAL plcbit DO_Bohrer1;
_GLOBAL plcbit DO_Z_axis_Klemmung;
_GLOBAL plcbit DO_Z_axis_nach_unten;
_GLOBAL plcbit DO_Z_axis_nach_oben;
_GLOBAL plcbit DO_X_axis_nach_rechts;
_GLOBAL plcbit DO_X_axis_nach_links;
_GLOBAL plcbit DI_Z_axis_unten;
_GLOBAL plcbit DI_Deckel_bereits_vorh;
_GLOBAL plcbit DI_Z_axis_oben;
_GLOBAL plcbit DI_Frontschale_vorh;
_GLOBAL plcbit DI_Frontschale_korr;
_GLOBAL plcbit DI_X_axis_recht;
_GLOBAL plcbit DI_X_axis_links;
_GLOBAL plcbit DO_Zylinderklemmung;
_GLOBAL plcbit DO_Vereinzler_open;
_GLOBAL plcbit DO_Vereinzler_close;
_GLOBAL plcbit DO_Hubzylinder_ab;
_GLOBAL plcbit DO_Hubzylinder_auf;
_GLOBAL plcbit DI_Frontschale;
_GLOBAL plcbit DI_Palette;
_GLOBAL plcbit DI_Mag_leer;
_GLOBAL plcbit DI_obere_Klinge;
_GLOBAL plcbit DI_untere_Klinge;
_GLOBAL plcbit DI_Hubzylinder_unten;
_GLOBAL plcbit DI_Hubzylinder_oben;
_GLOBAL struct TON timer_blink;
_GLOBAL struct TON timer_blink2;
_GLOBAL struct TON timer_error;
_GLOBAL struct TON timer_error_stopper;
_GLOBAL struct TON timer_2s;
_GLOBAL plcbit error_flag;
_GLOBAL plcbit work_now;
_GLOBAL plcbit work_done;
_GLOBAL unsigned char foerderband_state;
_GLOBAL unsigned char work_state;
_GLOBAL unsigned char auto_mode_glob;
_GLOBAL plcbit manual_work_mode_glob;
_GLOBAL unsigned long RFID_Reader;
_GLOBAL signed short AI_Potentiometer_2;
_GLOBAL signed short AI_Potentiometer_1;
_GLOBAL plcbit DO_Q2;
_GLOBAL plcbit DO_Q1;
_GLOBAL plcbit DO_weiss;
_GLOBAL plcbit DO_gruen;
_GLOBAL plcbit DO_Koppel_rechts;
_GLOBAL plcbit DO_Koppel_links;
_GLOBAL plcbit DO_Stopper;
_GLOBAL plcbit DO_schleichgang;
_GLOBAL plcbit DO_Antrieb_links;
_GLOBAL plcbit DO_Antrieb_rechts;
_GLOBAL plcbit DI_Ident_4;
_GLOBAL plcbit DI_Ident_3;
_GLOBAL plcbit DI_Ident_2;
_GLOBAL plcbit DI_Ident_1;
_GLOBAL plcbit DI_Wahl;
_GLOBAL plcbit DI_RESET;
_GLOBAL plcbit DI_Stop;
_GLOBAL plcbit DI_Start;
_GLOBAL plcbit DI_Drehgeber_2;
_GLOBAL plcbit DI_Drehgeber_1;
_GLOBAL plcbit DI_NOTAUS;
_GLOBAL plcbit DI_Stopper;
_GLOBAL plcbit DI_Koppel_links;
_GLOBAL plcbit DI_Koppel_rechts;
_GLOBAL plcbit DI_Band_rechts;
_GLOBAL plcbit DI_Band_links;





__asm__(".section \".plc\"");

/* Used IEC files */
__asm__(".ascii \"iecfile \\\"Logical/Global.var\\\" scope \\\"global\\\"\\n\"");
__asm__(".ascii \"iecfile \\\"Logical/Libraries/standard/standard.fun\\\" scope \\\"global\\\"\\n\"");

/* Exported library functions and function blocks */

__asm__(".previous");


#endif /* _BUR_1603281521_1_ */

