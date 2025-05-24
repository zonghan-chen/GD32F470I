#include <stdio.h>

#include "gd32f4xx.h"
#include "gd32f470i_eval.h"

#include "main.h"
#include "systick.h"

#include "..\User\User_COM\User_COM.h"

static void rcu_config(void);
static void gpio_config(void);

static void adc_config(void);
static void dma_config(void);
static void timer_config(void);

uint32_t adc_value[2];

int main(void)
{
	systick_config();

	com_init(COM0);

	// Configure RCU and GPIO
	rcu_config();
	gpio_config();

	// Configure peripheral
	adc_config();
	dma_config();
	timer_config();

	while (1)
	{
		delay_1ms(2000);

		printf("The data adc_value[0] is %08X\r\n", adc_value[0]);
		printf("The data adc_value[1] is %08X\r\n", adc_value[1]);
		printf("\r\n");
	}
}

static void rcu_config(void)
{
	// GPIOC
	rcu_periph_clock_enable(RCU_GPIOC);

	// ADC
	rcu_periph_clock_enable(RCU_ADC0);
	rcu_periph_clock_enable(RCU_ADC1);
	adc_clock_config(ADC_ADCCK_PCLK2_DIV8);

	// DMA
	rcu_periph_clock_enable(RCU_DMA1);

	// Timer
	rcu_periph_clock_enable(RCU_TIMER1);
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
}

static void gpio_config(void)
{
	gpio_mode_set(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_3);
	gpio_mode_set(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_5);
}

static void adc_config(void)
{
	// Configure ADC synchronization mode
	adc_sync_mode_config(ADC_DAUL_ROUTINE_FOLLOW_UP); // ADC0 and ADC1 work in follow-up mode & ADC2 works independently

	adc_sync_dma_config(ADC_SYNC_DMA_MODE1);
	adc_sync_dma_request_after_last_enable();

	// Configure ADC data alignment
	adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);
	adc_data_alignment_config(ADC1, ADC_DATAALIGN_RIGHT);

	// Configure ADC scan mode function
	adc_special_function_config(ADC0, ADC_SCAN_MODE, ENABLE);
	adc_special_function_config(ADC1, ADC_SCAN_MODE, ENABLE);

	// Configure ADC channel length
	adc_channel_length_config(ADC0, ADC_ROUTINE_CHANNEL, 2);
	adc_channel_length_config(ADC1, ADC_ROUTINE_CHANNEL, 2);

	// Configure ADC routine channel
	adc_routine_channel_config(ADC0, 0, ADC_CHANNEL_13, ADC_SAMPLETIME_480);
	adc_routine_channel_config(ADC0, 1, ADC_CHANNEL_15, ADC_SAMPLETIME_480);

	adc_routine_channel_config(ADC1, 0, ADC_CHANNEL_15, ADC_SAMPLETIME_480);
	adc_routine_channel_config(ADC1, 1, ADC_CHANNEL_13, ADC_SAMPLETIME_480);

	// Configure ADC external trigger
	adc_external_trigger_config(ADC0, ADC_ROUTINE_CHANNEL, EXTERNAL_TRIGGER_RISING);
	adc_external_trigger_config(ADC1, ADC_ROUTINE_CHANNEL, EXTERNAL_TRIGGER_DISABLE);
	adc_external_trigger_source_config(ADC0, ADC_ROUTINE_CHANNEL, ADC_EXTTRIG_ROUTINE_T1_CH1);

	// Enable ADC interface
	adc_enable(ADC0);
	adc_enable(ADC1);

	// Enable ADC calibration and reset calibration
	adc_calibration_enable(ADC0);
	adc_calibration_enable(ADC1);
}

static void dma_config(void)
{
	dma_single_data_parameter_struct dma_single_data_struct;

	dma_deinit(DMA1, DMA_CH0); // PERIEN[2:0]==000 ADC0

	// Configure DMA single data parameter struct
	dma_single_data_struct.periph_addr = (uint32_t)(&ADC_SYNCDATA);
	dma_single_data_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_single_data_struct.memory0_addr = (uint32_t)adc_value;
	dma_single_data_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_single_data_struct.periph_memory_width = DMA_PERIPH_WIDTH_32BIT;
	dma_single_data_struct.circular_mode = DMA_CIRCULAR_MODE_ENABLE;
	dma_single_data_struct.direction = DMA_PERIPH_TO_MEMORY;
	dma_single_data_struct.number = 2;
	dma_single_data_struct.priority = DMA_PRIORITY_HIGH;

	dma_single_data_mode_init(DMA1, DMA_CH0, &dma_single_data_struct);

	// Select DMA channel 0 subperipheral
	dma_channel_subperipheral_select(DMA1, DMA_CH0, DMA_SUBPERI0);

	// Enable DMA channel 0
	dma_channel_enable(DMA1, DMA_CH0);
}

static void timer_config(void)
{
	timer_parameter_struct timer_struct;
	timer_oc_parameter_struct timer_oc_struct;

	// Configure TIMER 1
	timer_struct.prescaler = 20000 - 1;
	timer_struct.alignedmode = TIMER_COUNTER_EDGE;
	timer_struct.counterdirection = TIMER_COUNTER_UP;
	timer_struct.clockdivision = TIMER_CKDIV_DIV1;
	timer_struct.period = 10000 - 1;
	timer_struct.repetitioncounter = 0;

	timer_init(TIMER1, &timer_struct);

	// Configure TIMER 1 channel 1 in PWM mode 0
	timer_oc_struct.outputstate = TIMER_CCX_ENABLE;
	timer_oc_struct.outputnstate = TIMER_CCXN_DISABLE;
	timer_oc_struct.ocpolarity = TIMER_OC_POLARITY_HIGH;
	timer_oc_struct.ocnpolarity = TIMER_OCN_POLARITY_HIGH;
	timer_oc_struct.ocidlestate = TIMER_OC_IDLE_STATE_LOW;
	timer_oc_struct.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

	timer_channel_output_config(TIMER1, TIMER_CH_1, &timer_oc_struct);

	timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, 3999);
	timer_channel_output_mode_config(TIMER1, TIMER_CH_1, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER1, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);

	// Enable TIMER 1
	timer_enable(TIMER1);
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
