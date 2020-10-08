
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	DI_Band_links=0;
	DI_Band_rechts=0;
	DI_Koppel_rechts=0;
	DI_Koppel_links=0;
	DI_Stopper=0;
	DI_NOTAUS=0;
	DI_Drehgeber_1=0;
	DI_Drehgeber_2=0;
	DI_Start=0;
	DI_Stop=0;
	DI_RESET=0;
	DI_Wahl=0;
	DI_Ident_1 = DI_Ident_2 = DI_Ident_3 = DI_Ident_4=0;

	DO_Antrieb_rechts=0;
	DO_Antrieb_links=0;
	DO_schleichgang=0;
	DO_Stopper=0;
	DO_Koppel_links=0;
	DO_Koppel_rechts=0;
	DO_gruen=0;
	DO_weiss=0;
	DO_Q1=0;
	DO_Q2=0;

	AI_Potentiometer_1=0;
	AI_Potentiometer_2=0;
	RFID_Reader=0;

	timer_5s.PT = 6000;
	timer_2s.PT = 2000;
	timer_blink.PT = 750;
}
