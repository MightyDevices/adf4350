/*
 * usart1.h
 *
 *  Created on: 18-06-2012
 *      Author: Tomek
 */

#ifndef DEV_USART1_H_
#define DEV_USART1_H_

#include <util/size.h>
#include <sys/ev.h>
#include <sys/sem.h>

/* lock */
extern sem_t usart1_sem;

/* usart1 interrupt */
void USART1_USART1Isr(void);

/* initialize usart1 */
int USART1_Init(void);
/* send data */
int USART1_Send(void *ptr, size_t size, cb_t cb);
/* simple send, does not rely on dma transfers */
int USART1_CriticalSend(const void *ptr, size_t size);

#endif /* USART1_H_ */
