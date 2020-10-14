
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#define MAX_ERROR_CNT_STOPPER 200

enum programm_states{EMER_HALT, INIT, STOP, GO_PRE_WORK, DETECT, WORK, GO_AFT_WORK, WAIT_TO_LET_GO, LET_GO, MANUAL, ERROR};
enum error_codes{KEIN_ERROR, MOTOR_LAEUFT_ZU_LANGE, KEINE_DRUCKLUFT}; //TODO --> in Global.typ einfügen

void _CYCLIC ProgramCyclic(void)
{	
	static enum error_codes error_code = KEIN_ERROR;
	static int stopper_err_cnt = 0;
	
	//Stopper
	if(DI_Stopper != DO_Stopper)
		stopper_err_cnt++;
	else
		stopper_err_cnt = 0;
	
	//Motor läuft 12 Sekunden (im Automatikmodus)
	if((DO_Antrieb_links || DO_Antrieb_rechts) && !auto_mode_glob)	
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
		state = ERROR;
	}
}