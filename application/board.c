
#include <math.h>
#include "test.h"

Led led1;
SegLed seg_led;

static void _fixedToSegCode(uint8_t *seg, int32_t data, uint8_t dp);

void
sysConfig(void)
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

void
menuShow(SegLed *seg_led, int32_t data, uint8_t dp)
{
	_fixedToSegCode(seg_led->buf, data, dp);
	ledRefresh(seg_led);
}

static void
_fixedToSegCode(uint8_t *seg, int32_t data, uint8_t dp)
{
	uint8_t ix;
	uint32_t div;
	uint8_t neg;
	uint8_t _d;
	uint8_t nz; /** none zero flag **/
	
	if(data < 0) {
		neg = 1;
		data = -data;
	} else {
		neg = 0;
	}
	
	ix = 0;
	nz = 0;
	div = pow(10, LED_GRID_NBR-1);
	while(div >= 1) {
		_d = data / div % 10;
		/** 显示除数值前面的无效零之外的所有数字 **/
		if(!((0==_d) && (0==nz) && (dp<(LED_GRID_NBR-ix-1)))) {
			seg[ix] = seg_code_tbl[_d];
			nz = 1;
		} else {
			seg[ix] = DEF_LED_NONE;
		}
		
		div /= 10;
		ix ++;
	}
	
	/** 显示负号 **/
	if(neg) {
		seg[0] |= DEF_LED_N;
	}
	
	/** 显示小数点 **/
	if(dp) {
		seg[LED_GRID_NBR-1-dp] |= DEF_LED_DP;
	}
}
