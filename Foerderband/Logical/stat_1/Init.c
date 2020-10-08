
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	DI_Hubzylinder_oben	=0;
	DI_Hubzylinder_unten=0;
	DI_untere_Klinge=0;
	DI_obere_Klinge=0;
	DI_Mag_leer	=0;
	DI_Palette=0;
	DI_Frontschale=0;

	DO_Hubzylinder_auf=0;
	DO_Hubzylinder_ab=0;
	DO_Vereinzler_close=0;
	DO_Vereinzler_open=0;
	DO_Zylinderklemmung=0;

}
