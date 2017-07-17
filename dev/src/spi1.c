/*
 * spi1.c
 *
 *  Created on: 29.06.2017
 *      Author: Tomek
 */


#include <stm32l151/rcc.h>
#include <stm32l151/nvic.h>
#include <stm32l151/gpio.h>
#include <stm32l151/spi.h>
#include <stm32l151/dma.h>
#include <sys/cb.h>
#include <sys/critical.h>
#include <sys/err.h>
#include <sys/sem.h>
#include <util/size.h>

#define DEBUG
#include <dev/debug.h>

/* resource sem */
sem_t spi1_sem;
/* current callback */
static cb_t callback;

/* dma interrupt */
void SPI1_DMA1Ch2Isr(void)
{
	/* clear flag */
	DMA1->IFCR = DMA_IFCR_CGIF2;
	/* disable dma transfer */
	SPI1->CR2 = 0;

	/* call callback if not empty or null */
	if (callback != CB_NULL) {
		callback(0);
	/* change the address to notify sync caller that operation has ended */
	} else {
		callback = CB_NONE;
	}
}

/* initialize spi1 */
int SPI1_Init(void)
{
	/* disable interrupts to ensure atomicity of register access */
	Critical_Enter();

	/* enable gpios */
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_DMA1EN;
	/* enable spi1 */
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	/* reset spi */
	RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;
	/* clear reset */
	RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST;

	/* reset moder */
	GPIOA->MODER &= ~(GPIO_MODER_MODER5 | GPIO_MODER_MODER6 | GPIO_MODER_MODER7);
	/* set max speed */
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5 | GPIO_OSPEEDER_OSPEEDR6 |
			GPIO_OSPEEDER_OSPEEDR7;
	/* select spi function */
	GPIOA->AFRL |= 5 << (5*4) | 5 << (6*4) | 5 << (7*4);
	/* set up pull down on miso line */
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR6_1;
	/* apply function */
	GPIOA->MODER |= GPIO_MODER_MODER5_1 | GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1;

	/* configure spi: csem phase, polarity, cs control, master mode */
	SPI1->CR1 = SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_MSTR | SPI_CR1_SPE;
	/* enable peripheral */
	SPI1->CR1 |= SPI_CR1_SPE;

	/* peripheral address for transmit dma */
	DMA1C3->CPAR = (uint32_t)&SPI1->DR;
	/* fill dma config register */
	DMA1C3->CCR =  DMA_CCR_DIR | DMA_CCR_MINC;

	/* peripheral address for receive dma */
	DMA1C2->CPAR = (uint32_t)&SPI1->DR;
	/* fill dma config register */
	DMA1C2->CCR =  DMA_CCR_MINC | DMA_CCR_TCIE;

	/* set dma interrupt priority */
	NVIC_SETINTPRI(STM32_INT_DMA1_CH2, 0x50);
	/* enable interrupt */
	NVIC_ENABLEINT(STM32_INT_DMA1_CH2);

	/* reset sem */
	Sem_Release(&spi1_sem);
	/* restore interrupts */
	Critical_Exit();
	/* report status */
	return EOK;
}

/* initiate xfer */
int SPI1_Xfer(void *ptr, size_t size, cb_t cb)
{
	/* result code, sync or async call? */
	int rc = size, sync = cb == CB_NULL;
	/* store callback information */
	callback = cb;

	/* disable dmas */
	DMA1C3->CCR &= ~DMA_CCR_EN; DMA1C2->CCR &= ~DMA_CCR_EN;
	/* set addresses */
	DMA1C3->CMAR = DMA1C2->CMAR = (uint32_t)ptr;
	/* set data count */
	DMA1C3->CNDTR = DMA1C2->CNDTR = size;
	/* enable both dmas */
	DMA1C3->CCR |= DMA_CCR_EN; DMA1C2->CCR |= DMA_CCR_EN;

	/* enable dma transfer */
	SPI1->CR2 = SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN;

	/* sync call? */
	while (sync && callback == CB_NULL);

	/* report status */
	return rc;
}
