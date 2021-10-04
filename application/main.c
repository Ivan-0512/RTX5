
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
	
	#if 0
	testTimer();
	#endif
	
	#if 0
	testMutex();
	#endif
	
	#if 0
	testSemaphore();
	#endif
	
	#if 1
	testMsgQueue();
	#endif
	
	osKernelStart();                  // Start thread execution
	for (;;) {}
}