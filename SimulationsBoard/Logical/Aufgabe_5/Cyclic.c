
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

int add(int, int);
int subtract(int, int);
int multiply(int, int);
int divide(int, int);
void handleButton(R_TRIGtyp* , BOOL* , int (*fun)(int, int), int, int, int*);

void _CYCLIC ProgramCyclic(void)
{
	handleButton(&R_TRIG_BUT_1, &but_1, add, savedVal_Pot_1,savedVal_Pot_2, &seven_seg);
	handleButton(&R_TRIG_BUT_2, &but_2, subtract, savedVal_Pot_1,savedVal_Pot_2, &seven_seg);
	handleButton(&R_TRIG_BUT_3, &but_3, multiply, savedVal_Pot_1,savedVal_Pot_2, &seven_seg);
	handleButton(&R_TRIG_BUT_4, &but_4, divide, savedVal_Pot_1,savedVal_Pot_2, &seven_seg);
	
	F_TRIG_SW.CLK = switch_left;
	F_TRIG_SW_RIGHT.CLK = switch_right;
	
	//Anzeige linkes Poti
	if(switch_left && !switch_right)
		seven_seg = (100*pot_1/32767);
	//anzeige rechtes Poti
	if(!switch_left && switch_right)
		seven_seg = (100*pot_2/32767);		
	
	//Wenn beide ein sind: --- anzeigen
	if(switch_left && switch_right)
		seven_seg = 1000;
	
	if(F_TRIG_SW.Q)
		savedVal_Pot_1 = 100*pot_1/32767;
	if(F_TRIG_SW_RIGHT.Q)
		savedVal_Pot_2 = 100*pot_2/32767;
	
	F_TRIG(&F_TRIG_SW);
	F_TRIG(&F_TRIG_SW_RIGHT);
	
	LED_SW_left = switch_left;
	LED_SW_right = switch_right;
}

int add(int a, int b )
{
	return a+b;
}
int subtract(int a, int b )
{
	return a-b;
}

int multiply(int a, int b )
{
	return a*b;
}
int divide(int a, int b )
{
	return a/b;
}

void handleButton(R_TRIGtyp* edge, BOOL* but, int (*fun)(int, int), int a, int b, int* output)
{
	edge->CLK = *but;
	R_TRIG(edge);
	
	if(edge->Q)
		*output = fun(a,b);
}