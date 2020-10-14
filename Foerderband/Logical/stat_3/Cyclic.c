#define false 0
#define true 1

#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

enum hubzylinderstates {UP, DWN, DONT_MOVE};
enum states{WAIT, SENKEN, HALTEN, HEBEN, FERTIG, ERROR};
enum error_states {NO_ERROR, KEINE_FRONTSCHALE};

void setHubzylinderstate (enum hubzylinderstates state)
{
	switch(state)
	{
		case UP:
			DO_Hubzylinder_auf_stat3 = 1;
			DO_Hubzylinder_ab_stat3 = 0;
			break;
		case DWN:
			DO_Hubzylinder_auf_stat3 = 0;
			DO_Hubzylinder_ab_stat3 = 1;
			break;
		case DONT_MOVE:
			DO_Hubzylinder_auf_stat3 = 0;
			DO_Hubzylinder_ab_stat3 = 0;
			break;
	}
}


void _CYCLIC ProgramCyclic(void)
{
	static enum states state = WAIT;
	static enum error_states error_state = NO_ERROR;
	static F_TRIGtyp stop_trig;

	stop_trig.CLK = DI_Stop;
	F_TRIG(&stop_trig);
	switch(state)
	{
		case WAIT:	//Auf Arbeitsbefehl (work_now) warten und überprüfen, ob Frontschale vorhanden
			setHubzylinderstate(UP);
			work_done = 0;
			
			if((work_now && DI_Frontschale_vorhanden && auto_mode_glob) || (manual_work_mode_glob && stop_trig.Q))	//Arbeitsbefehl vorhanden & Werkstück in Ordnung --> Senken
				state = SENKEN;
			
			if(work_now && !DI_Frontschale_vorhanden)	//Arbeitsbefehl vorhanden & Werkstück nicht in Ordnung --> Error
			{
				error_state = KEINE_FRONTSCHALE;
				state = ERROR;
			}
			break;
		
		case SENKEN:	//Hubzylinder senken und halten 
			setHubzylinderstate(DWN);
			
			if((DI_Hubzylinder_unten_stat3 && auto_mode_glob)|| (manual_work_mode_glob && stop_trig.Q))
				state = HALTEN;	
			break;
		
		case HALTEN:	//Hubzylinder nicht bewegen, Timer abwarten, dann Hubzylinder heben
			setHubzylinderstate(DONT_MOVE);
			
			Timer_Pressen.PT = Time_Pressen;
			Timer_Pressen.IN = 1;

			if ((Timer_Pressen.Q&& auto_mode_glob)|| (manual_work_mode_glob && stop_trig.Q))
			{
				Timer_Pressen.IN = 0;
				state = HEBEN;
			}
			break;

		case HEBEN:		//Hubzylinder heben --> Fertig
			setHubzylinderstate(UP);
			
			if((DI_Hubzylinder_oben_stat3 && auto_mode_glob)|| (manual_work_mode_glob && stop_trig.Q))
				state = FERTIG;
			break;
		
		case FERTIG:
			work_done = true;
			
			if(work_now == 0)
				state = WAIT;
			break;
		
		case ERROR:
			break;
	}

	if((!auto_mode_glob || !work_now) &&(!manual_work_mode_glob))
		state = WAIT;
	work_state = state;
	TON(&Timer_Pressen);

}