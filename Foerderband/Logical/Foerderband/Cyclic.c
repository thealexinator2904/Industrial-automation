#define false 0
#define true 1

#include <bur/plctypes.h>
#include <standard.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

BOOL isWorkMode();
BOOL isAutoMode();
void set_Koppel(enum koppel_state state);
blinkLed(BOOL* led, INT time_to_blink);
blinkLed2(BOOL* led1, BOOL* led2, INT time_to_blink);

void _CYCLIC ProgramCyclic(void)
{
	static enum programm_states state = INIT;
	static enum error_codes error_code = KEIN_ERROR;

	static F_TRIGtyp F_TRIG_01, F_TRIG_autoMode, F_TRIG_rechts;
	static R_TRIGtyp R_TRIG_reset;
	static int auto_mode = false;
	
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
			DO_gruen = 1;
			DO_Antrieb_rechts = 1;
			DO_Antrieb_links = 0;
			DO_Stopper = 0;
			DO_schleichgang = 0;
			set_Koppel(BUSY);
			
			timer_2s.IN = 0;
			timer_5s.IN = 1;
			if((DI_Ident_1 || DI_Ident_2 || DI_Ident_3 || DI_Ident_4) && auto_mode)
				state = DETECT;	
	
			if(DI_Band_rechts && auto_mode)
				state = GO_AFT_WORK;
			
			if(timer_5s.Q && auto_mode)
			{
				timer_5s.IN = 0;
				state = STOP;
			}
			if(!auto_mode)
				state = MANUAL;
			break;
		
		case STOP:
			DO_Antrieb_rechts = 0;
			DO_Antrieb_links = 0;
			DO_Stopper = 0;
			set_Koppel(RTR);
			
			timer_2s.IN = 0;
			
			if(auto_mode && !DI_Koppel_links)
				state = GO_PRE_WORK;
			if(!auto_mode)
			{
				state = MANUAL;
			}
			break;
		
		case GO_PRE_WORK:
			DO_Antrieb_rechts = 1;
			set_Koppel(RTR);
			
			timer_2s.IN = 0;
			
			if((DI_Ident_1 || DI_Ident_2 || DI_Ident_3 || DI_Ident_4) && auto_mode)
				state = DETECT;
			
			if(!auto_mode)
				state = MANUAL;
			break;	
		
		case DETECT:
			DO_Antrieb_rechts = 1;
			DO_schleichgang = 1;
			set_Koppel(BUSY);
			
			timer_2s.IN = 1;
			
			if(timer_2s.Q && auto_mode)
			{
				state = WORK;
				timer_2s.IN = 0;
			}
			
			if(!auto_mode)
				state = MANUAL;
			break;
		
		case WORK: 
			DO_Antrieb_rechts = 0;
			DO_schleichgang = 0;
			DO_Koppel_links = 0;
			set_Koppel(BUSY);
			
			timer_2s.IN = 0;
			work_now = 1;
			
			if(work_done && auto_mode)
				state = GO_AFT_WORK;
			
			if(!auto_mode)
				state = MANUAL;
			break;
		
		case GO_AFT_WORK:
			DO_Stopper = 1;
			DO_schleichgang = 0;
			DO_Antrieb_rechts = 1;
			set_Koppel(BUSY);
			
			timer_2s.IN = 0;

			if(DI_Band_rechts)
				state = WAIT_TO_LET_GO;
			
			if(!auto_mode)
			{
				state = MANUAL;
			}
			break;
		
		case WAIT_TO_LET_GO:
			DO_Stopper = 0;
			DO_schleichgang = 0;
			DO_Antrieb_rechts = 0;
			set_Koppel(RTT);
			
			timer_2s.IN = 0;

			if(!DI_Koppel_rechts) //wait till Übernahmebestätigung
				state = LET_GO;
			
			if(!auto_mode)
			{
				state = MANUAL;
			}
			break;
		
		case LET_GO: //Let it go, Let it go, can't hold it back anymore :D
			DO_Antrieb_rechts = 1;
			set_Koppel(RTT);
			
			timer_2s.IN = 0;

			if(auto_mode && !DI_Band_rechts)
				state = STOP;
			
			if(!auto_mode)
			{
				state = MANUAL;
			}
			break;
		
		case ERROR:
			DO_Antrieb_links = 0;
			DO_Antrieb_rechts = 0;
			error_flag = true;
			set_Koppel(BUSY);
			
			timer_2s.IN = 0;
			blinkLed2(&DO_Q1, &DO_Q2, time_blink_fast);

			if(!auto_mode)
				state = MANUAL;
			break;
		
		case MANUAL:
			set_Koppel(BUSY);
			timer_2s.IN = 0;
			error_flag = 0;

			if (AI_Potentiometer_1 > 16000)
				DO_schleichgang = 0;
			else
				DO_schleichgang = 1;
			
			if (!manual_work_mode_glob)
			{
				if(DI_Start)
				{
					DO_Antrieb_links = 1;
					DO_Antrieb_rechts = 0;
					DO_weiss = 0;
					
					if(DO_schleichgang)
						blinkLed(&DO_gruen, time_blink_middle);
					else
						blinkLed(&DO_gruen, time_blink_fast);
				}
				else if(!DO_Antrieb_links && !DI_Stop)
				{
					DO_Antrieb_rechts = 1;
					DO_Antrieb_links = 0;
					DO_gruen = 0;
					
					if(DO_schleichgang)
						blinkLed(&DO_weiss, time_blink_middle);
					else
						blinkLed(&DO_weiss, time_blink_fast);
				}
				else
				{
					DO_Antrieb_links = 0;
					DO_Antrieb_rechts = 0;
					
					DO_gruen = 0;
					DO_weiss = 0;
				}
			
				if(R_TRIG_reset.Q)
				{
					DO_Stopper = !DO_Stopper;
				}
			}
			else
			{	
				DO_Antrieb_links = 0;
				DO_Antrieb_rechts = 0;
			}

			if(auto_mode)
			{
				DO_gruen = 0;
				DO_weiss = 0;
				DO_Q1 = 0;
				DO_Q2 = 0;
			
				state = INIT;
			}
			break;
	}

	DO_Q1 = auto_mode;
	F_TRIG_rechts.CLK = DI_Band_rechts;
	
	if(DI_Wahl && !auto_mode)
		blinkLed(&DO_gruen, time_blink_slow);
	
	TON(&timer_2s);
	TON(&timer_5s);
	R_TRIG(&F_TRIG_01);
	R_TRIG_reset.CLK = DI_RESET;
	R_TRIG(&R_TRIG_reset);
	F_TRIG(&F_TRIG_rechts);
	
	manual_work_mode_glob = isWorkMode();
	DO_Q2 = manual_work_mode_glob;

	foerderband_state = state;
	
	if(set_error_state == 1)
		state = ERROR;
}

BOOL isWorkMode()
{
	static TON_typ timer;
	static BOOL returnVal = false;
	
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

BOOL isAutoMode()
{	
	static R_TRIGtyp r_start_but;
	r_start_but.CLK = DI_Start;
	static int auto_mode = false ;
	
	R_TRIG(&r_start_but);
	
	if(DI_Wahl)
		if(r_start_but.Q && !error_flag)
			auto_mode = true;
		else ;
	else
	{
		auto_mode = false;
		error_flag = false;
		set_error_state = false;
	}
	
	if(!DI_Stop)
		auto_mode = false;
	
	return auto_mode;
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

blinkLed(BOOL* led, INT time_to_blink)
{
	timer_blink.IN = 1;
	timer_blink.PT = time_to_blink;
			
	TON(&timer_blink);
			
	if(timer_blink.Q)
	{
		*led = !(*led);
		timer_blink.IN = 0;
		TON(&timer_blink);
	}
}

blinkLed2(BOOL* led_1, BOOL* led_2, INT time_to_blink)
{
	timer_blink2.IN = 1;
	timer_blink2.PT = time_to_blink;
			
	TON(&timer_blink2);
			
	if(timer_blink2.Q)
	{
		*led_1 = !(*led_1);
		*led_2 = !(*led_2);
		timer_blink2.IN = 0;
		TON(&timer_blink2);
	}
}