#define CHECK_CONDITION(params) (params) && isAutoMode()
#define true 1
#define false 0

#include <bur/plctypes.h>
#include <standard.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

enum error_states{NO_ERROR, TIMEOUT_LEG_1, TIMEOUT_LEG_2, DETECTION_ERROR};
enum programm_states{INIT, STOP, GO_PRE_WORK, DETECT, WORK, GO_AFT_WORK, WAIT_TO_LET_GO, LET_GO, ERROR, TEST};

BOOL isAutoMode()
{
	return 1;
}

void _CYCLIC ProgramCyclic(void)
{
	static enum programm_states state=INIT;
	static enum error_states error= NO_ERROR;
	static R_TRIGtyp r_start_but;
	static F_TRIGtyp F_TRIG_01;
	static int auto_mode=false;
	
	switch(state)
	{
		case INIT:
			DO_Antrieb_rechts = 1;
			DO_Stopper = 0;
			
			timer_5s.IN = 1;
			
			//Schritt 1 im Init: Anlage leer fahren um Fehler durch
			//power loss abzufangen
			if(DI_Band_links)
			{
				state = GO_PRE_WORK;
				timer_5s.IN = 0;
			}
	 		if((DI_Ident_1 || DI_Ident_2 || DI_Ident_3 || DI_Ident_4))
			{
				state=WORK;
				timer_5s.IN = 0;			
			}
			if(DI_Band_rechts)
			{
				state=GO_AFT_WORK;
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
			DO_Stopper = 0;
			if(DI_Band_links && auto_mode)
				state = GO_PRE_WORK;
			break;
		case GO_PRE_WORK:
			DO_Antrieb_rechts = 1;
			timer_5s.IN = 1;
			if((DI_Ident_1 || DI_Ident_2 || DI_Ident_3 || DI_Ident_4) && auto_mode)
				state = DETECT;
			if(timer_5s.Q && auto_mode)
			{
				state = ERROR;
				timer_5s.IN = 0;
			}
			break;	
		case DETECT:
			DO_Antrieb_rechts = 1;
			DO_schleichgang = 1;
			
			timer_5s.IN = 1;
			timer_2s.IN = 1;
			if(timer_2s.Q && auto_mode)
			{
				state = WORK;
				timer_2s.IN = 0;
				timer_5s.IN = 0;
			}
			break;
		case WORK:
			DO_Antrieb_rechts = 0;
			DO_schleichgang = 0;
			//hier kannste mal arbeiten du Spast
			timer_5s.IN = 1;
			if(timer_5s.Q && auto_mode)
			{
				state = GO_AFT_WORK;
				timer_5s.IN = 0;
			}
			break;
		case GO_AFT_WORK:
			DO_Stopper = 1;
			DO_Antrieb_rechts = 1;
			DO_schleichgang = 0;
			if(DI_Band_rechts)
				state = WAIT_TO_LET_GO;
			break;
		case WAIT_TO_LET_GO:
			DO_Stopper = 0;
			DO_Antrieb_rechts = 0;
			DO_schleichgang = 0;
			DO_Koppel_rechts = 1;
			if(DI_Koppel_rechts) //wait till Übernahmebestätigung
				state = STOP; //eigentlich let go, aber mein rechter Platz ist frei, ich wünsche mir jemanden herbei :( 
			break;
		case LET_GO: //Let it go, Let it go, can't hold it back anymore :D
				DO_Koppel_rechts = 0;
				DO_Antrieb_rechts = 0;//eigentlich 0 aber testzwecke
				if(!DI_Koppel_rechts && auto_mode)
					state = STOP;
			break;
		case ERROR:
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
	
	
	TON(&timer_5s);
	TON(&timer_2s);
	F_TRIG(&F_TRIG_01);
	R_TRIG(&r_start_but);
}