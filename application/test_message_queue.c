
#include "test.h"

osMessageQueueId_t msg_queue;

static void _putThread(void *argument);
static void _getThread(void *argument);

void
testMsgQueue(void)
{	
	msg_queue = osMessageQueueNew(3, 4, NULL);
	
	osThreadNew(_putThread, NULL, NULL);
	osThreadNew(_getThread, NULL, NULL);
}

static void
_putThread(void *argument)
{
	(void)argument;
	uint32_t cnt = 0;
	
	for(;;) {
		osMessageQueuePut(msg_queue, &cnt, 0, 10);
		cnt ++;
		osDelay(1000);
	}
}

static void
_getThread(void *argument)
{
	(void)argument;
	uint32_t cnt;
	
	for(;;) {
		osMessageQueueGet(msg_queue, &cnt, NULL, osWaitForever);
		menuShow(&seg_led, cnt, 0);
	}
}
