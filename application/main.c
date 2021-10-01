/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
 
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "led.h"
#include "spi_led.h"
#include "utility.h"

Led led1;
SegLed seg_led;

static void _Led1Task(void *argument);
static void _segLedTask(void *argument);
static void _sysConfig(void);

int
main(void)
{
	_sysConfig();

	osKernelInitialize();             // Initialize CMSIS-RTOS
	osThreadNew(_Led1Task, NULL, NULL); // Create application led thread
	osThreadNew(_segLedTask, NULL, NULL); // Create application segment led thread
	osKernelStart();                  // Start thread execution
	for (;;) {}
}

static void
_Led1Task(void *argument)
{
	(void)argument;
	
	for(;;) {
		ledOn(&led1);
		osDelay(500); /** delay 500 RTOS ticks **/
		ledOff(&led1);
		osDelay(500); /** delay 500 RTOS ticks **/
	}
}

static void
_segLedTask(void *argument)
{
	(void)argument;
	uint32_t tick;
	static const uint8_t seg_code[] =
	{
		DEF_LED_0,
		DEF_LED_1,
		DEF_LED_2,
		DEF_LED_3,
		DEF_LED_4,
		DEF_LED_5,
		DEF_LED_6,
		DEF_LED_7,
		DEF_LED_8,
		DEF_LED_9,
	};
	uint8_t sc_sz;
	uint8_t start_ix;
	uint8_t ix;
	
	start_ix = 0;
	sc_sz = ARRAYSIZE(seg_code);
	tick = osKernelGetTickCount();
	
	for(;;) {
		tick += 1000;
		osDelayUntil(tick); /** waits until an absolute time (1000 kernel ticks) is reached **/
		
		for(ix=0; ix < LED_GRID_NBR_MAX; ix++) {
			seg_led.buf[ix] = seg_code[(start_ix+ix)%sc_sz];
		}
		
		start_ix ++;
		if(start_ix >= sc_sz) {
			start_ix = 0;
		}
		
		ledRefresh(&seg_led);
	}
}

static void
_sysConfig(void)
{
    /* configure systick */
	SystemCoreClockUpdate();

	/** led init **/
	led1.gpio_clk = RCU_GPIOA;
	led1.gpio_port = GPIOA;
	led1.pin = GPIO_PIN_11;
	ledInit(&led1);
	
	/** spi led init **/
	spiLedInit(&seg_led);
}