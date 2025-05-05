#include "gd32f470i_eval.h"

#include "..\common.h"

#include "User_USART.h"

void usart_dma_config(void)
{
	dma_single_data_parameter_struct dma_init_struct;

	rcu_periph_clock_enable(RCU_DMA1);

	// Deinitialize DMA channel 7 (USART0 TX)
	dma_deinit(DMA1, DMA_CH7);

	dma_init_struct.periph_addr = USART0_DATA_ADDRESS;
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.memory0_addr = (uint32_t)tx_buffer;
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
	dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
	dma_init_struct.number = BUFFER_SIZE;
	dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;

	dma_single_data_mode_init(DMA1, DMA_CH7, &dma_init_struct);
	dma_channel_subperipheral_select(DMA1, DMA_CH7, DMA_SUBPERI4);
	dma_circulation_disable(DMA1, DMA_CH7);

	// Deinitialize DMA channel 2 (USART0 RX)
	dma_deinit(DMA1, DMA_CH2);

	dma_init_struct.memory0_addr = (uint32_t)rx_buffer;
	dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;

	dma_single_data_mode_init(DMA1, DMA_CH2, &dma_init_struct);
	dma_channel_subperipheral_select(DMA1, DMA_CH2, DMA_SUBPERI4);
	dma_circulation_disable(DMA1, DMA_CH2);
}
