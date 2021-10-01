#ifndef __LED_H
#define __LED_H
#include "gd32e23x.h"
#include "gd32e23x_rcu.h"

typedef struct {
	rcu_periph_enum gpio_clk;
	uint32_t gpio_port;
	uint32_t pin;
	
	uint32_t timing;
	uint32_t time_on_ms;
	uint32_t time_total_ms;
} Led;


int ledInit(Led *led);
int ledOn(Led *led);
int ledOff(Led *led);
int ledToggle(Led *led);
void ledBlink(Led *led);
#endif
