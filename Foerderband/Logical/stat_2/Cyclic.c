#define false 0
#define true 1

#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

void setHubzylinderstate(enum hubzylinderstates  state);
void setVereinzlerstate(enum vereinzlerstates state);

void _CYCLIC ProgramCyclic(void)
{
	static enum states state = WAIT;

	switch(state)
	{
		case WAIT:
			setHubzylinderstate(UP);
			setVereinzlerstate(CLOSE);
			work_done = 0;
			
			if(work_now && DI_Palette)
				state = SENKEN;
			
			if(DI_Frontschale)
				state = HEBEN;
			break;
		
		case SENKEN:
			setHubzylinderstate(DWN);
			
			if(DI_Hubzylinder_unten)
				state = FALLEN_LASSEN;
			break;
		
		case FALLEN_LASSEN:
			setHubzylinderstate(DONT_MOVE);
			setVereinzlerstate(OPEN);
			
			if(DI_Hubzylinder_unten && DI_obere_Klinge)
				state = HEBEN;
			break;
		
		case HEBEN:
			setVereinzlerstate(CLOSE);
			setHubzylinderstate(UP);
			
			if(DI_Hubzylinder_oben)
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
	
	if(!auto_mode_glob || !work_now)
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