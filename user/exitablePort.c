#include <t3xx_2025_config.h>

/*
* overwrite the original exit function
* In Order to terminate GTest properly when running the freertos simulation we must end the scheduler
* unfortunately in the original Port vTaskEndScheduler() calls exit(0)
* =>GTest will allways end with success
* 
* Therefore we rename the original function and include everything else from the port
*/
#define vPortEndScheduler vPortEndScheduler_orig
#include T3XX_2025_FREERTOS_PORT_PATH

#undef vPortEndScheduler


void vPortEndScheduler(void)
{
	//exit( 0 );
}