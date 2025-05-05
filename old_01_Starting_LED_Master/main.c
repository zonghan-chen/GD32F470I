#include <stdio.h>

#include "gd32f4xx.h"
#include "gd32f470i_eval.h"

#include "main.h"
#include "systick.h"

#include "..\User\User_LED\User_LED.h"

int main(void)
{
	// Initialize the system tick timer
	systick_config();

	// Initialize GPIO
	led_init(LED1);
	led_init(LED2);
	led_init(LED3);

	// Light (Effect: LED1, LED2 and LED3 turn on for 1 second + turn off for 1 second)
	while (1)
	{
		// LED1
		led_on(LED1);
		delay_1ms(1000);
		led_off(LED1);
		delay_1ms(1000);

		// LED2
		led_on(LED2);
		delay_1ms(1000);
		led_off(LED2);
		delay_1ms(1000);

		// LED3
		led_on(LED3);
		delay_1ms(1000);
		led_off(LED3);
		delay_1ms(1000);
	}
}
