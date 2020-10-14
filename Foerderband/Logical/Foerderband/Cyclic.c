#define false 0
#define true 1

#include <bur/plctypes.h>
#include <standard.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

enum error_states{NO_ERROR, TIMEOUT_LEG_1, TIMEOUT_LEG_2, DETECTION_ERROR};
enum programm_states{EMER_HALT, INIT, STOP, GO_PRE_WORK, DETECT, WORK, GO_AFT_WORK, WAIT_TO_LET_GO, LET_GO, MANUAL, ERROR};
enum koppel_state{RTR, RTT, BUSY};

BOOL isWorkMode()
{
	static TON_typ timer;
	static BOOL returnVal= false;
	
	timer.IN = DI_RESET;
	timer.PT = 2000;
	
	if(timer.Q)
	{
		returnVal = !returnVal;
		timer.IN = 0;
	}

	if(auto_mode_glob)
		returnVal = false;
	
	TON(&timer);
	
	return returnVal;
}
void set_Koppel(enum koppel_state state)
{
	switch(state)
	{
		case RTR:
			DO_Koppel_links = 1;
			DO_Koppel_rechts = 0;
			break;
		case RTT:
			DO_Koppel_links = !1;
			DO_Koppel_rechts = !0;
			break;
		case BUSY:
			DO_Koppel_links = 0;
			DO_Koppel_rechts = 0;
			break;
	}
}
BOOL isAutoMode()
{	
	static R_TRIGtyp r_start_but;
	r_start_but.CLK = DI_Start;
	static int auto_mode = false ;
	
	R_TRIG(&r_start_but);
	
	if(DI_Wahl)
		if(r_start_but.Q)
			auto_mode =  true;
		else ;
	else
		auto_mode = false;
	
	if(!DI_Stop)
		auto_mode = false;
	return auto_mode;
}

void _CYCLIC ProgramCyclic(void)
{
	static enum programm_states state=INIT;
	static enum error_states error= NO_ERROR;

	static F_TRIGtyp F_TRIG_01, F_TRIG_autoMode, F_TRIG_rechts;
	static int auto_mode=false;
	
	if(!DI_NOTAUS)
		state = EMER_HALT;
		
	auto_mode = isAutoMode();
	auto_mode_glob = auto_mode;
	work_now = 0;
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
			//ist, wird wohl keine da sein \O.O/ Was weiß ich,
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
			work_now = 1;
			if(work_done && auto_mode)
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
			if(!DI_Koppel_rechts) //wait till Übernahmebestätigung
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
			set_Koppel(BUSY);
			timer_5s.IN = 0;
			timer_2s.IN = 0;
			//DO_Antrieb_links = DI_Start;
			//DO_Antrieb_rechts = !DO_Antrieb_links && !DI_Stop;
			DO_Stopper = DI_RESET;
			
			if (!manual_work_mode_glob)
			{
				DO_Antrieb_links = DI_Start;
				DO_Antrieb_rechts = !DO_Antrieb_links && !DI_Stop;
				DO_Stopper = DI_RESET;
			}
			else
			{	
				DO_Antrieb_links = 0;
				DO_Antrieb_rechts = 0;
			}
			if (AI_Potentiometer_1 > 16000)
			{
				DO_schleichgang = 0;
			}
		
			if(auto_mode)
				state= INIT;
			break;
	}

	DO_Q1 = auto_mode;
	F_TRIG_rechts.CLK= DI_Band_rechts;
	
	if(DI_Wahl && !auto_mode)
	{
		timer_blink.IN = 1;
		if(timer_blink.Q)
		{
			timer_blink.IN = 0;
			DO_gruen = !DO_gruen;
		}
	}else
	{
		DO_gruen = auto_mode;	
	}
	
	TON(&timer_5s);
	TON(&timer_2s);
	TON(&timer_blink);
	R_TRIG(&F_TRIG_01);
	F_TRIG(&F_TRIG_rechts);
	
	manual_work_mode_glob = isWorkMode();
	DO_Q2 = manual_work_mode_glob;

	foerderband_state = state;
}