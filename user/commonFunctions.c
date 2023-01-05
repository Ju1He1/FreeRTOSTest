#include "commonFunctions.h"



#ifndef BUILD_TARGET
#include "CMSIS_Simulation_Mock.h"
#endif // !BUILD_TARGET

extern int __get_IPSR();

bool inHandlerModePublic()
{
  const bool bHandlerMode = (__get_IPSR() != 0);
  return bHandlerMode;
}