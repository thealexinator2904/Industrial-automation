#define false 0
#define true 1

#define OR_MANUAL_MODE(bedingung) ((( bedingung ) && auto_mode_glob) || (manual_work_mode_glob && stop_trig.Q))

#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

void setHubzylinderstate(enum hubzylinderstates  state);
void setDrehzylinderstate(enum drehzylinderstates state);
void setGreiferstate(enum greiferstate state);

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
			setDrehzylinderstate(_0);
			setGreiferstate(OPEN);
			
			work_done = 0;
			 
			if(OR_MANUAL_MODE(work_now))
				state = SENKEN;
			
			if(!DI_Frontschale)
				state = FERTIG;
			break;
		
		case GREIFEN:
			setGreiferstate(CLOSE);
			
			if(OR_MANUAL_MODE(DI_Greifer_closed))
				state = HEBEN;
			break;
		
		case HEBEN:
			setHubzylinderstate(UP);
			
			if(OR_MANUAL_MODE(DI_Hubzylinder_oben && DI_phi_0) && DI_phi_0)
				state = DREHEN;
			
			if(OR_MANUAL_MODE(DI_Hubzylinder_oben && DI_phi_180) && DI_phi_180)
				state = FERTIG;
			break;
		
		case DREHEN:
			setDrehzylinderstate(_180);
			
			if(OR_MANUAL_MODE(DI_phi_180))
				state = SENKEN;
			break;
		
		case SENKEN:
			setHubzylinderstate(DWN);
			
			if(OR_MANUAL_MODE(DI_Hubzylinder_unten && DI_phi_0) && DI_phi_0)
				state = GREIFEN;
			
			if(OR_MANUAL_MODE(DI_Hubzylinder_unten && DI_phi_180) && DI_phi_180)
				state = LOESEN;
			break;
		
		case LOESEN:
			setGreiferstate(OPEN);
			
			if(OR_MANUAL_MODE(DI_Greifer_open))
				state = HEBEN;
			break;
		
		case FERTIG:
			work_done = true;
			
			if(work_now == 0)
				state = WAIT;
			break;
		
		case ERROR_STAT4:
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

void setDrehzylinderstate(enum drehzylinderstates state)
{
	switch(state)
	{
		case _0:
			DO_phi_0 = 1;
			DO_phi_180 = 0;
			break;
		
		case _180:
			DO_phi_0 = 0;
			DO_phi_180 = 1;	
			break;
	}
}

void setGreiferstate(enum greiferstate state)
{
	switch(state)
	{
		case OPEN:
			DO_Greifer_open = 1;
			DO_Greifer_close = 0;
			break;
		
		case CLOSE:
			DO_Greifer_open = 0;
			DO_Greifer_close = 1;
			break;
	}
}