#include <stdio.h>

#include "gd32f4xx.h"
#include "gd32f470i_eval.h"

#include "main.h"
#include "systick.h"

#include "..\User\User_LED\User_LED.h"
#include "..\User\User_Key\User_Key.h"

int main(void)
{
	// Initialize the system tick timer
	systick_config();

	// Initialize GPIO
	led_init(LED1);
	key_init(KEY_TAMPER, KEY_MODE_GPIO);

	uint8_t last_key_state = SET;
	uint8_t current_key_state;

	// Switch light
	while (1)
	{
		current_key_state = key_state_get(KEY_TAMPER);

		if (last_key_state == SET && current_key_state == RESET)
		{
			led_toggle(LED1);
		}

		last_key_state = current_key_state;
	}
}
