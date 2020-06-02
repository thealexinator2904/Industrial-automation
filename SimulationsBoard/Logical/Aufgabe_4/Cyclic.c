
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _CYCLIC ProgramCyclic(void)
{
	if(switch_left)
	{
		seven_seg = (100*pot_1/32767);
	}
	else
	{
		seven_seg = 0;	
	}
	LED_SW_left = switch_left;
}
