#define false 0
#define true 1

#define OR_MANUAL_MODE(bedingung) ((( bedingung ) && auto_mode_glob) || (manual_work_mode_glob && stop_trig.Q))

#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

void setHubzylinderstate(enum hubzylinderstates  state);
void setVereinzlerstate(enum vereinzlerstates state);

void _CYCLIC ProgramCyclic(void)
{
	static enum states state = WAIT;
	static F_TRIGtyp stop_trig;

	stop_trig.CLK = DI_Stop;
	F_TRIG(&stop_trig);
	
	switch(state)
	{
		case WAIT:
			setHubzylinderstate(UP);
			setVereinzlerstate(CLOSE);
			work_done = 0;
			
			if(OR_MANUAL_MODE( work_now && DI_Palette))
				state = SENKEN;
			
			if(DI_Frontschale)
				state = HEBEN;
			break;
		
		case SENKEN:
			setHubzylinderstate(DWN);
			
			if(OR_MANUAL_MODE( DI_Hubzylinder_unten ))
				state = FALLEN_LASSEN;
			break;
		
		case FALLEN_LASSEN:
			setHubzylinderstate(DONT_MOVE);
			setVereinzlerstate(OPEN);
			
			if(OR_MANUAL_MODE( DI_Hubzylinder_unten && DI_obere_Klinge))
				state = HEBEN;
			break;
		
		case HEBEN:
			setVereinzlerstate(CLOSE);
			setHubzylinderstate(UP);
			
			if(OR_MANUAL_MODE( DI_Hubzylinder_oben))
				state = FERTIG;
			break;
		
		case FERTIG:
			work_done = true;
			if(work_now == 0)
				state = WAIT;
			break;
		
		case ERROR_STAT2:
			break;
	}
	
	if((!auto_mode_glob || !work_now) && !manual_work_mode_glob)
		state = WAIT;
	work_state = state;
}

void setHubzylinderstate(enum hubzylinderstates  state)
{
	switch(state)
	{
		case UP:
			DO_Hubzylinder_auf = 1;
			DO_Hubzylinder_ab = 0;
			
			DO_Zylinderklemmung = 1;
			break;
		
		case DWN:
			DO_Hubzylinder_auf = 0;
			DO_Hubzylinder_ab = 1;
			
			DO_Zylinderklemmung = 1;
			break;
		
		case DONT_MOVE:
			DO_Zylinderklemmung = 0;
			break;
	}
}

void setVereinzlerstate(enum vereinzlerstates state)
{
	switch(state)
	{
		case OPEN:
			DO_Vereinzler_close = 0;
			DO_Vereinzler_open = 1;
			break;
		
		case CLOSE:
			DO_Vereinzler_close = 1;
			DO_Vereinzler_open = 0;		
			break;
	}
}