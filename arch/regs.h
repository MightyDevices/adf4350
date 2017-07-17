/*
 * regs.h
 *
 *  Created on: 29.06.2017
 *      Author: Tomek
 */

#ifndef ARCH_REGS_H_
#define ARCH_REGS_H_

#include <stdint.h>

/* read basepri register */
static inline __attribute__((always_inline)) uint32_t Regs_ReadBasepri(
		uint32_t x)
{
	/* result */
	uint32_t result;
	/* some assembly magic */
	__asm__ volatile (
		"mrs		%0, basepri		\n"
		: "=r" (result)
		:
	);

	/* report result */
	return result;
}

/* write basepri register */
static inline __attribute__((always_inline)) void Regs_WriteBasepri(
		uint32_t x)
{
	__asm__ volatile (
		"msr 	basepri, %0			\n"
		:
		: "r" (x)
	);
}

/* read stack pointer */
static inline __attribute__((always_inline)) uint32_t Regs_ReadMSP(void)
{
	/* result */
	uint32_t result;
	/* some assembly magic */
	__asm__ volatile (
		"mrs		%0, msp			\n"
		: "=r" (result)
		:
	);

	/* report result */
	return result;
}

/* read Interrupt Control State Register */
static inline __attribute__((always_inline)) uint32_t Regs_ReadIPSR(void)
{
	/* result */
	uint32_t result;
	/* some assembly magic */
	__asm__ volatile (
		"mrs		%0, ipsr		\n"
		: "=r" (result)
		:
	);

	/* report result */
	return result;
}

#endif /* ARCH_REGS_H_ */
