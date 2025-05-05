#include <stdio.h>

#include "gd32f4xx.h"
#include "gd32f470i_eval.h"

#include "main.h"
#include "systick.h"

#include "..\User\User_LED\User_LED.h"
#include "..\User\User_Key\User_Key.h"
#include "..\User\User_COM\User_COM.h"

static void led123_init(void);

int main(void)
{
	systick_config();

	led123_init();

	while (1)
	{
		led_on(LED1);
		led_off(LED3);
		delay_1ms(1000);

		led_on(LED2);
		led_off(LED1);
		delay_1ms(1000);

		led_on(LED3);
		led_off(LED2);
		delay_1ms(1000);
	}
}

static void led123_init(void)
{
	led_init(LED1);
	led_init(LED2);
	led_init(LED3);
}
