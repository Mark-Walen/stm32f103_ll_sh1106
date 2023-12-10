#include "stdio.h"
#include "dma.h"

/*********************************************************************
 * @fn      DMA_Tx_Init
 *
 * @brief   Initializes the DMAy Channelx configuration.
 *
 * @param   DMA_CHx - x can be 1 to 7.
 *          ppadr - Peripheral base address.
 *          memadr - Memory base address.
 *          bufsize - DMA channel buffer size.
 *
 * @return  none
 */
void SPI1_DMA_Tx_Init( DMA_Channel_TypeDef *DMAy_Channelx, uint32_t ppadr, uint32_t memadr, uint16_t buffer_size)
{
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_DMA1, ENABLE );

    DMA_DeInit( DMAy_Channelx );

    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr; 	//SPI 数据寄存器地址
	DMA_InitStructure.DMA_MemoryBaseAddr = memadr;   	//内存地址(要传输的变量的指针)
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	//方向(从内存到外设)
	DMA_InitStructure.DMA_BufferSize = buffer_size;		//传输内容的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 	// 外设地址不增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 	//内存地址自增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte ; //外设数据单位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte ; 		//内存数据单位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; 						//DMA模式：一次传输
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium ; 					//优先级：高
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;							//禁止内存到内存的传输
	 
	DMA_Init(DMAy_Channelx, &DMA_InitStructure); 		//配置DMA1的3通道
	DMA_Cmd(DMAy_Channelx, ENABLE);       				//使能DMA
}

/*********************************************************************
 * @fn      DMA_Rx_Init
 *
 * @brief   Initializes the SPI1 DMA Channelx configuration.
 *
 * @param   DMA_CHx - x can be 1 to 7.
 *          ppadr - Peripheral base address.
 *          memadr - Memory base address.
 *          bufsize - DMA channel buffer size.
 *
 * @return  none
 */
void SPI1_DMA_Rx_Init(DMA_Channel_TypeDef *DMAy_Channelx, uint32_t ppadr, uint32_t memadr, uint16_t buffer_size)
{
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMAy_Channelx);

    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr; 	//SPI 数据寄存器地址
	DMA_InitStructure.DMA_MemoryBaseAddr = memadr;   	//内存地址(要传输的变量的指针)
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	//方向(从外设到内存)
	DMA_InitStructure.DMA_BufferSize = buffer_size;		//传输内容的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 	// 外设地址不增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 	//内存地址自增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte ; //外设数据单位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 		//内存数据单位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 						//DMA模式：一次传输
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium ; 					//优先级：高
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;							//禁止内存到内存的传输
	 
	DMA_Init(DMAy_Channelx, &DMA_InitStructure); 		//配置DMA1的3通道
	DMA_Cmd(DMAy_Channelx, ENABLE);       				//使能DMA
}

int SPI1_DMA_Send_Buffer(DMA_Channel_TypeDef *DMAy_Channelx, uint32_t DMAy_FLAG_TCx, uint32_t ppadr, uint32_t memadr, uint16_t buffer_size)
{
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
	DMA_Cmd(DMAy_Channelx, DISABLE); //失能DMA，使得DMA_SetCurrDataCounter能够使用
	SPI1_DMA_Tx_Init(DMAy_Channelx, ppadr, memadr, buffer_size);
	while (DMA_GetFlagStatus(DMAy_FLAG_TCx) == RESET); //检查指定的 SPI标志位设置与否:发送缓存空标志位
	DMA_ClearFlag(DMAy_FLAG_TCx);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
	return 0;
}
