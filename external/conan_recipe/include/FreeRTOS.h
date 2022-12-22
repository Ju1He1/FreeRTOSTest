#pragma once

#ifdef _WIN32
  #define FreeRTOS_EXPORT __declspec(dllexport)
#else
  #define FreeRTOS_EXPORT
#endif

FreeRTOS_EXPORT void FreeRTOS();
