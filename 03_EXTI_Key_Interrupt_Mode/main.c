#include <stdio.h>

#include "gd32f4xx.h"
#include "gd32f470i_eval.h"

#include "main.h"
#include "systick.h"

#include "..\User\User_LED\User_LED.h"
#include "..\User\User_Key\User_Key.h"

static void led2_flash_for_test(uint8_t flash_time);

int main(void)
{
	systick_config();

	led_init(LED2);
	key_init(KEY_TAMPER, KEY_MODE_EXTI);

	led2_flash_for_test(1);

	while (1)
	{
	}
}

static void led2_flash_for_test(uint8_t flash_time)
{
	uint8_t time_cnt;
	for (time_cnt = 0; time_cnt < flash_time; time_cnt++)
	{
		delay_1ms(500);
		led_on(LED2);

		delay_1ms(500);
		led_off(LED2);
	}
}
