#include <bur/plctypes.h>
#include <standard.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#define T_OPENED_DOOR 5000

struct motorDATA
{
	char M_rechts, M_links, stop_rechts, stop_links, lichtschranke, anzeige;
};

enum
{
	INIT, STOP, OPENS, OPENED, CLOSES, ERROR
};

char handleDoor(char state, struct motorDATA *motor, char s_open, char isOTHERdoorClosed);

void _CYCLIC ProgramCyclic(void)
{
	static struct motorDATA motorDATA_1={0,0,0,0,0}, motorDATA_2={0,0,0,0,0};
	static int state1, state2;
	
	motorDATA_1.lichtschranke = B1;
	motorDATA_1.stop_links = S5;
	motorDATA_1.stop_rechts = S6;
	
	motorDATA_2.lichtschranke = B2;
	motorDATA_2.stop_links = S7;
	motorDATA_2.stop_rechts = S8;
	
	state1 = handleDoor(state1, &motorDATA_1, (S1 | S3), S7);
	state2 = handleDoor(state2, &motorDATA_2, (S4 | S2), S5);

	M1R = motorDATA_1.M_rechts;
	M1L = motorDATA_1.M_links;
	Anzeige_1 = motorDATA_1.anzeige;
	
	M2R = motorDATA_2.M_rechts;
	M2L = motorDATA_2.M_links;
	Anzeige_2 = motorDATA_2.anzeige;
}

char handleDoor(char state, struct motorDATA *motor, char s_open, char isOTHERdoorClosed)
{
	static TON_typ doorOpenTimer, blinkTimer, errorTimer;
	doorOpenTimer.PT = 5000;
	blinkTimer.PT = 200;
	errorTimer.PT = 10000;
	switch(state)
	{
		case INIT:
			motor->anzeige = 0;
			
			if(!motor->stop_links)
				state = CLOSES;
			if(motor->stop_links)
				state = STOP;
			break;
		
		case STOP:
			motor->M_rechts = 0;
			motor->M_links = 0;
			motor->anzeige = 0;
			
			if(s_open && isOTHERdoorClosed)
				state = OPENS;
			break;
		
		case OPENS:
			motor->M_rechts = 1;
			motor->M_links = 0;
			motor->anzeige = 0;
			
			if(motor->stop_rechts)
				state = OPENED;
			break;
		
		case OPENED:
			motor->M_rechts = 0;
			motor->M_links = 0;
			motor->anzeige = 0;
			doorOpenTimer.IN = 1;

			if(doorOpenTimer.Q)
			{
				doorOpenTimer.IN = 0;
				state = CLOSES;
			}
			break;
		
		case CLOSES:
			motor->M_rechts = 0;
			motor->M_links = 1;
			
			blinkTimer.IN = 1;
			if(blinkTimer.Q)
			{
				blinkTimer.IN = 0;
				//Toggle anzeigeLED
				motor->anzeige ^= 1;
			}
			
			if(motor->stop_links)
				state = STOP;
			if(motor->lichtschranke)
				state = OPENS;
			if(s_open)
				state = OPENS;
			
			break;
		
		case ERROR:
			motor->M_rechts = 0;
			motor->M_links = 0;
			motor->anzeige = 1;
			
			if(s_open && isOTHERdoorClosed)
				state = OPENS;
			break;
	}
	//errrorHandling
	errorTimer.IN = motor->M_links || motor->M_rechts;
	
	if(errorTimer.Q)
		state = ERROR;
	
	TON(&doorOpenTimer);
	TON(&blinkTimer);
	TON(&errorTimer)
	return state;
}
