#ifndef USER_LED_H
#define USER_LED_H

#include "gd32f4xx.h"

#include "systick.h"

typedef enum
{
	LED1 = 0,
	LED2 = 1,
	LED3 = 2
} led_typedef_enum;

void led_init(led_typedef_enum lednum);
void led_on(led_typedef_enum lednum);
void led_off(led_typedef_enum lednum);
void led_toggle(led_typedef_enum lednum);

void led123_init(void);
void led123_flash_for_test(uint8_t flash_times);

#endif
