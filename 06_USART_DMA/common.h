#ifndef COMMON_H
#define COMMON_H

#include "gd32f4xx.h"

// 06_USART_DMA
#define ARRAY_SIZE(array_name) (uint32_t)(sizeof(array_name) / sizeof(*(array_name)))

extern uint8_t tx_buffer[];
extern uint8_t rx_buffer[];

extern const uint16_t BUFFER_SIZE;

#endif
