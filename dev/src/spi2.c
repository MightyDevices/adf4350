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
#include <util/bn.h>
#include <util/size.h>

#define DEBUG
#include <dev/debug.h>

/* resource sem */
sem_t spi2_sem;
/* current callback */
static cb_t callback;

/* dma interrupt */
void SPI2_DMA1Ch5Isr(void)
{
	/* clear flag */
	DMA1->IFCR = DMA_IFCR_CGIF5;
	/* disable dma transfer */
	SPI2->CR2 = 0;

	/* wait for txe */
	while (STM32_BB(&SPI2->SR, BN(SPI_SR_TXE)) == 0);
	/* wait for bsy */
	while (STM32_BB(&SPI2->SR, BN(SPI_SR_BSY)) != 0);

	/* call callback if not empty or null */
	if (callback != CB_NULL) {
		callback(0);
	/* change the address to notify sync caller that operation has ended */
	} else {
		callback = CB_NONE;
	}
}

/* initialize spi1 */
int SPI2_Init(void)
{
	/* disable interrupts to ensure atomicity of register access */
	Critical_Enter();

	/* enable gpios */
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN | RCC_AHBENR_DMA1EN;
	/* enable spi2 */
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

	/* reset spi */
	RCC->APB1RSTR |= RCC_APB1RSTR_SPI2RST;
	/* clear reset */
	RCC->APB1RSTR &= ~RCC_APB1RSTR_SPI2RST;

	/* reset moder */
	GPIOB->MODER &= ~(GPIO_MODER_MODER13 | GPIO_MODER_MODER15);
	/* set max speed */
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13 | GPIO_OSPEEDER_OSPEEDR15;
	/* select spi function */
	GPIOB->AFRH |= 5 << (5*4) | 5 << (7*4);
	/* apply function */
	GPIOB->MODER |= GPIO_MODER_MODER13_1 | GPIO_MODER_MODER15_1;

	/* configure spi: csem phase, polarity, cs control, master mode */
	SPI2->CR1 = SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_MSTR | SPI_CR1_SPE;
	/* enable peripheral */
	SPI2->CR1 |= SPI_CR1_SPE;

	/* peripheral address for transmit dma */
	DMA1C5->CPAR = (uint32_t)&SPI2->DR;
	/* fill dma config register */
	DMA1C5->CCR = DMA_CCR_DIR | DMA_CCR_MINC | DMA_CCR_TCIE;

	/* set dma interrupt priority */
	NVIC_SETINTPRI(STM32_INT_DMA1_CH5, 0x50);
	/* enable interrupt */
	NVIC_ENABLEINT(STM32_INT_DMA1_CH5);

	/* reset sem */
	Sem_Release(&spi2_sem);
	/* restore interrupts */
	Critical_Exit();
	/* report status */
	return EOK;
}

/* initiate xfer */
int SPI2_Send(const void *ptr, size_t size, cb_t cb)
{
	/* result code, sync or async call? */
	int rc = size, sync = cb == CB_NULL;
	/* store callback information */
	callback = cb;

	/* disable dma */
	DMA1C5->CCR &= ~DMA_CCR_EN;
	/* set addresses */
	DMA1C5->CMAR = (uint32_t)ptr;
	/* set data count */
	DMA1C5->CNDTR = size;
	/* enable dma */
	DMA1C5->CCR |= DMA_CCR_EN;

	/* enable dma transfer */
	SPI2->CR2 = SPI_CR2_TXDMAEN;

	/* sync call? */
	while (sync && callback == CB_NULL);

	/* report status */
	return rc;
}
