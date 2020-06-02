
#include <bur/plctypes.h>
#include <standard.h>       /* prototypes for STANDARD-Library */
#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

void handleButton(R_TRIGtyp* edge, TONtyp* timer,BOOL* but, BOOL* red, BOOL* green)
{
	edge->CLK = timer->Q;
	timer->PT = 3000;
	timer->IN = *but;
	TON(timer);
	R_TRIG(edge);
	
	if(edge->Q)
	{
		if(*red != 0 || *green !=0)
		{
			*red = !*red;
			*green = !*green;	
		}
	}
}

void _CYCLIC ProgramCyclic(void)
{
	handleButton(&R_TRIG_BUT_1, &TON_BUT_1, &but_1, &LED1_red, &LED1_green);
	handleButton(&R_TRIG_BUT_2, &TON_BUT_2, &but_2, &LED2_red, &LED2_green);
	handleButton(&R_TRIG_BUT_3, &TON_BUT_3, &but_3, &LED3_red, &LED3_green);
	handleButton(&R_TRIG_BUT_4, &TON_BUT_4, &but_4, &LED4_red, &LED4_green);
	
	R_TRIG_SW.CLK = switch_left;
	F_TRIG_SW.CLK = switch_left;
	
	R_TRIG(&R_TRIG_SW);
	F_TRIG(&F_TRIG_SW);

	if(F_TRIG_SW.Q)
	{
		LED1_red = 0;
		LED1_green = 0;
		LED2_red = 0;
		LED2_green = 0;
		LED3_red = 0;
		LED3_green = 0;
		LED4_red = 0;
		LED4_green = 0;	
	}
	
	if(R_TRIG_SW.Q)
	{
		LED1_red = 1;
		LED1_green = 0;
		LED2_red = 1;
		LED2_green = 0;
		LED3_red = 1;
		LED3_green = 0;
		LED4_red = 1;
		LED4_green = 0;	
	}
	LED_SW_left = switch_left;
}
