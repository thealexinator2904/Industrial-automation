
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

enum hubzylinderstates{UP, DWN, DONT_MOVE};
enum vereinzlerstates{OPEN, CLOSE};
enum states{WAIT, SENKEN, FALLEN_LASSEN, HEBEN, FERTIG, ERROR};

void setHubzylinderstate(enum hubzylinderstates  state)
{
	DO_Zylinderklemmung = 1;
	switch(state)
	{
		case UP:
			DO_Hubzylinder_auf = 1;
			DO_Hubzylinder_ab = 0;
			break;
		case DWN:
			DO_Hubzylinder_auf = 0;
			DO_Hubzylinder_ab = 1;
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

void _CYCLIC ProgramCyclic(void)
{
	static enum states state = WAIT;
	switch(state)
	{
		case WAIT:
			setHubzylinderstate(UP);
			setVereinzlerstate(CLOSE);
			work_done = 0;
			if(work_now)
				state=SENKEN;
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
				state=HEBEN;
			break;
		case HEBEN:
			setVereinzlerstate(CLOSE);
			setHubzylinderstate(UP);
			if(DI_Hubzylinder_oben)
				state = FERTIG;
			break;
		case FERTIG:
			work_done = 1;
			if(work_now == 0)
				state = WAIT;
		case ERROR:

			break;
	}
}
