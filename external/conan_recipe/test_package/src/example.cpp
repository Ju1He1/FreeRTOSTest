
#include <FreeRTOS/FreeRTOS.h>
#include <FreeRTOS/semphr.h>

static StaticSemaphore_t mg_MutexBuffer = {};

static SemaphoreHandle_t mg_mutexHandle = nullptr;

int main() {
    mg_mutexHandle = xSemaphoreCreateRecursiveMutexStatic(&mg_MutexBuffer);
	int iRes = -1;
	if(nullptr != mg_mutexHandle)
	{
		iRes = 0;
	}
	return iRes;
}
