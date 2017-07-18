/*
 * arch.h
 *
 *  Created on: 29.06.2017
 *      Author: Tomek
 */

#ifndef ARCH_ARCH_H_
#define ARCH_ARCH_H_

#include <stdint.h>

/* load exclusively */
static inline __attribute__((always_inline)) uint32_t Arch_LDREX(volatile
		void *ptr)
{
	/* result */
	uint32_t result;
	/* some assembly magic */
	__asm__ volatile (
		"ldrex		%0, [%1]		\n"
		: "=r" (result)
		: "r" (ptr)
	);
	/* report result */
	return result;
}

/* store exclusively */
static inline __attribute__((always_inline)) int Arch_STREX(uint32_t value,
		volatile void *ptr)
{
	/* storage result */
	int result;
	/* some assembly magic */
	__asm__ volatile (
		"strex		%0, %1, [%2]	\n"
		: "=r" (result)
		: "r" (value), "r" (ptr)
	);
	/* report result */
	return -result;
}

/* count leading zeros */
static inline __attribute__((always_inline)) uint32_t Arch_CLZ(uint32_t x)
{
	/* result */
	uint32_t result;
	/* some assembly magic */
	__asm__ volatile (
		"clz		%0, %1		\n"
		: "=r" (result)
		: "r" (x)
	);
	/* report result */
	return result;
}

/* reverse byte order in 32 bit word */
static inline __attribute__((always_inline)) uint32_t Arch_REV(uint32_t x)
{
	/* result */
	uint32_t result;
	/* some assembly magic */
	__asm__ volatile (
		"rev		%0, %1		\n"
		: "=r" (result)
		: "r" (x)
	);
	/* report result */
	return result;
}

#endif /* ARCH_ARCH_H_ */
