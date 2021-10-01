#ifndef __SPI_LED_H
#define __SPI_LED_H
#include "gd32e23x.h"
#include "led_def.h"

typedef struct {
	uint8_t buf[LED_GRID_NBR_MAX];
	uint8_t hidden;
} SegLed;

void spiLedInit(SegLed *seg_led);
void ledRefresh(SegLed *seg_led);

#endif
