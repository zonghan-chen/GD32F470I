#include <stdio.h>

#include "gd32f4xx.h"
#include "gd32f470i_eval.h"

#include "main.h"
#include "systick.h"

#include "..\User\User_LED\User_LED.h"
#include "..\User\User_Key\User_Key.h"
#include "..\User\User_COM\User_COM.h"

int main(void)
{
	systick_config();

	com_init(COM0);

	key_init(KEY_TAMPER, KEY_MODE_GPIO);

	led123_init();
	led123_flash_for_test(3);

	printf("\r\n USART printf example: please press the Tamper key \r\n");

	while (usart_flag_get(EVAL_COM0, USART_FLAG_TC) == RESET)
	{
	}

	uint8_t last_key_state = SET;
	uint8_t current_key_state;

	while (1)
	{
		current_key_state = key_state_get(KEY_TAMPER);

		if (last_key_state == SET && current_key_state == RESET)
		{
			led_on(LED3);

			printf("\r\n USART printf example \r\n");

			while (usart_flag_get(EVAL_COM0, USART_FLAG_TC) == RESET)
			{
			}

			led_off(LED3);
		}

		last_key_state = current_key_state;
	}
}

// retarget the C library printf function to the USART
int fputc(int ch, FILE *f)
{
	usart_data_transmit(EVAL_COM0, (uint8_t)ch);

	while (usart_flag_get(EVAL_COM0, USART_FLAG_TBE) == RESET)
	{
	}

	return ch;
}
