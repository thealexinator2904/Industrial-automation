
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	switch_left	=0;
	switch_right = 0;
	but_1 = 0;
	but_3 = 0;
	but_2 = 0;
	but_4 = 0;

	LED1_green = 0;
	LED1_red = 0;
	LED1_orange = 0;

	LED2_green = 0;
	LED2_red = 0;
	LED2_orange = 0;

	LED3_green = 0;
	LED3_red = 0;
	LED3_orange = 0;
		
	LED4_green = 0;
	LED4_red = 0;
	LED4_orange = 0;

	pot_1 = 0;
	pot_2 = 0;
	takt = 0;
	seven_seg = 420;

}
