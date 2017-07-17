/*
 * spi2.h
 *
 *  Created on: 29.06.2017
 *      Author: Tomek
 */

#ifndef DEV_SPI2_H_
#define DEV_SPI2_H_

#include <sys/cb.h>
#include <sys/sem.h>
#include <util/size.h>

/* semaphore */
extern sem_t spi2_sem;

/* dma interrupt */
void SPI2_DMA1Ch5Isr(void);
/* initialize spi1 */
int SPI2_Init(void);
/* initiate xfer */
int SPI2_Send(const void *ptr, size_t size, cb_t cb);

#endif /* DEV_SPI2_H_ */
