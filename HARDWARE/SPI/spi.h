#ifndef __SPI_H__
#define __SPI_H__

#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"

#ifndef SPI1_AFIO
	#define SPI1_RCC_APB2_CLK RCC_APB2Periph_AFIO | \
							 RCC_APB2Periph_GPIOA | \
							 RCC_APB2Periph_SPI1
	
	#define SPI1_NSS_PORT GPIOA
	#define SPI1_NSS_PIN GPIO_Pin_4
	#define SPI1_SCLK_PORT GPIOA
	#define SPI1_SCLK_PIN GPIO_Pin_5
	#define SPI1_MISO_PORT GPIOA
	#define SPI1_MISO_PIN GPIO_Pin_6
	#define SPI1_MOSI_PORT GPIOA
	#define SPI1_MOSI_PIN GPIO_Pin_7
#else
	#define SPI1_RCC_APB2_CLK RCC_APB2Periph_AFIO | \
							 RCC_APB2Periph_GPIOA | \
							 RCC_APB2Periph_GPIOB | \
							 RCC_APB2Periph_SPI1
	#define SPI1_NSS_PORT GPIOA
	#define SPI1_NSS_PIN GPIO_Pin_15
	#define SPI1_SCLK_PORT GPIOB
	#define SPI1_SCLK_PIN GPIO_Pin_3
	#define SPI1_MISO_PORT GPIOB
	#define SPI1_MISO_PIN GPIO_Pin_4
	#define SPI1_MOSI_PORT GPIOB
	#define SPI1_MOSI_PIN GPIO_Pin_5
#endif

#define SPI2_RCC_APB1_CLK RCC_APB1Periph_SPI2
#define SPI2_RCC_APB2_CLK RCC_APB2Periph_AFIO | \
						 RCC_APB2Periph_GPIOB
#define SPI2_NSS_PORT GPIOB
#define SPI2_NSS_PIN GPIO_Pin_12
#define SPI2_SCLK_PORT GPIOB
#define SPI2_SCLK_PIN GPIO_Pin_13
#define SPI2_MISO_PORT GPIOB
#define SPI2_MISO_PIN GPIO_Pin_14
#define SPI2_MOSI_PORT GPIOB
#define SPI2_MOSI_PIN GPIO_Pin_15

typedef enum spi_comm_state{
	SPI_OK = 0,
	SPI_E_COM_FAIL = -1,
	SPI_E_NULLPTR = -2
} spi_comm_state_t;

void spi_master_init(SPI_TypeDef *SPIx, uint8_t duplex);

int8_t spi_master_write_byte(SPI_TypeDef *SPIx, uint8_t data);
int8_t spi_master_read_write_byte(SPI_TypeDef *SPIx, uint8_t *data);
int spi_master_write_buffer(uint8_t *tx_data, uint32_t len, void *fp, void *addr);
int spi_master_read_buffer(uint8_t *rx_data, uint32_t len, void *fp, void *addr);
#endif
