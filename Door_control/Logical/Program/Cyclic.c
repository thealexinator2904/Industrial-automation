#include <bur/plctypes.h>
#include <standard.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#define T_OPENED_DOOR 5000

struct motorDATA
{
	char M_rechts, M_links, stop_rechts, stop_links, lichtschranke;
};

enum
{
	STOP, OPENS, OPENED, CLOSES
};

char handleDoor(char state, struct motorDATA *motor, char s_open, char isOTHERdoorClosed, char* isClosed);

void _CYCLIC ProgramCyclic(void)
{
	static struct motorDATA motorDATA_1={0,0,0,0,0}, motorDATA_2={0,0,0,0,0};
	static char bull;
	static int state1, state2;
	
	motorDATA_1.lichtschranke = B1;
	motorDATA_1.stop_links = S5;
	motorDATA_1.stop_rechts = S6;
	
	motorDATA_2.lichtschranke = B2;
	motorDATA_2.stop_links = S7;
	motorDATA_2.stop_rechts = S8;
	
	state1 = handleDoor(state1, &motorDATA_1, (S1 | S3), S7, &bull);
	state2 = handleDoor(state2, &motorDATA_2, (S4 | S2), S5, &bull);

	M1R = motorDATA_1.M_rechts;
	M1L = motorDATA_1.M_links;
	
	M2R = motorDATA_2.M_rechts;
	M2L = motorDATA_2.M_links;
}

char handleDoor(char state, struct motorDATA *motor, char s_open, char isOTHERdoorClosed, char* isClosed)
{
	static TON_typ doorOpenTimer;
	doorOpenTimer.PT = 5000;
	switch(state)
	{
		case STOP:
			motor->M_rechts = 0;
			motor->M_links = 0;
			if(s_open && isOTHERdoorClosed)
				state = OPENS;
			if(!motor->stop_links)
				state = CLOSES;
			break;
		
		case OPENS:
			motor->M_rechts = 1;
			motor->M_links = 0;
			if(motor->stop_rechts)
				state = OPENED;
			if(motor->lichtschranke)
				state=STOP;
			break;
		
		case OPENED:
			motor->M_rechts = 0;
			motor->M_links = 0;
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
			if(motor->stop_links)
				state = STOP;
			if(motor->lichtschranke)
				state = STOP;
			break;
	}
	TON(&doorOpenTimer);
	return state;
}
