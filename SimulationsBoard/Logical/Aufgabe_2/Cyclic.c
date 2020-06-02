#include <bur/plctypes.h>
#include <standard.h>       /* prototypes for STANDARD-Library */
#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _CYCLIC ProgramCyclic(void)
{
	R_TRIG_BUT_1.CLK = but_1;
	R_TRIG_BUT_2.CLK = but_2;
	R_TRIG_BUT_3.CLK = but_3;
	R_TRIG_BUT_4.CLK = but_4;
	R_TRIG_SW.CLK = switch_left;
	F_TRIG_SW.CLK = switch_left;
		
	R_TRIG(&R_TRIG_BUT_1);
	R_TRIG(&R_TRIG_BUT_2);
	R_TRIG(&R_TRIG_BUT_3);
	R_TRIG(&R_TRIG_BUT_4);
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
	
	if(R_TRIG_BUT_1.Q)
	{
		if(LED1_red != 0 || LED1_green !=0)
		{
			LED1_red = !LED1_red;
			LED1_green = !LED1_green;	
		}
	}
	if(R_TRIG_BUT_2.Q)
	{
		if(LED2_red != 0 || LED2_green !=0)
		{
			LED2_red = !LED2_red;
			LED2_green = !LED2_green;
		}
	}
	if(R_TRIG_BUT_3.Q)
	{
		if(LED3_red != 0 || LED3_green !=0)
		{
			LED3_red = !LED3_red;
			LED3_green = !LED3_green;	
		}
	}
	if(R_TRIG_BUT_4.Q)
	{
		if(LED4_red != 0 || LED4_green !=0)
		{
			LED4_red = !LED4_red;
			LED4_green = !LED4_green;
		}
	}
	
	LED_SW_left = switch_left;
}
