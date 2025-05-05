#include "gd32f470i_eval.h"

#include "User_Key.h"

static rcu_periph_enum KEY_CLK[KEYn] = {WAKEUP_KEY_GPIO_CLK, TAMPER_KEY_GPIO_CLK, USER_KEY_GPIO_CLK};
static uint32_t KEY_PORT[KEYn] = {WAKEUP_KEY_GPIO_PORT, TAMPER_KEY_GPIO_PORT, USER_KEY_GPIO_PORT};
static uint32_t KEY_PIN[KEYn] = {WAKEUP_KEY_PIN, TAMPER_KEY_PIN, USER_KEY_PIN};

void key_init(key_typedef_enum key_num, keymode_typedef_enum key_mode)
{
	// Initialize the clock
	rcu_periph_clock_enable(RCU_SYSCFG);
	rcu_periph_clock_enable(KEY_CLK[key_num]);

	// Configure the input/output mode of GPIO
	gpio_mode_set(KEY_PORT[key_num], GPIO_MODE_INPUT, GPIO_PUPD_NONE, KEY_PIN[key_num]);
}

uint8_t key_state_get(key_typedef_enum key_num)
{
	return gpio_input_bit_get(KEY_PORT[key_num], KEY_PIN[key_num]);
}
