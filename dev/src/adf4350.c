/*
 * adf4350.c
 *
 *  Created on: 17.07.2017
 *      Author: Tomek
 */

#include <arch/arch.h>
#include <dev/adf4350_regs.h>
#include <dev/spi2.h>
#include <stm32l151/rcc.h>
#include <stm32l151/gpio.h>
#include <stm32l151/exti.h>
#include <stm32l151/syscfg.h>
#include <sys/critical.h>
#include <sys/err.h>

#define DEBUG
#include <dev/debug.h>

/* lock detected event */
ev_t adf4350_ev;

/* lock detect */
void ADF4350_Exti11Isr(void)
{
	/* clear bit */
	EXTI->PR = EXTI_PR_PR11;

	/* notify others */
	Ev_Notify(&adf4350_ev, 0);
}

/* initialize Synthesizer */
int ADF4350_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable port b */
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

	/* chip enable (pb14) and latch enable (pb12) */
	GPIOB->MODER &= ~(GPIO_MODER_MODER14 | GPIO_MODER_MODER12);
	/* set default state */
	GPIOB->BSRR = GPIO_BSRR_BS_14 | GPIO_BSRR_BR_12;
	/* configure as outputs */
	GPIOB->MODER |= GPIO_MODER_MODER12_0 | GPIO_MODER_MODER14_0;

	/* rf power down (pdr, pb2) */
	GPIOB->MODER &= ~(GPIO_MODER_MODER2);
	/* set default state */
	GPIOB->BSRR = GPIO_BSRR_BS_2;
	/* configure as output */
	GPIOB->MODER |= GPIO_MODER_MODER2_0;

	/* lock detect (pb11) */
	GPIOB->MODER &= ~(GPIO_MODER_MODER11);
	/* enable pull down */
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR11_1;

	/* configure pb11 as exti11 */
	SYSCFG->EXTICR3 = (SYSCFG->EXTICR3 & ~SYSCFG_EXTICR3_EXTI11) |
			SYSCFG_EXTICR3_EXTI11_PB;
	/* enable rising edge sensitivity */
	EXTI->RTSR |= EXTI_RTSR_TR11;
	/* enable interrupt generation */
	EXTI->IMR |= EXTI_IMR_MR11;
	/* enable event genertion */
	EXTI->EMR |= EXTI_EMR_MR11;

	/* exit critical section */
	Critical_Exit();
	/* report status */
	return EOK;
}

/* write registers */
void ADF4350_WriteRegisters(const uint32_t *regs, uint32_t num)
{
	/* process all words */
	while (num--) {
		/* clear latch enable */
		GPIOB->BSRR = GPIO_BSRR_BR_12;
		/* adf4350 expects whole 32 bit words to be shifted out MSB first, ST's SPI
		 * cannot operate with 32 bit words, so we need to pack 4 bytes into
		 * 32 bit word, MSByte first */
		uint32_t temp = Arch_REV(*regs++);
		/* send 32-bit word */
		SPI2_Send(&temp, sizeof(temp), 0);
		/* latch new data */
		GPIOB->BSRR = GPIO_BSRR_BS_12;
	}
}

/* return locked state */
int ADF4350_IsLocked(void)
{
	/* return lock pin status */
	return !!(GPIOB->IDR & GPIO_IDR_IDR_11);
}
