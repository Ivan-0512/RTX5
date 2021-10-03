
#include "test.h"

static void _ledThread(void *argument);
static void _thread2(void *argument);

osEventFlagsId_t evt;

void
testEventFlags(void)
{
	evt = osEventFlagsNew(NULL);
	osThreadNew(_ledThread, NULL, NULL); // Create application led thread
	osThreadNew(_thread2, NULL, NULL); // Create application segment led thread
}

static void
_ledThread(void *argument)
{
	(void)argument;
	uint32_t flags;
	
	for(;;) {
		flags = osEventFlagsWait(evt, 0x00000001, osFlagsWaitAny, osWaitForever);
		menuShow(&seg_led, flags, 0);
		
		flags = osEventFlagsWait(evt, 0x00000002, osFlagsWaitAny, osWaitForever);
		menuShow(&seg_led, flags, 0);
		
		flags = osEventFlagsWait(evt, 0x0000000C, osFlagsWaitAll | osFlagsNoClear, osWaitForever);
		flags = osEventFlagsGet(evt);
		menuShow(&seg_led, flags, 0);
		osEventFlagsClear (evt, 0x0000000C);
		
		flags = osEventFlagsWait(evt, 0x00000007, osFlagsWaitAll, osWaitForever);
		menuShow(&seg_led, flags, 0);
	}
}

static void
_thread2(void *argument)
{
	(void)argument;
	for(;;) {
		osEventFlagsSet(evt, 0x00000001);
		osDelay(1000);
		
		osEventFlagsSet(evt, 0x00000002);
		osDelay(1000);
		
		osEventFlagsSet(evt, 0x0000000C);
		osDelay(1000);
		
		osEventFlagsSet(evt, 0x00000007);
		osDelay(1000);
	}
}
