#include <bur/plctypes.h>
#include <standard.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

enum error_states{TIMEOUT_LEG_1, TIMEOUT_LEG_2, DETECTION_ERROR};
enum programm_states{INIT, STOP, GO_PRE_WORK, DETECT, WORK, GO_AFT_WORK, WAIT_TO_LET_GO, LET_GO, ERROR};

void _CYCLIC ProgramCyclic(void)
{
	static enum programm_states state=INIT;
	static F_TRIGtyp F_TRIG_01;
	
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
			if(DI_Ident_1 || DI_Ident_2 || DI_Ident_3 || DI_Ident_4)
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
			DO_Stopper = 0;
			if(DI_Band_links)
				state = GO_PRE_WORK;
			break;
		case GO_PRE_WORK:
			DO_Antrieb_rechts = 1;
			timer_5s.IN = 1;
			if(DI_Ident_1 || DI_Ident_2 || DI_Ident_3 || DI_Ident_4)
				state = DETECT;
			if(timer_5s.Q)
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
			if(timer_2s.Q)
			{
				state = WORK;
				timer_2s.IN = 0;
			}	
			
			//Sollte eigentlich GARNICHT passieren, aber bei timer error immer hilfreich 
			if(timer_5s.Q)
			{
				state = ERROR;
				timer_5s.IN = 0;
			}
			break;
		case WORK:
			DO_Antrieb_rechts = 0;
			DO_schleichgang = 0;
			//hier kannste mal arbeiten du Spast
			timer_5s.IN = 1;
			if(timer_5s.Q)
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
			break;
		case LET_GO:
			break;
		case ERROR:
			break;
	}
	TON(&timer_5s);
	TON(&timer_2s);
	F_TRIG(&F_TRIG_01);
}