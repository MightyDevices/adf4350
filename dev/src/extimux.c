/*
 * extimux.c
 *
 *  Created on: 31-08-2015
 *      Author: Tomek
 */

#include <stm32l151/rcc.h>
#include <stm32l151/exti.h>
#include <stm32l151/nvic.h>
#include <stm32l151/syscfg.h>
#include <sys/critical.h>
#include <sys/err.h>

/* routines */
#include <dev/adf4350.h>

/* exti interrupt mux for lines 5 to 9 */
void ExtiMux_Exti5_9Isr(void)
{
//	/* get pending register */
//	uint32_t pr = EXTI->PR;
//
//	/* exti5 interrupt */
//	if (pr & EXTI_PR_PR5)
//		SX1272_Dio4Exti5Isr();
//
//	/* exti10 interrupt */
//	if (pr & EXTI_PR_PR7)
//		SX1272_Dio3Exti7Isr();

}

/* exti interrupt mux for lines 10 to 15 */
void ExtiMux_Exti10_15Isr(void)
{
	/* get pending register */
	uint32_t pr = EXTI->PR;
//
//	/* exti10 interrupt */
//	if (pr & EXTI_PR_PR10)
//		SX1272_Dio1Exti10Isr();
//
	/* exti10 interrupt */
	if (pr & EXTI_PR_PR11)
		ADF4350_Exti11Isr();
}

/* initialize exti mux */
int ExtiMux_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable syscfg */
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	/* set priority */
	NVIC_SETINTPRI(STM32_INT_EXTI5_9, 0xf0);
	/* enable */
	NVIC_ENABLEINT(STM32_INT_EXTI5_9);

	/* set priority */
	NVIC_SETINTPRI(STM32_INT_EXTI10_15, 0xf0);
	/* enable interrupt */
	NVIC_ENABLEINT(STM32_INT_EXTI10_15);

	/* exit critical section */
	Critical_Exit();

	/* report status */
	return EOK;
}

