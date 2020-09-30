#include <bur/plctypes.h>
#include <standard.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

enum error_states{NO_ERROR, TIMEOUT_LEG_1, TIMEOUT_LEG_2, DETECTION_ERROR};
enum programm_states{EMER_HALT, INIT, STOP, GO_PRE_WORK, DETECT, WORK, GO_AFT_WORK, WAIT_TO_LET_GO, LET_GO, MANUAL, ERROR};
enum koppel_state{RTR, RTT, BUSY};

void set_Koppel(enum koppel_state state)
{
	switch(state)
	{
		case RTR:
			DO_Koppel_links = 1;
			DO_Koppel_rechts = 0;
			break;
		case RTT:
			DO_Koppel_links = 1;
			DO_Koppel_rechts = 0;
			break;
		case BUSY:
			DO_Koppel_links = 0;
			DO_Koppel_rechts = 0;
			break;
	}
}
BOOL isAutoMode()
{
	return 1;
}

void _CYCLIC ProgramCyclic(void)
{
	static enum programm_states state=INIT;
	static enum error_states error= NO_ERROR;
	static R_TRIGtyp r_start_but;
	static F_TRIGtyp F_TRIG_01, F_TRIG_autoMode, F_TRIG_rechts;
	static int auto_mode=false;
	
	if(!DI_NOTAUS)
		state = EMER_HALT;
	DO_Q2=0;
	switch(state)
	{
		case EMER_HALT:
			DO_Antrieb_rechts = 0;
			DO_Antrieb_links = 0;
			set_Koppel(BUSY);
			if(DI_NOTAUS)
				state = INIT;
			break;
		case INIT:
			DO_Antrieb_rechts = 1;
			DO_Antrieb_links = 0;
			DO_Stopper = 0;
			DO_schleichgang = 0;
			timer_5s.IN = 1;
			timer_2s.IN = 0;
			set_Koppel(BUSY);
			//Schritt 1 im Init: Anlage leer fahren um Fehler durch
			//power loss abzufangen
			/*if(DI_Band_links && auto_mode)
			{
				state = GO_PRE_WORK;
				timer_5s.IN = 0;
			}*/
			if((DI_Ident_1 || DI_Ident_2 || DI_Ident_3 || DI_Ident_4) && auto_mode)
			{
				state=DETECT;
				timer_5s.IN = 0;			
			}
			if(DI_Band_rechts && auto_mode)
			{
				state=GO_AFT_WORK;
				timer_5s.IN = 0;			
			}
			if(!auto_mode)
			{
				state = MANUAL;
				timer_5s.IN = 0;
			}
			//Wenn die Palette nach 5 Sekunden nirgends aufgetaucht
			//ist, wird wohl keine da sein \O.O/ Was weiﬂ ich,
			//eigentlich isses ja wurscht
			if(timer_5s.Q)
			{
				state = STOP;
				timer_5s.IN = 0;
				DO_Stopper = 0;
			}
			break;
		case STOP:
			DO_Antrieb_rechts = 0;
			DO_Antrieb_links = 0;
			DO_Stopper = 0;
			timer_5s.IN = 0;
			timer_2s.IN = 0;
			set_Koppel(RTR);
			if(auto_mode && !DI_Koppel_links && DI_Band_links)
				state = GO_PRE_WORK;
			if(!auto_mode)
			{
				state = MANUAL;
			}
			break;
		case GO_PRE_WORK:
			DO_Antrieb_rechts = 1;
			timer_5s.IN = 1;
			timer_2s.IN = 0;
			set_Koppel(RTR);
			if((DI_Ident_1 || DI_Ident_2 || DI_Ident_3 || DI_Ident_4) && auto_mode)
				state = DETECT;
			if(!auto_mode)
			{
				state = MANUAL;
			}
			break;	
		case DETECT:
			DO_Antrieb_rechts = 1;
			DO_schleichgang = 1;
			set_Koppel(BUSY);
			timer_5s.IN = 1;
			timer_2s.IN = 1;
			if(timer_2s.Q && auto_mode)
			{
				state = WORK;
				timer_2s.IN = 0;
				timer_5s.IN = 0;
			}
			if(!auto_mode)
			{
				state = MANUAL;
			}
			break;
		case WORK:
			DO_Antrieb_rechts = 0;
			DO_schleichgang = 0;
			DO_Koppel_links = 0;
			timer_2s.IN = 0;
			set_Koppel(BUSY);
			//hier kannste mal arbeiten du Spast
			timer_5s.IN = 1;
			if(timer_5s.Q && auto_mode)
			{
				state = GO_AFT_WORK;
				timer_5s.IN = 0;
			}
			if(!auto_mode)
			{
				state = MANUAL;
			}
			break;
		case GO_AFT_WORK:
			DO_Stopper = 1;
			DO_Antrieb_rechts = 1;
			DO_schleichgang = 0;
			timer_5s.IN = 0;
			timer_2s.IN = 0;
			set_Koppel(BUSY);
			if(DI_Band_rechts)
				state = WAIT_TO_LET_GO;
			if(!auto_mode)
			{
				state = MANUAL;
			}
			break;
		case WAIT_TO_LET_GO:
			DO_Stopper = 0;
			DO_Antrieb_rechts = 0;
			DO_schleichgang = 0;
			timer_5s.IN = 0;
			timer_2s.IN = 0;
			set_Koppel(RTT);
			if(!DI_Koppel_rechts) //wait till ‹bernahmebest‰tigung
				state = LET_GO;
			if(!auto_mode)
			{
				state = MANUAL;
			}
			break;
		case LET_GO: //Let it go, Let it go, can't hold it back anymore :D
			DO_Antrieb_rechts = 1;
			timer_5s.IN = 0;
			timer_2s.IN = 0;
			set_Koppel(RTT);
			if(auto_mode && !DI_Band_rechts)
				state = STOP;
			if(!auto_mode)
			{
				state = MANUAL;
			}
			break;
		case ERROR:
			DO_Antrieb_links = 0;
			DO_Antrieb_rechts= 0;
			timer_5s.IN = 0;
			timer_2s.IN = 0;
			DO_Q2=1;
			set_Koppel(BUSY);
			if(!auto_mode)
			{
				state = MANUAL;
			}
			break;
		case MANUAL:
			DO_schleichgang = 1;
			DO_Antrieb_links = DI_Start;
			DO_Antrieb_rechts= !DO_Antrieb_links && !DI_Stop;
			DO_Stopper = DI_RESET;
			set_Koppel(BUSY);
			timer_5s.IN = 0;
			timer_2s.IN = 0;
			if(auto_mode)
				state= INIT;
			break;
	}
	
	r_start_but.CLK = DI_Start;
	
	if(DI_Wahl)
		if(r_start_but.Q)
			auto_mode=true;
		else ;
	else
		auto_mode=false;
	
	DO_Q1 = auto_mode;
	F_TRIG_rechts.CLK= DI_Band_rechts;
	TON(&timer_5s);
	TON(&timer_2s);
	R_TRIG(&F_TRIG_01);
	F_TRIG(&F_TRIG_rechts);
	R_TRIG(&r_start_but);
	state_glob = state;
}