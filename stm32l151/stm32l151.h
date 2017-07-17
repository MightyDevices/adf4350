/*
 * stm32l151.h
 *
 *  Created on: 29.06.2017
 *      Author: Tomek
 */

#ifndef STM32L151_STM32L151_H_
#define STM32L151_STM32L151_H_

#include <stdint.h>

/* register type 8 bit */
typedef volatile uint8_t reg8_t;
/* register type 16 bit */
typedef volatile uint16_t reg16_t;
/* register type */
typedef volatile uint32_t reg32_t;
/* bitband type */
typedef volatile uint32_t bitband_t;

/* core exeptions */
/* reset routine */
#define STM32_EXC_RESET						1
/* Non maskable interrupt. The RCC Clock Security System (CSS) is
 * linked to the NMI vector. */
#define STM32_EXC_NMI						2
/* All class of fault */
#define STM32_EXC_HARDFAULT					3
/* Memory management */
#define STM32_EXC_MEMMANAGE					4
/* Pre-fetch fault, memory access fault */
#define STM32_EXC_BUSFAULT					5
/* Undefined instruction or illegal state */
#define STM32_EXC_USAGEFAULT				6
/* System service call via SWI instruction */
#define STM32_EXC_SVC						11
/* Debug Monitor */
#define STM32_EXC_DEBUGMON					12
/* Pendable request for system service */
#define STM32_EXC_PENDSV					14
/* System tick timer */
#define STM32_EXC_SYSTICK					15


/* interrupt sources */
/* Window Watchdog interrupt */
#define STM32_INT_WWDG						0
/* PVD through EXTI Line detection interrupt */
#define STM32_INT_PVD						1
/* Tamper and TimeStamp through EXTI line interrupts */
#define STM32_INT_TAMPER					2
/* RTC Wakeup through EXTI line interrupt */
#define STM32_INT_RTCWKUP					3
/* Flash global interrupt */
#define STM32_INT_FLASH						4
/* RCC global interrupt */
#define STM32_INT_RCC						5
/* EXTI Line0 interrupt */
#define STM32_INT_EXTI0						6
/* EXTI Line1 interrupt */
#define STM32_INT_EXTI1						7
/* EXTI Line2 interrupt */
#define STM32_INT_EXTI2						8
/* EXTI Line3 interrupt */
#define STM32_INT_EXTI3						9
/* EXTI Line4 interrupt */
#define STM32_INT_EXTI4						10
/* DMA1 Channel1 global interrupt */
#define STM32_INT_DMA1_CH1					11
/* DMA1 Channel2 global interrupt */
#define STM32_INT_DMA1_CH2					12
/* DMA1 Channel3 global interrupt */
#define STM32_INT_DMA1_CH3					13
/* DMA1 Channel4 global interrupt */
#define STM32_INT_DMA1_CH4					14
/* DMA1 Channel5 global interrupt */
#define STM32_INT_DMA1_CH5					15
/* DMA1 Channel6 global interrupt */
#define STM32_INT_DMA1_CH6					16
/* DMA1 Channel7 global interrupt */
#define STM32_INT_DMA1_CH7					17
/* ADC1 global interrupt */
#define STM32_INT_ADC						18
/* USB High priority interrupt */
#define STM32_INT_USBHP						19
/* USB Low priority interrupt */
#define STM32_INT_USBLP						20
/* DAC interrupt */
#define STM32_INT_DAC						21
/* Comparator wakeup through EXTI line (21 and 22) interrupt/Channel
 * acquisition interrupt */
#define STM32_INT_COMP						22
/* EXTI Line[9:5] interrupts */
#define STM32_INT_EXTI5_9					23
/* LCD global interrupt */
#define STM32_INT_LCD						24
/* TIM9 global interrupt */
#define STM32_INT_TIM9						25
/* TIM10 global interrupt */
#define STM32_INT_TIM10						26
/* TIM11 global interrupt */
#define STM32_INT_TIM11						27
/* TIM2 global interrupt */
#define STM32_INT_TIM2						28
/* TIM3 global interrupt */
#define STM32_INT_TIM3						29
/* TIM4 global interrupt */
#define STM32_INT_TIM4						30
/* I2C1 event interrupt */
#define STM32_INT_I2C1EV					31
/* I2C1 error interrupt */
#define STM32_INT_I2C1ER					32
/* I2C2 event interrupt */
#define STM32_INT_I2C2EV					33
/* I2C2 error interrupt */
#define STM32_INT_I2C2ER					34
/* SPI1 global interrupt */
#define STM32_INT_SPI1						35
/* SPI2 global interrupt */
#define STM32_INT_SPI2						36
/* USART1 global interrupt */
#define STM32_INT_USART1					37
/* USART2 global interrupt */
#define STM32_INT_USART2					38
/* USART3 global interrupt */
#define STM32_INT_USART3					39
/* EXTI Line[15:10] interrupts */
#define STM32_INT_EXTI10_15					40
/* RTC Alarms (A and B) through EXTI line interrupt */
#define STM32_INT_RTCALARM					41
/* USB Device FS Wakeup through EXTI line interrupt */
#define STM32_INT_USBWKUP					42
/* TIM6 global interrupt */
#define STM32_INT_TIM6						43
/* TIM7 global interrupt */
#define STM32_INT_TIM7						44

/* bitband access */
#define STM32_BB(x, b)                                                  	\
        *((reg32_t *) (((uint32_t)(x) & 0xf0000000) | 0x02000000 |       	\
                       ((uint32_t)(x) & 0x000fffff) << 5 |               	\
                       ((b) << 2)))

/* enable interrupts globally */
#define STM32_ENABLEINTS()					\
	__asm__ volatile ("cpsie i")

/* disable interrupts globally */
#define STM32_DISABLEINTS()					\
	__asm__ volatile ("cpsid i")

/* ram function */
#define RAMFUNC __attribute__ ((long_call, section (".data")))

#endif /* STM32L151_STM32L151_H_ */
