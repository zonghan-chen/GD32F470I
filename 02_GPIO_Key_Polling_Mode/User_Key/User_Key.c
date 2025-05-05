#include "gd32f470i_eval.h"

#include "User_Key.h"

static rcu_periph_enum KEY_CLK[KEYn] = {WAKEUP_KEY_GPIO_CLK, TAMPER_KEY_GPIO_CLK, USER_KEY_GPIO_CLK};

static uint32_t KEY_PORT[KEYn] = {WAKEUP_KEY_GPIO_PORT, TAMPER_KEY_GPIO_PORT, USER_KEY_GPIO_PORT};
static uint32_t KEY_PIN[KEYn] = {WAKEUP_KEY_PIN, TAMPER_KEY_PIN, USER_KEY_PIN};

static exti_line_enum KEY_EXTI_LINE[KEYn] = {WAKEUP_KEY_EXTI_LINE, TAMPER_KEY_EXTI_LINE, USER_KEY_EXTI_LINE};
static uint8_t KEY_PORT_SOURCE[KEYn] = {WAKEUP_KEY_EXTI_PORT_SOURCE, TAMPER_KEY_EXTI_PORT_SOURCE, USER_KEY_EXTI_PORT_SOURCE};
static uint8_t KEY_PIN_SOURCE[KEYn] = {WAKEUP_KEY_EXTI_PIN_SOURCE, TAMPER_KEY_EXTI_PIN_SOURCE, USER_KEY_EXTI_PIN_SOURCE};
static uint8_t KEY_IRQn[KEYn] = {WAKEUP_KEY_EXTI_IRQn, TAMPER_KEY_EXTI_IRQn, USER_KEY_EXTI_IRQn};

void key_init(key_typedef_enum key_num, keymode_typedef_enum key_mode)
{
	// Initialize the clock
	rcu_periph_clock_enable(RCU_SYSCFG);
	rcu_periph_clock_enable(KEY_CLK[key_num]);

	// Configure the input/output mode of GPIO
	gpio_mode_set(KEY_PORT[key_num], GPIO_MODE_INPUT, GPIO_PUPD_NONE, KEY_PIN[key_num]);

	if (key_mode == KEY_MODE_EXTI)
	{
		// Enable interrupt and set the priority of interrupt
		nvic_irq_enable(KEY_IRQn[key_num], 2U, 0U);

		// Configure the GPIO pin as EXTI line
		syscfg_exti_line_config(KEY_PORT_SOURCE[key_num], KEY_PIN_SOURCE[key_num]);

		// Configure the key EXTI line
		exti_init(KEY_EXTI_LINE[key_num], EXTI_INTERRUPT, EXTI_TRIG_FALLING);
		exti_interrupt_flag_clear(KEY_EXTI_LINE[key_num]);
	}
}

uint8_t key_state_get(key_typedef_enum key_num)
{
	return gpio_input_bit_get(KEY_PORT[key_num], KEY_PIN[key_num]);
}
