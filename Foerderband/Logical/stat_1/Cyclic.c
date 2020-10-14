#define false 0
#define true 1

#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

enum hubzylinderstates{UP, DWN, DONT_MOVE};
enum linearStates{LINKS,RECHTS};
enum states{WAIT, SENKEN, BOHREN_1, VERFAHREN, BOHREN_2, HEBEN, FERTIG, ERROR};

void setHubzylinderstate(enum hubzylinderstates  state)
{
	DO_Z_axis_Klemmung = 1;
	switch(state)
	{
		case UP:
			DO_Z_axis_nach_oben = 1;
			DO_Z_axis_nach_unten = 0;
			break;
		case DWN:
			DO_Z_axis_nach_oben = 0;
			DO_Z_axis_nach_unten = 1;
			break;
		case DONT_MOVE:
			DO_Z_axis_Klemmung = 0;
			break;
	}
}

void setLinearAchse(enum linearStates state)
{
	switch(state)
	{
		case LINKS:
			DO_X_axis_nach_links = 1;
			DO_X_axis_nach_rechts = 0;
			break;
		
		case RECHTS:
			DO_X_axis_nach_links = 0;
			DO_X_axis_nach_rechts = 1;
			break;
	}
}

void setBohrer(int on)
{
	DO_Bohrer1 = on;
	DO_Bohrer2 = on;
}

void _CYCLIC ProgramCyclic(void)
{
	static enum states state = WAIT;

	switch(state)
	{
		case WAIT:
			setHubzylinderstate(UP);
			setLinearAchse(LINKS);
			setBohrer(0);
			work_done = 0;
			if(work_now)
				state=BOHREN_1;
			break;
		case SENKEN:
			setHubzylinderstate(DWN);
			if(DI_Z_axis_unten)
				state= HEBEN;
			break;
		case BOHREN_1:
			setBohrer(1);
			state=SENKEN;
			break;
		
		case VERFAHREN:
			setLinearAchse(RECHTS);
			if(DI_X_axis_links)
				state = BOHREN_1;
			break;
		case BOHREN_2:
			
			break;
		case HEBEN:
			setHubzylinderstate(UP);
			if(DI_Z_axis_oben)
			{
				if(DI_X_axis_recht)
					state = VERFAHREN;
				else state = FERTIG;
			}
			break;
		case FERTIG:
			work_done = true;
			if(work_now == 0)
				state = WAIT;
			break;
		case ERROR:
			break;
	}
	if(!auto_mode_glob || !work_now)
		state = WAIT;
	work_state = state;
}
