struct motorDATA
{
	BOOL M_rechts, M_links, stop_rechts, stop_links, lichtschranke;
};

enum
{
	STOP, OPENS, OPENED, CLOSES, CLOSED
};

char handleDoor(struct motorDATA *motor, char s_open, char s_close, char isOTHERdoorClosed, char* isClosed)
{
	static int state = STOP;
	
	switch(state)
	{
		case STOP:
			motor->M_rechts = 0;
			motor->M_links = 0;
			if(s_open && isOTHERdoorClosed)
				state = OPENS;
			if(s_close)
				state = CLOSES
		break;
		
		case OPENS:
			
		break;
		
		case OPENED:
		
		break;
		
		case CLOSES:
		
		break;
		
		case CLOSED:
		
		break;
		
		case default:
		
		break;
	}
	return state;
}