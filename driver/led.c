
#include "led.h"


int ledInit(Led *led)
{
    /* enable the GPIO clock */
    rcu_periph_clock_enable(led->gpio_clk);
    /* configure GPIO port */ 
    gpio_mode_set(led->gpio_port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, led->pin);
    gpio_output_options_set(led->gpio_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, led->pin);
    /* reset GPIO pin */
    gpio_bit_reset(led->gpio_port, led->pin);
	
	led->timing = 0;
	
	if(!led->time_on_ms) {
		led->time_on_ms = 100;
	}
	
	if(!led->time_total_ms) {
		led->time_total_ms = 1500;
	}
	
	return 0;
}

int ledOn(Led *led)
{
	gpio_bit_set(led->gpio_port, led->pin);
	return 0;
}

int ledOff(Led *led)
{
	gpio_bit_reset(led->gpio_port, led->pin);
	return 0;
}

int ledToggle(Led *led)
{
	GPIO_TG(led->gpio_port) = led->pin;
	return 0;
}

void ledBlink(Led *led)
{
	led->timing ++;
	
	if(led->timing == led->time_on_ms) {
		ledOff(led);
	} else if(led->timing == led->time_total_ms) {
		ledOn(led);
		led->timing = 0;
	}
}