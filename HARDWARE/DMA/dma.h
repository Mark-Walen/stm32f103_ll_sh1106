#ifndef __DMA_H__
#define __DMA_H__

#include "stm32f10x_dma.h"

#define SPI1_DMA_CHANL 	DMA1_Channel3
#define SPI1_DMA_FALG 	DMA1_FLAG_TC3

void SPI1_DMA_Tx_Init( DMA_Channel_TypeDef *DMAy_Channelx, uint32_t ppadr, uint32_t memadr, uint16_t buffer_size);
void SPI1_DMA_Rx_Init( DMA_Channel_TypeDef *DMAy_Channelx, uint32_t ppadr, uint32_t memadr, uint16_t buffer_size);
int SPI1_DMA_Send_Buffer(DMA_Channel_TypeDef *DMAy_Channelx, uint32_t DMAy_FLAG_TCx, uint32_t ppadr, uint32_t memadr, uint16_t buffer_size);
#endif
