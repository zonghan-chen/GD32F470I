#include <stdio.h>

#include "gd32f4xx.h"
#include "gd32f470i_eval.h"

#include "main.h"
#include "systick.h"

#include "..\User\User_LED\User_LED.h"
#include "..\User\User_Key\User_Key.h"

int main(void)
{
	// Initialize LED
	led_init(LED1);
	led_init(LED2);

	// Initialize key
	key_init(KEY_TAMPER, KEY_MODE_EXTI);

	// Turn on LED1
	led_on(LED1);

	while (1)
	{
	}
}
