#ifndef __TEST_H
#define __TEST_H
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"

#include "led.h"
#include "spi_led.h"
#include "utility.h"

extern Led led1;
extern SegLed seg_led;

void sysConfig(void);
void menuShow(SegLed *seg_led, int32_t data, uint8_t dp);

void testDelay(void);
void testThreadFlags(void);
void testEventFlags(void);
void testTimer(void);
void testMutex(void);
void testSemaphore(void);
void testMsgQueue(void);

#endif
