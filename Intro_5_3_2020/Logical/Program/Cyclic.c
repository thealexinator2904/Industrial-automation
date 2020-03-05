
#include <bur/plctypes.h>
#include <standard.h>
#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _CYCLIC ProgramCyclic(void)
{
	Time_on.IN = IN1;
	OUT = Time_on.Q;
	TON(&Time_on);
}
