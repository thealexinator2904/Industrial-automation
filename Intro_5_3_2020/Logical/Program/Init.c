
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	IN1 = 0;
	IN2 = 0;
	OUT = 1;
	ON_Del = 1000;
	Time_on.PT = ON_Del;
}
