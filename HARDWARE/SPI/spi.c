#include <stdio.h>
#include <stddef.h>
#include "spi.h"
#include "delay.h"

static void spi1_master_gpio_init(uint8_t duplex)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(SPI1_RCC_APB2_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = SPI1_SCLK_PIN|SPI1_MOSI_PIN;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		// 复用输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// 速度50MHz
	GPIO_Init(SPI1_SCLK_PORT, &GPIO_InitStructure);	  		// 初始化GPIOA5,7
	GPIO_SetBits(SPI1_SCLK_PORT, SPI1_SCLK_PIN|SPI1_MOSI_PIN);  			// PA5/PA7上拉
	
	GPIO_InitStructure.GPIO_Pin = SPI1_MISO_PIN;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 			// 浮空输入
	if (duplex)
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	else
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 	GPIO_Init(SPI1_MISO_PORT, &GPIO_InitStructure);	  		// 初始化GPIOA6
	
	GPIO_InitStructure.GPIO_Pin = SPI1_NSS_PIN;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		// 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// 速度50MHz
 	GPIO_Init(SPI1_NSS_PORT, &GPIO_InitStructure);	  		// 初始化GPIOA4
	
	GPIO_SetBits(SPI1_NSS_PORT, SPI1_NSS_PIN);
}

static void spi2_master_gpio_init(uint8_t duplex)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(SPI2_RCC_APB1_CLK, ENABLE);
 	RCC_APB2PeriphClockCmd(SPI2_RCC_APB2_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = SPI2_SCLK_PIN|SPI2_MOSI_PIN;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		// 复用输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// 速度50MHz
	GPIO_Init(SPI2_SCLK_PORT, &GPIO_InitStructure);	  		// 初始化GPIOA5,7
	
	GPIO_InitStructure.GPIO_Pin = SPI2_MISO_PIN;
	if (duplex)
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 			// 浮空输入
	}
	else
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// 速度50MHz
 	GPIO_Init(SPI2_MISO_PORT, &GPIO_InitStructure);	  		// 初始化GPIOA6
	
	GPIO_InitStructure.GPIO_Pin = SPI2_NSS_PIN;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		// 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// 速度50MHz
 	GPIO_Init(SPI2_NSS_PORT, &GPIO_InitStructure);	  		// 初始化GPIOA4
	GPIO_SetBits(SPI2_SCLK_PORT, SPI2_SCLK_PIN|SPI2_MOSI_PIN); // PA5/PA7上拉
	GPIO_SetBits(SPI2_NSS_PORT, SPI2_NSS_PIN);
}

void spi_master_init(SPI_TypeDef *SPIx, uint8_t duplex)
{
	SPI_InitTypeDef SPI_InitStructure;
	if(SPIx == SPI1)
		spi1_master_gpio_init(duplex);
	else
		spi2_master_gpio_init(duplex);
	
	if (!duplex)
	{
		SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx; //设置 SPI 单线只发送
	}
	else
	{
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	}
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //主 SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; // SPI 发送接收 8 位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;//串行同步时钟的空闲状态为低电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;//第1个跳变沿数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //NSS 主机片选信号(CS)由软件控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; //预分频 256
	//SPI 速度设置函数（调整传输速度快慢 只有4个分频可选）
	//SPI_BaudRatePrescaler_2 2 分频 (SPI 36M@sys 72M)
	//SPI_BaudRatePrescaler_8 8 分频 (SPI 9M@sys 72M)
	//SPI_BaudRatePrescaler_16 16 分频 (SPI 4.5M@sys 72M)
	//SPI_BaudRatePrescaler_256 256 分频 (SPI 281.25K@sys 72M)
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //数据传输从 MSB 高位开始 低位为LSB
	SPI_InitStructure.SPI_CRCPolynomial = 7; //CRC 值计算的多项式
	SPI_Init(SPIx, &SPI_InitStructure); //根据指定的参数初始化外设 SPIx 寄存器
	
	SPI_Cmd(SPIx, ENABLE); //使能 SPI 外设
}

int8_t spi_master_write_byte(SPI_TypeDef *SPIx, uint8_t tx_data)
{
	uint8_t retry = 0;
	
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) //检查指定的 SPI标志位设置与否:发送缓存空标志位
	{
		retry++;
		if(retry>200) return SPI_E_COM_FAIL;
	}
	retry = 0;
	SPI_I2S_SendData(SPIx, tx_data); //通过外设 SPIx 发送一个数据
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET) {
		retry++;
		if(retry>200) return SPI_E_COM_FAIL;
	}
	return SPI_OK;
}

int8_t spi_master_read_write_byte(SPI_TypeDef *SPIx, uint8_t *data)
{
	uint8_t retry = 0;
	
	if (spi_master_write_byte(SPIx, *data) < 0)
		return SPI_E_COM_FAIL;
	
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
	{
		retry++;
		if(retry > 200)return SPI_E_COM_FAIL;
	}
	*data = SPI_I2S_ReceiveData(SPIx);
	
	return SPI_OK;
}

int spi_master_write_buffer(uint8_t *tx_data, uint32_t len, void *fp, void *addr)
{
	(void) addr;
	SPI_TypeDef *SPIx = (SPI_TypeDef *) fp;
	
	if(tx_data == NULL)
		return SPI_E_NULLPTR;
	
	for (uint32_t i = 0; i < len; i++)
	{
		if (spi_master_write_byte(SPIx, tx_data[i]) < 0)
			return SPI_E_COM_FAIL;
	}
	return SPI_OK;
}

int spi_master_read_buffer(uint8_t *rx_data, uint32_t len, void *fp, void *addr)
{
	(void) addr;
	SPI_TypeDef *SPIx = (SPI_TypeDef *) fp;
	
	if(rx_data == NULL)
		return SPI_E_NULLPTR;
	
	for (uint32_t i = 0; i < len; i++)
	{
		if (spi_master_read_write_byte(SPIx, &rx_data[i]) < 0)
			return SPI_E_COM_FAIL;
	}
	
	return SPI_OK;
}
