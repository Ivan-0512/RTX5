
#include "test.h"


typedef struct {
	uint32_t val;
} Tick;

Tick tick;

static void _thread1(void *argument);
static void _oneShotTimerCallback(void *argument);
static void _periodicTimerCallback(void *argument);

void
testTimer(void)
{
	osTimerId_t one_shot;
	osTimerId_t periodic;
	
	periodic = osTimerNew(_periodicTimerCallback, osTimerPeriodic, (void *)&tick, NULL);
	if(NULL == periodic) {
		return;
	}
	
	one_shot = osTimerNew(_oneShotTimerCallback, osTimerOnce, (void *)periodic, NULL);
	if(NULL == one_shot) {
		return;
	}
	
	osThreadNew(_thread1, (void *)one_shot, NULL);
	
	osTimerStart(one_shot, 1000);
}

static void
_thread1(void *argument)
{
	osTimerId_t one_shot = (osTimerId_t)argument;
	osThreadId_t thread;
	
	osTimerStart(one_shot, 1000);
	
	thread = osThreadGetId();
	osThreadTerminate(thread);
}

static void
_oneShotTimerCallback(void *argument)
{
	osTimerId_t periodic = (osTimerId_t)argument;
	osTimerStart(periodic, 1000);
}

static void
_periodicTimerCallback(void *argument)
{
	Tick *tick = (Tick *)argument;
	
	tick->val ++;
	menuShow(&seg_led, tick->val, 0);
}
