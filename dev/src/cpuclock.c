/*
 * cpuclock.c
 *
 *  Created on: 29.06.2017
 *      Author: Tomek
 */

#include <stm32l151/rcc.h>
#include <sys/critical.h>
#include <sys/err.h>


/* initialize frequency scaling module */
int CpuClock_Init(void)
{
	/* enter critical section */
	Critical_Enter();
	/* set starting frequency: 4.192MHz */
	RCC->ICSCR = (RCC->ICSCR & ~RCC_ICSCR_MSIRANGE) | RCC_ICSCR_MSIRANGE_6;
	/* exit critical section */
	Critical_Exit();

	/* report status */
	return EOK;
}

