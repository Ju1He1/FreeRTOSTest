#include "commonFunctions.h"



#ifdef BUILD_SIMULATION
#include "CMSIS_Simulation_Mock.h"
#endif // BUILD_SIMULATION

extern int __get_IPSR();

bool inHandlerModePublic()
{
  const bool bHandlerMode = (__get_IPSR() != 0);
  return bHandlerMode;
}