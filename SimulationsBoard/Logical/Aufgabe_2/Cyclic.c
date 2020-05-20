
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _CYCLIC ProgramCyclic(void)
{
	char was_but_1_pressed, was_but_2_pressed, was_but_3_pressed,was_but_4_pressed;
	if(switch_left)
	{
		if(but_1)
		{
			LED1_green = 1;	
			LED1_red = 0;
		}
		else
		{
			LED1_green = 0;	
			LED1_red = 1;
		}
	}
	else
	{
		LED1_red = 0;
		LED2_red = 0;
		LED3_red = 0;
		LED4_red = 0;
	}
}
