
#include <bur/plctypes.h>
#define OR_MANUAL_MODE(bedingung) ((( bedingung ) && auto_mode_glob) || (manual_work_mode_glob && F_TRIG_stop.Q))
#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#define true 1
#define false 0

int takePicture(void);
void processPicture(void);

void _CYCLIC ProgramCyclic(void)
{	
	static enum states_stat6 state_stat6 = WAIT;
	static enum error_codes_stat6 error_code_stat6 = NO_ERROR;
	
	static R_TRIGtyp R_TRIG_reset;
	static F_TRIGtyp F_TRIG_stop;
	
	R_TRIG_reset.CLK = DI_RESET;
	R_TRIG(&R_TRIG_reset);
	F_TRIG_stop.CLK = DI_Stop;
	F_TRIG(&F_TRIG_stop);
	
	switch(state_stat6)
	{
		case WAIT:
			work_done = false;
			 
			if(OR_MANUAL_MODE(work_now))
				state_stat6 = TAKE_PIC;
			break;
			
		case TAKE_PIC:	//takes a picture, when finished, switches to processing it
			if(takePicture())
				state_stat6 = PROCESS_PIC;
			break;
		
		case PROCESS_PIC:	//processes the picture and decides whether its satisfactory or not
			processPicture();
			
			if((shit_pic_cnt < 3) || (nice_pic_cnt < 3))
				state_stat6 = TAKE_PIC;
			
			else if(shit_pic_cnt >= 3)	//if 3 consecutive pictures are bad -> ERROR_STAT6
			{
				state_stat6 = ERROR_STAT6;
				error_code_stat6 = SHIT_PIC;
			}
	
			else if (nice_pic_cnt >= 3)	//if 3 consecutive pictures are good -> WORK_DONE
				state_stat6 = WORK_DONE;
			break;
			
		case WORK_DONE:
			work_done = true;
				
			if(!work_now)
				state_stat6 = WAIT;
			break;
			
		case ERROR_STAT6:
			if(R_TRIG_reset.Q)
				state_stat6 = WAIT;
			break;
	}	
}

int takePicture(void)
{
	timer_picture.IN = true;
	timer_picture.PT = timer_picture_time;
	TON(&timer_picture);
	
	return false;
	
	if(timer_picture.Q)
	{
		DO_Kamera_Trigger = !DO_Kamera_Trigger;
		timer_picture.IN = false;
		TON(&timer_picture);
		
		return true;
	}
}

void processPicture(void)
{
	if (DI_Kamera_00 && (!DI_Kamera_02)) //good pic
		nice_pic_cnt++;
			
	else if ((!DI_Kamera_00) && DI_Kamera_02)	//bad pic
		shit_pic_cnt++;
}		
		
