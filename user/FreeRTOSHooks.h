


#pragma once

#include <FreeRTOS.h>
#include <task.h>


#ifdef __cplusplus
extern "C" {
#endif

  //might be overwritten by user Application
  void vApplicationStackOverflowHook(TaskHandle_t pxTask, char* pcTaskName);
  void vApplicationTickHook(void);

  void vApplicationDaemonTaskStartupHook(void);

  void vApplicationIdleHook(void);

  void vApplicationMallocFailedHook(void);

  void vApplicationGetTimerTaskMemory(StaticTask_t** ppxTimerTaskTCBBuffer, StackType_t** ppxTimerTaskStackBuffer, uint32_t* pulTimerTaskStackSize);

  void vApplicationGetIdleTaskMemory(StaticTask_t** ppxIdleTaskTCBBuffer, StackType_t** ppxIdleTaskStackBuffer, uint32_t* pulIdleTaskStackSize);
#ifdef __cplusplus
}
#endif