/*
 * spi1.h
 *
 *  Created on: 29.06.2017
 *      Author: Tomek
 */

#ifndef DEV_SPI1_H_
#define DEV_SPI1_H_

#include <sys/cb.h>
#include <sys/sem.h>
#include <util/size.h>

/* semaphore */
extern sem_t spi1_sem;

/* dma interrupt */
void SPI1_DMA1Ch2Isr(void);
/* initialize spi1 */
int SPI1_Init(void);
/* initiate xfer */
int SPI1_Xfer(void *ptr, size_t size, cb_t cb);

#endif /* DEV_SPI1_H_ */
