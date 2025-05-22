#include "gd32f470i_eval.h"

#include "User_COM.h"

static uint32_t EVAL_COM[COMn] = {EVAL_COM0};

static rcu_periph_enum EVAL_COM_CLK[COMn] = {EVAL_COM0_CLK};
static rcu_periph_enum EVAL_COM_GPIO_CLK[COMn] = {EVAL_COM0_GPIO_CLK};

static uint32_t EVAL_COM_PORT[COMn] = {EVAL_COM0_GPIO_PORT};
static uint32_t EVAL_COM_TX_PIN[COMn] = {EVAL_COM0_TX_PIN};
static uint32_t EVAL_COM_RX_PIN[COMn] = {EVAL_COM0_RX_PIN};

static uint32_t EVAL_COM_AF[COMn] = {EVAL_COM0_AF};

void com_init(com_typedef_enum com_num)
{
	rcu_periph_clock_enable(EVAL_COM_CLK[com_num]);
	rcu_periph_clock_enable(EVAL_COM_GPIO_CLK[com_num]);

	gpio_af_set(EVAL_COM_PORT[com_num], EVAL_COM_AF[com_num], EVAL_COM_TX_PIN[com_num]);
	gpio_af_set(EVAL_COM_PORT[com_num], EVAL_COM_AF[com_num], EVAL_COM_RX_PIN[com_num]);

	gpio_mode_set(EVAL_COM_PORT[com_num], GPIO_MODE_AF, GPIO_PUPD_PULLUP, EVAL_COM_TX_PIN[com_num]);
	gpio_output_options_set(EVAL_COM_PORT[com_num], GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, EVAL_COM_TX_PIN[com_num]);

	gpio_mode_set(EVAL_COM_PORT[com_num], GPIO_MODE_AF, GPIO_PUPD_PULLUP, EVAL_COM_RX_PIN[com_num]);
	gpio_output_options_set(EVAL_COM_PORT[com_num], GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, EVAL_COM_RX_PIN[com_num]);

	usart_deinit(EVAL_COM[com_num]);
	usart_baudrate_set(EVAL_COM[com_num], 115200U);
	usart_receive_config(EVAL_COM[com_num], USART_RECEIVE_ENABLE);
	usart_transmit_config(EVAL_COM[com_num], USART_TRANSMIT_ENABLE);
	usart_enable(EVAL_COM[com_num]);
}
