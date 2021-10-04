
#include "test.h"

osSemaphoreId_t sem;

static void _ledThread(void *argument);

void
testSemaphore(void)
{	
	sem = osSemaphoreNew(1, 1, NULL);
	
	osThreadNew(_ledThread, (void *)1, NULL);
	osThreadNew(_ledThread, (void *)2, NULL);
}

static void
_ledThread(void *argument)
{
	osStatus_t status;
	uint32_t id = (uint32_t)argument;
	uint32_t delay;
	
	if(1 == id) {
		delay = 500;
	} else {
		delay = 1000;
	}
	
	for(;;) {
		status = osSemaphoreAcquire(sem, osWaitForever);
		if(osOK == status) {
			menuShow(&seg_led, id, 0);
			osDelay(delay);
			osSemaphoreRelease(sem);
		}
	}
}
