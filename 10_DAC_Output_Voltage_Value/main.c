#include <stdio.h>

#include "gd32f4xx.h"
#include "gd32f470i_eval.h"

#include "main.h"
#include "systick.h"

#include "..\User\User_LED\User_LED.h"

static void rcu_config(void);
static void gpio_config(void);

static void dac_config(void);

int main(void)
{
	systick_config();

	// Configure RCU and GPIO
	rcu_config();
	gpio_config();

	// Configure DAC peripheral
	dac_config();

	led123_init();
	led123_flash(3);

	while (1)
	{
	}
}

static void rcu_config(void)
{
	// GPIOA
	rcu_periph_clock_enable(RCU_GPIOA);

	// DAC
	rcu_periph_clock_enable(RCU_DAC);
}

static void gpio_config(void)
{
	gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_4);
}

static void dac_config(void)
{
	// Deinitialize DAC peripheral
	dac_deinit(DAC0);

	// Disable DAC trigger
	dac_trigger_disable(DAC0, DAC_OUT0);

	// Configure DAC wave mode
	dac_wave_mode_config(DAC0, DAC_OUT0, DAC_WAVE_DISABLE);

	// Enable DAC output buffer
	dac_output_buffer_enable(DAC0, DAC_OUT0);

	// Enable DAC peripheral
	dac_enable(DAC0, DAC_OUT0);

	// Set DAC data holding register value
	dac_data_set(DAC0, DAC_OUT0, DAC_ALIGN_12B_L, 0x7FF0);
}
