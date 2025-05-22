#include <stdio.h>

#include "gd32f4xx.h"
#include "gd32f470i_eval.h"

#include "main.h"
#include "systick.h"

#include "..\User\User_COM\User_COM.h"

float temperature;
float reference_voltage;
float battery_voltage;

static void adc_config(void);

int main(void)
{
	systick_config();

	com_init(COM0);

	// Configure ADC peripheral
	adc_config();

	while (1)
	{
		adc_software_trigger_enable(ADC0, ADC_INSERTED_CHANNEL);

		delay_1ms(2000);

		temperature = (1.42 - ADC_IDATA0(ADC0) * 3.3 / 4096) * 1000 / 4.35 + 25;
		reference_voltage = (ADC_IDATA1(ADC0) * 3.3 / 4096);
		battery_voltage = (ADC_IDATA2(ADC0) * 4 * 3.3 / 4096);

		printf("The temperature data is %2.0f degrees Celsius\r\n", temperature);
		printf("The internal reference voltage data is %5.3fV\r\n", reference_voltage);
		printf("The external battery voltage is %5.3fV\r\n", battery_voltage);
		printf("\r\n");
	}
}

static void adc_config(void)
{
	rcu_periph_clock_enable(RCU_ADC0);
	adc_clock_config(ADC_ADCCK_PCLK2_DIV4);

	adc_channel_length_config(ADC0, ADC_INSERTED_CHANNEL, 3);

	adc_inserted_channel_config(ADC0, 0, ADC_CHANNEL_16, ADC_SAMPLETIME_480); // Configure ADC temperature sensor channel
	adc_inserted_channel_config(ADC0, 1, ADC_CHANNEL_17, ADC_SAMPLETIME_480); // Configure ADC internal reference voltage channel
	adc_inserted_channel_config(ADC0, 2, ADC_CHANNEL_18, ADC_SAMPLETIME_480); // Configure ADC external battery channel (1/4 voltate)

	// Configure ADC external trigger
	adc_external_trigger_config(ADC0, ADC_INSERTED_CHANNEL, DISABLE);

	// Configure ADC data alignment
	adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);

	// Enable ADC scan mode
	adc_special_function_config(ADC0, ADC_SCAN_MODE, ENABLE);

	adc_channel_16_to_18(ADC_VBAT_CHANNEL_SWITCH, ENABLE);		// Enable vbat battery channel
	adc_channel_16_to_18(ADC_TEMP_VREF_CHANNEL_SWITCH, ENABLE); // Enable temperature sensor and vrefint battery channel

	// Enable ADC interface
	adc_enable(ADC0);

	// ADC calibration and reset calibration
	adc_calibration_enable(ADC0);
}

// Retarget the C library printf function to the USART0
int fputc(int ch, FILE *f)
{
	usart_data_transmit(EVAL_COM0, (uint8_t)ch);

	while (usart_flag_get(EVAL_COM0, USART_FLAG_TBE) == RESET)
	{
	}

	return ch;
}
