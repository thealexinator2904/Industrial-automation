#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _CYCLIC ProgramCyclic(void)
{
	R_TRIG_SW.CLK = switch_left;
	F_TRIG_SW.CLK = switch_left;
	
	R_TRIG(&R_TRIG_SW);
	F_TRIG(&F_TRIG_SW);

	if(F_TRIG_SW.Q)
	{
		LED1_orange = 0;
		LED2_orange = 0;
		LED3_orange = 0;
		LED4_orange = 0;
	}
	
	if(R_TRIG_SW.Q)
	{
		LED1_orange = 1;
		LED2_orange = 1;
		LED3_orange = 1;
		LED4_orange = 1;
	}
	

	LED_SW_left = switch_left;
}
