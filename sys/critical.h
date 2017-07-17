/*
 * critical.h
 *
 *  Created on: 26-08-2015
 *      Author: Tomek
 */

#ifndef SYS_CRITICAL_H_
#define SYS_CRITICAL_H_

#include <arch/regs.h>

/* critical section counter - used for nesting critical sections */
extern int critical_nesting_cnt;

/* enter critical section */
static inline __attribute__((always_inline)) void Critical_Enter(void)
{
	/* set interrupt base priority register */
	Regs_WriteBasepri(0x10);
	/* increment counter */
	critical_nesting_cnt++;
}

/* exit critical section */
static inline __attribute__((always_inline)) void Critical_Exit(void)
{
	/* decrement counter, re-enable interrupts if needed */
	if (--critical_nesting_cnt == 0)
		Regs_WriteBasepri(0);
}


#endif /* SYS_CRITICAL_H_ */
