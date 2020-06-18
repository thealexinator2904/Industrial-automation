
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#define T_OPENED_DOOR 5000

struct motorDATA
{
	BOOL M_rechts, M_links, stop_rechts, stop_links, lichtschranke;
};

enum
{
	STOP, OPENS, OPENED, CLOSES
};

char handleDoor(struct motorDATA *motor, char s_open, char isOTHERdoorClosed, char* isClosed);

void _CYCLIC ProgramCyclic(void)
{

}

char handleDoor(struct motorDATA *motor, char s_open, char isOTHERdoorClosed, char* isClosed)
{
	static int state = STOP;
	static R_TRIGtyp edge;
	static TONtyp doorOpenTimer;
	
	switch(state)
	{
		case STOP:
			motor->M_rechts = 0;
			motor->M_links = 0;
			if(s_open && isOTHERdoorClosed)
				state = OPENS;
			break;
		
		case OPENS:
			motor->M_rechts = 1;
			motor->M_links = 0;
			if(motor->stop_links)
				state = OPENED;
			if(motor->lichtschranke)
				state=STOP;
			break;
		
		case OPENED:
			motor->M_rechts = 0;
			motor->M_links = 0;

			doorOpenTimer.PT = T_OPENED_DOOR;
			doorOpenTimer.IN = 1;
			TON(&doorOpenTimer);
			if(doorOpenTimer.Q)
			{
				doorOpenTimer.IN = 0;
				state = CLOSES;
			}
			break;
		
		case CLOSES:
			motor->M_rechts = 0;
			motor->M_links = 0;
			
			if(motor->stop_rechts)
				state = STOP;
			if(motor->lichtschranke)
				state = STOP;
			break;

	}
	
	return state;
}