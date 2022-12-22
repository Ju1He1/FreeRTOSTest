#include <FreeRTOS.h>
#include <task.h>
#include "AssertWithTrace.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __GNUC__
#include <unistd.h>
#endif //__GNUC__



#ifndef _MSC_VER
static long int GetLastError()
{
  return 0;
}

#endif // !_MSC_VER


void vAssertCalled(const char* const pcFileName, unsigned long ulLine)
{


  /* Called if an assertion passed to configASSERT() fails.  See
  http://www.freertos.org/a00110.html#configASSERT for more information. */
  printf("ASSERT! Line %ld, file %s, GetLastError() %ld\r\n", ulLine, pcFileName, GetLastError());
  fprintf(stderr, "ASSERT! Line %ld, file %s, GetLastError() %ld\r\n", ulLine, pcFileName, GetLastError());
  {
    char chBuffer[100] = { 0 };

    //only export the last 30 Characters of the filename
    const uint32_t u32MaxFilenameLength = 30;
    const uint32_t u32BufferOffset = (uint32_t)strlen(pcFileName) - u32MaxFilenameLength;
    snprintf(chBuffer, sizeof(chBuffer), "ASSERT!Line %ld, file %s, GetLastError() %ld\r\n", ulLine, pcFileName + u32BufferOffset, GetLastError());
    perror(chBuffer);
  }
  taskENTER_CRITICAL();
  {

#ifdef BUILD_SIMULATION

#ifdef _MSC_VER
    /* Cause debugger break point if being debugged. */
    __debugbreak();
#endif //_MSC_VER
    //Abort Simmulation
    abort();
#endif //BUILD_SIMMULATION

#ifdef BUILD_TARGET
    //on the target we must hold the programm.
    for (;;)
    {
      volatile int i = 0;
      i++;
    }
#endif //BUILD_TARGET
  }
  taskEXIT_CRITICAL();
}

