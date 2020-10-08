
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#define MAX_ERROR_CNT_STOPPER 200

enum programm_states{EMER_HALT, INIT, STOP, GO_PRE_WORK, DETECT, WORK, GO_AFT_WORK, WAIT_TO_LET_GO, LET_GO, MANUAL, ERROR};

void _CYCLIC ProgramCyclic(void)
{
	static int stopper_err_cnt = 0;
	
	//Stopper
	if(DI_Stopper != DO_Stopper)
		stopper_err_cnt++;
	else
		stopper_err_cnt = 0;
	
	
}