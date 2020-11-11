#define TARGET_TEMP 9000
#define HYSTERESE 100

#define false 0
#define true 1

#include <bur/plctypes.h>
#include <standard.h>
#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

void _CYCLIC ProgramCyclic(void)
{
	static enum states state = WAIT;
	static int _ready_to_go = false;
	static TON_typ heat_timer;
	
	heat_timer.PT = heat_timer_time;
	heat_timer.IN =_ready_to_go;
	
	switch(state)
	{
		case WAIT:
			DO_Heizung = 0;
			work_done = 0;
			_ready_to_go = 0;
			
			if(work_now)
				state = HEIZEN;
			break;
		
		case HEIZEN:
			if(AI_Messwandler > TARGET_TEMP + HYSTERESE/2)
				DO_Heizung = 0;
			
			if(AI_Messwandler < TARGET_TEMP - HYSTERESE/2)
				DO_Heizung = 1;
			
			if(AI_Messwandler > TARGET_TEMP)
				_ready_to_go = 1;
			
			if(heat_timer.Q)
				state = FERTIG;
			break;
		
		case FERTIG:
			work_done = true;
			DO_Heizung = 0;
			_ready_to_go = 0;
			
			if(work_now == 0)
				state = WAIT;
			break;
		
		case ERROR_STAT5:
			break;
	}
	
	if(!auto_mode_glob || !work_now)
		state = WAIT;
	
	work_state = state;
	TON(&heat_timer);
}
