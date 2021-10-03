
#include "test.h"

int
main(void)
{
	sysConfig();

	osKernelInitialize();             // Initialize CMSIS-RTOS
	#if 0
	testDelay();
	#endif
	
	#if 0
	testThreadFlags();
	#endif
	
	#if 0
	testEventFlags();
	#endif
	
	#if 1
	testTimer();
	#endif
	
	osKernelStart();                  // Start thread execution
	for (;;) {}
}