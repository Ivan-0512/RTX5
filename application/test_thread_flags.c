
#include "test.h"

static void _ledThread(void *argument);
static void _thread2(void *argument);

osThreadId_t led_thread;

void
testThreadFlags(void)
{
	
	led_thread = osThreadNew(_ledThread, NULL, NULL); // Create application led thread
	osThreadNew(_thread2, NULL, NULL); // Create application segment led thread
}

static void
_ledThread(void *argument)
{
	(void)argument;
	uint32_t flags;
	
	for(;;) {
		flags = osThreadFlagsWait(0x00000001, osFlagsWaitAny, osWaitForever);
		menuShow(&seg_led, flags, 0);
		
		flags = osThreadFlagsWait(0x00000002, osFlagsWaitAny, osWaitForever);
		menuShow(&seg_led, flags, 0);
		
		flags = osThreadFlagsWait(0x0000000C, osFlagsWaitAll | osFlagsNoClear, osWaitForever);
		flags = osThreadFlagsGet();
		menuShow(&seg_led, flags, 0);
		osThreadFlagsClear(0x0000000C);
		
		flags = osThreadFlagsWait(0x00000007, osFlagsWaitAll, osWaitForever);
		menuShow(&seg_led, flags, 0);
	}
}

static void
_thread2(void *argument)
{
	(void)argument;
	for(;;) {
		osThreadFlagsSet(led_thread, 0x00000001);
		osDelay(1000);
		
		osThreadFlagsSet(led_thread, 0x00000002);
		osDelay(1000);
		
		osThreadFlagsSet(led_thread, 0x0000000C);
		osDelay(1000);
		
		osThreadFlagsSet(led_thread, 0x00000007);
		osDelay(1000);
	}
}
