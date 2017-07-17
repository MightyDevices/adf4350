/*
 * usart1.c
 *
 *  Created on: 18-06-2015
 *      Author: Tomek
 */


#include <dev/usart1.h>
#include <stm32l151/rcc.h>
#include <stm32l151/usart.h>
#include <stm32l151/gpio.h>
#include <stm32l151/dma.h>
#include <stm32l151/nvic.h>
#include <stdint.h>
#include <util/size.h>
#include <sys/cb.h>
#include <sys/err.h>
#include <sys/ev.h>
#include <sys/sem.h>
#include <sys/critical.h>

/* resource lock */
sem_t usart1_sem;
/* current callback */
static cb_t callback;

/* usart1 interrupt */
void USART1_USART1Isr(void)
{
	/* clear transfer complete */
	USART1->SR = ~USART_SR_TC;

	/* sync call */
	if (callback == CB_NULL) {
		callback = CB_NONE;
	/* async call was made? */
	} else if (callback != CB_NONE) {
		callback(0);
	}
}

/* initialize usart1 */
int USART1_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable gpioa and dma */
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_DMA1EN;
	/* enable usart1 clock */
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

	/* reset usart */
	RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
	/* disable reset */
	RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;

	/* reset moder configutration */
	GPIOA->MODER &= ~(GPIO_MODER_MODER9 | GPIO_MODER_MODER10);
	/* set both as alternate function */
	GPIOA->MODER |= GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1;
	/* reset afrh */
	GPIOA->AFRH &= ~(0xF << 4 | 0xF << 8);
	/* set alternate function to usart */
	GPIOA->AFRH |= 7 << 4 | 7 << 8;
	/* set pull-up on rxd line to avoid toggling */
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR10_0;

	/* enable oversampling and transmitter */
	USART1->CR1 = USART_CR1_OVER8 | USART_CR1_TE | USART_CR1_TCIE;
	/* configure baud rate, div = 2.25 */
	USART1->BRR = 0x22;
	/* enable dma request */
	USART1->CR3 = USART_CR3_DMAT;

	/* configure tx dma */
	DMA1C4->CCR = DMA_CCR_MINC | DMA_CCR_DIR;
	/* peripheral address */
	DMA1C4->CPAR = (uint32_t)&USART1->DR;
	/* reset data counter */
	DMA1C4->CNDTR = 0;

	/* set low priority for tx transfer */
	NVIC_SETINTPRI(STM32_INT_USART1, 0x20);
	/* enable tx transfer interrupts */
	NVIC_ENABLEINT(STM32_INT_USART1);

	/* enable usart */
	USART1->CR1 |= USART_CR1_UE;

	/* exit critical section */
	Critical_Exit();

	/* reset lock */
	Sem_Release(&usart1_sem);

	/* report status */
	return EOK;
}

/* send data */
int USART1_Send(void *ptr, size_t size, cb_t cb)
{
	/* result code, sync or async call? */
	int rc = size, sync = cb == CB_NULL;

	/* store callback information */
	callback = cb;

	/* disable dma */
	DMA1C4->CCR &= ~DMA_CCR_EN;
	/* set memory address */
	DMA1C4->CMAR = (uint32_t)ptr;
	/* set memory size */
	DMA1C4->CNDTR = size;
	/* start transmitting */
	DMA1C4->CCR |= DMA_CCR_EN;

	/* release resource manually after a sync call has finished */
	while (sync && callback == CB_NULL);
	/* report status */
	return rc;
}

/* critical send, does not rely on dma transfers */
int USART1_CriticalSend(const void *ptr, size_t size)
{
	/* data pointer */
	const uint8_t *p = ptr;

	/* disable dma functionality */
	USART1->CR3 &= ~USART_CR3_DMAT;

	/* send byte after byte */
	while (size-- > 0) {
		/* wait for free buffer */
		while ((USART1->SR & USART_SR_TXE) == 0);
		/* send byte */
		USART1->DR = *(p++);
	}

	/* wait for free buffer */
	while ((USART1->SR & USART_SR_TC) == 0);
	/* clear transfer complete */
	USART1->SR = ~USART_SR_TC;
	/* restore dma functionality */
	USART1->CR3 |= USART_CR3_DMAT;

	/* report status */
	return EOK;
}
