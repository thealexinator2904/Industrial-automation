#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void handleButton(R_TRIGtyp* edge, TONtyp* timer,BOOL* but, BOOL* red, BOOL* orange, BOOL* green);

void _CYCLIC ProgramCyclic(void)
{
	R_TRIG_SW.CLK = switch_left;
	F_TRIG_SW.CLK = switch_left;
	
	R_TRIG(&R_TRIG_SW);
	F_TRIG(&F_TRIG_SW);

	if(F_TRIG_SW.Q)
	{
		LED1_orange = 0;
		LED1_green = 0;
		LED1_red = 0;
		
		LED2_orange = 0;
		LED2_green = 0;
		LED2_red = 0;
		
		LED3_orange = 0;
		LED3_green = 0;
		LED3_red = 0;
		
		LED4_orange = 0;
		LED4_green = 0;
		LED4_red = 0;
	}
	
	if(R_TRIG_SW.Q)
	{
		LED1_orange = 1;
		LED2_orange = 1;
		LED3_orange = 1;
		LED4_orange = 1;
	}
	
	handleButton(&F_TRIG_BUT_1, &TON_BUT_1, &but_1, &LED1_red, &LED1_orange, &LED1_green);
	handleButton(&R_TRIG_BUT_2, &TON_BUT_2, &but_2, &LED2_red, &LED2_orange, &LED2_green);
	handleButton(&R_TRIG_BUT_3, &TON_BUT_3, &but_3, &LED3_red, &LED3_orange, &LED3_green);
	handleButton(&R_TRIG_BUT_4, &TON_BUT_4, &but_4, &LED4_red, &LED4_orange, &LED4_green);

	LED_SW_left = switch_left;
}

void handleButton(R_TRIGtyp* edge, TONtyp* timer,BOOL* but, BOOL* red, BOOL* orange, BOOL* green)
{
	timer->IN = *but;
	timer->PT = 1000;
	TON(timer);
	edge->CLK = *but;
	R_TRIG(edge);
	
	if(edge->Q && (*orange == 1 || *green == 1|| *red == 1))
	{
		*orange=0;
		*red = 0;
		*green = 1;
	}
	if(timer->Q && (*orange == 1 || *green == 1|| *red == 1))
	{
		*orange=0;
		*red = 1;
		*green = 0;
	}
}

void handleButton_extended()