#include <stdio.h>

#include "gd32f4xx.h"
#include "gd32f470i_eval.h"
#include "peripheral.h"
#include "common.h"

#include "main.h"
#include "systick.h"

__IO ErrStatus transfer_status = ERROR;

// Compare transmission buffer and reception buffer
static ErrStatus memory_compare(uint8_t *src, uint8_t *dst, uint16_t length);

int main(void)
{
	systick_config();

	com_init(COM0);

	// Configure USART DMA
	usart_dma_config();

	// Enable USART0 DMA transmission channel and reception channel
	dma_channel_enable(DMA1, DMA_CH7);
	dma_channel_enable(DMA1, DMA_CH2);

	// Enable USART0 DMA for transmission and reception
	usart_dma_transmit_config(USART0, USART_TRANSMIT_DMA_ENABLE);
	usart_dma_receive_config(USART0, USART_RECEIVE_DMA_ENABLE);

	led123_init();
	led123_flash(3);

	while (dma_flag_get(DMA1, DMA_CH7, DMA_INTF_FTFIF) == RESET)
	{
	}

	while (dma_flag_get(DMA1, DMA_CH2, DMA_INTF_FTFIF) == RESET)
	{
	}

	transfer_status = memory_compare(tx_buffer, rx_buffer, BUFFER_SIZE);

	while (1)
	{
		if (transfer_status == SUCCESS)
		{
			led_on(LED1);
			delay_1ms(500);

			led_on(LED2);
			delay_1ms(500);

			led_on(LED3);
			delay_1ms(500);

			led_off(LED1);
			led_off(LED2);
			led_off(LED3);
			delay_1ms(500);
		}
		else
		{
			led123_flash(3);
		}
	}
}

static ErrStatus memory_compare(uint8_t *src, uint8_t *dst, uint16_t length)
{
	while (length--)
	{
		if (*src++ != *dst++)
		{
			return ERROR;
		}
	}

	return SUCCESS;
}
