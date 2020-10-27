
#include <bur/plctypes.h>

#define true 1
#define false 0

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

void _CYCLIC ProgramCyclic(void)
{	
	static enum error_codes error_code = KEIN_ERROR;
	
	//Stopper ist nicht im gewünschten Zustand / Keine Druckluft vorhanden
	if(DI_Stopper != DO_Stopper)
		timer_error_stopper.IN = 1;
	else
		timer_error_stopper.IN = 0;
	
	timer_error_stopper.PT = timer_error_stopper_time;
	TON(&timer_error_stopper);
	
	if(timer_error_stopper.Q)
	{
		timer_error_stopper.IN = 0;
		TON(&timer_error_stopper);
		
		error_code = KEINE_DRUCKLUFT;
		set_error_state = true;
	}
	
	//Motor läuft 12 Sekunden (im Automatikmodus)
	if((DO_Antrieb_links || DO_Antrieb_rechts) && auto_mode_glob)	
		timer_error.IN = 1;
	else
		timer_error.IN = 0;
	
	timer_error.PT = timer_error_time;
	TON(&timer_error);
	
	if(timer_error.Q)
	{
		timer_error.IN = 0;
		TON(&timer_error);
		
		error_code = MOTOR_LAEUFT_ZU_LANGE;
		set_error_state = true;
	}
}