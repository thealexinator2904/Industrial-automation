
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
	DI_Ident=0;

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

}
