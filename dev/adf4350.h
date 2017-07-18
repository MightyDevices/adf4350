/*
 * adf4350.h
 *
 *  Created on: 17.07.2017
 *      Author: Tomek
 */

#ifndef DEV_ADF4350_H_
#define DEV_ADF4350_H_

#include <stdint.h>
#include <sys/ev.h>

/* lock detected event */
extern ev_t adf4350_ev;

/* lock detect */
void ADF4350_Exti11Isr(void);

/* initialize Synthesizer */
int ADF4350_Init(void);
/* write registers */
void ADF4350_WriteRegisters(const uint32_t *regs, uint32_t num);
/* return locked state */
int ADF4350_IsLocked(void);

#endif /* DEV_ADF4350_H_ */
