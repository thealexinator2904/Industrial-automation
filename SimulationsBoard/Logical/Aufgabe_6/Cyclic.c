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
		LED1_red = 0;
		LED1_green = 0;
	}
	
	if(R_TRIG_SW.Q)
	{
		LED1_red = 1;
		LED1_green = 0;
	}
	
	if(switch_left)
	{
		LED1_red = !LED1_red;
		LED1_green = !LED1_green;
	}
	LED_SW_left = switch_left;
}
