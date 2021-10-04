
#include "test.h"

osMutexId_t mutex;
const osMutexAttr_t mutex_attr = {
	.name = "_ledThread mutex",
	.attr_bits = osMutexRecursive | osMutexPrioInherit,
	.cb_mem = NULL,
	.cb_size = 0,
};

static void _ledThread(void *argument);

void
testMutex(void)
{	
	mutex = osMutexNew(&mutex_attr);
	
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
		status = osMutexAcquire(mutex, osWaitForever);
		if(osOK == status) {
			menuShow(&seg_led, id, 0);
			osDelay(delay);
			osMutexRelease(mutex);
		}
	}
}
