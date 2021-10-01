/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
 
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"

static void appMain(void *argument);

int
main(void)
{
	// System Initialization
	SystemCoreClockUpdate();
	// ...

	osKernelInitialize();             // Initialize CMSIS-RTOS
	osThreadNew(appMain, NULL, NULL); // Create application main thread
	osKernelStart();                  // Start thread execution
	for (;;) {}
}

static void
appMain(void *argument)
{
	(void)argument;
	
	for(;;) {
		
	}
}