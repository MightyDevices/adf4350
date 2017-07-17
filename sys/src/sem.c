/*
 * sem.c
 *
 *  Created on: 03-07-2015
 *      Author: Tomek
 */

#include <arch/arch.h>
#include <sys/sem.h>
#include <sys/err.h>

/* try to lock on semaphore */
int Sem_TryLock(sem_t *s)
{
	/* temporary semaphore value */
	uint32_t c;

	/* this has to be enclosed in a loop because of the possibility of
	 * disturbing the memory access by the interrupt */
	do {
		/* load value */
		c = Arch_LDREX(s);
		/* no resources */
		if (c == 0)
			return EFATAL;
	/* task will be completed when there are resources available and write is
	 * successful */
	} while (Arch_STREX(0, s));

	/* memory barrier to ensure all memory writes have been completed up to
	 * this point */
	__asm__ volatile ("dmb");
	/* report status */
	return EOK;
}

/* lock */
int Sem_Lock(sem_t *s)
{
	/* temporary semaphore value */
	uint32_t c;

	/* loop until operation succeeds */
	do {
		/* wait for semaphore to become released */
		while ((c = Arch_LDREX(s)) == 0);
	/* try to write to semaphore */
	} while (Arch_STREX(0, s));

	/* memory barrier to ensure all memory writes have been completed up to
	 * this point */
	__asm__ volatile ("dmb");
	/* this cannot fail */
	return EOK;
}

/* release semaphore */
void Sem_Release(sem_t *s)
{
	/* memory barrier */
	__asm__ volatile ("dmb");
	/* loop until write is successful */
	do {
		/* read current value */
		Arch_LDREX(s);
	/* try to release */
	} while (Arch_STREX(1, s));
}
