#include "gd32f470i_eval.h"

#include "User_LED.h"

static rcu_periph_enum GPIO_CLK[LEDn] = {LED1_GPIO_CLK, LED2_GPIO_CLK, LED3_GPIO_CLK};
static uint32_t GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT, LED3_GPIO_PORT};
static uint32_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN};

void led_init(led_typedef_enum lednum)
{
	// Initialize the clock
	rcu_periph_clock_enable(GPIO_CLK[lednum]);

	// Configure the input/output mode of GPIO
	gpio_mode_set(GPIO_PORT[lednum], GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN[lednum]);

	// Set the GPIO output mode and speed
	gpio_output_options_set(GPIO_PORT[lednum], GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, GPIO_PIN[lednum]);
}

void led_on(led_typedef_enum lednum)
{
	gpio_bit_set(GPIO_PORT[lednum], GPIO_PIN[lednum]); // Output high level
}

void led_off(led_typedef_enum lednum)
{
	gpio_bit_reset(GPIO_PORT[lednum], GPIO_PIN[lednum]); // Output low level
}
