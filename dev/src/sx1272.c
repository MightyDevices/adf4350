/*
 * sx1272.c
 *
 *  Created on: 29.06.2017
 *      Author: Tomek
 */

#include <dev/spi1.h>
#include <dev/sx1272.h>
#include <dev/sx1272_regs.h>
#include <stm32l151/rcc.h>
#include <stm32l151/gpio.h>
#include <stm32l151/nvic.h>
#include <stm32l151/exti.h>
#include <stm32l151/syscfg.h>
#include <sys/critical.h>
#include <sys/ev.h>
#include <sys/err.h>
#include <sys/sem.h>

#define DEBUG
#include <dev/debug.h>

/* xtal frequency */
#define XTAL_FREQ								32000000
/* flags */
#define FLAG_WR									0x80
#define FLAG_RD									0x00

/* semaphore */
sem_t sx1272_sem;
/* event */
ev_t sx1272_ev;

/* perform spi xfer */
static void SX1272_SpiXfer(void *ptr, size_t size, int cont)
{
	/* select chip */
	GPIOB->BSRR = GPIO_BSRR_BR_0;
	/* xfer data */
	SPI1_Xfer(ptr, size, 0);
	/* de-select chip */
	if (!cont)
		GPIOB->BSRR = GPIO_BSRR_BS_0;
}

/* interrupt routine for DIO0 */
void SX1272_Dio0Exti1Isr(void)
{
	/* clear interrupt */
	EXTI->PR = EXTI_PR_PR1;

	/* notify others */
	Ev_Notify(&sx1272_ev, 0);
	/* display message */
	dprintf_i("DIO0\n", 0);
}

/* interrupt routine for DIO1 */
void SX1272_Dio1Exti10Isr(void)
{
	/* clear interrupt */
	EXTI->PR = EXTI_PR_PR10;

	/* notify others */
	Ev_Notify(&sx1272_ev, 0);
	/* display message */
	dprintf_i("DIO1\n", 0);
}

/* interrupt routine for DIO2 */
void SX1272_Dio2Exti11Isr(void)
{
	/* clear interrupt */
	EXTI->PR = EXTI_PR_PR11;
	/* display message */
	dprintf_i("DIO2\n", 0);
}

/* interrupt routine for DIO3 */
void SX1272_Dio3Exti7Isr(void)
{
	/* clear interrupt */
	EXTI->PR = EXTI_PR_PR7;
	/* display message */
	dprintf_i("DIO3\n", 0);
}

/* interrupt routine for DIO4 */
void SX1272_Dio4Exti5Isr(void)
{
	/* clear interrupt */
	EXTI->PR = EXTI_PR_PR5;
	/* display message */
	dprintf_i("DIO4\n", 0);
}

/* interrupt routine for DIO5 */
void SX1272_Dio5Exti4Isr(void)
{
	/* clear interrupt */
	EXTI->PR = EXTI_PR_PR4;
	/* display message */
	dprintf_i("DIO5\n", 0);
}

/* initialize sx chip */
int SX1272_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable gpios */
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN;
	/* enable sys config */
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	/* configure reset pin */
	GPIOA->MODER &= ~GPIO_MODER_MODER2;
	/* set default state */
	GPIOA->BSRR = GPIO_BSRR_BR_2;
	/* enable as output */
	GPIOA->MODER |= GPIO_MODER_MODER2_0;

	/* configure nss pin */
	GPIOB->MODER &= ~GPIO_MODER_MODER0;
	/* set default state */
	GPIOB->BSRR = GPIO_BSRR_BS_0;
	/* configure as ouput */
	GPIOB->MODER |= GPIO_MODER_MODER0_0;

	/* configure dio pins as inputs */
	GPIOB->MODER &= ~(GPIO_MODER_MODER1 | GPIO_MODER_MODER4 | GPIO_MODER_MODER5 |
			GPIO_MODER_MODER7 | GPIO_MODER_MODER10 | GPIO_MODER_MODER11);
	/* prepare pull-downs */
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR1_1 | GPIO_MODER_MODER4_1 | GPIO_MODER_MODER5_1 |
			GPIO_MODER_MODER7_1 | GPIO_MODER_MODER10_1 | GPIO_MODER_MODER11_1;

	/* reset mapping */
	SYSCFG->EXTICR1 &= ~(SYSCFG_EXTICR1_EXTI1);
	SYSCFG->EXTICR2 &= ~(SYSCFG_EXTICR2_EXTI4 | SYSCFG_EXTICR2_EXTI5);
	SYSCFG->EXTICR3 &= ~(SYSCFG_EXTICR3_EXTI10 | SYSCFG_EXTICR3_EXTI11);
	/* remap exti: 1, 4, 5, 7, 10, 11 to port b */
	SYSCFG->EXTICR1 |= SYSCFG_EXTICR1_EXTI1_PB;
	SYSCFG->EXTICR2 |= SYSCFG_EXTICR2_EXTI4_PB | SYSCFG_EXTICR2_EXTI5_PB;
	SYSCFG->EXTICR3 |= SYSCFG_EXTICR3_EXTI10_PB | SYSCFG_EXTICR3_EXTI11_PB;

	/* configure for rising edge sensitivity */
	EXTI->RTSR = EXTI_RTSR_TR1 | EXTI_RTSR_TR4 | EXTI_RTSR_TR5 | EXTI_RTSR_TR7 |
			EXTI_RTSR_TR10 | EXTI_RTSR_TR11;

	/* configure priority */
	NVIC_SETINTPRI(STM32_INT_EXTI1, 0xf0);
	/* enable interrupt */
	NVIC_ENABLEINT(STM32_INT_EXTI1);

	/* TODO: enable specific interrupts */
	EXTI->IMR = EXTI_IMR_MR1 | EXTI_IMR_MR4 | EXTI_IMR_MR5 | EXTI_IMR_MR7 |
			EXTI_IMR_MR10 | EXTI_IMR_MR11;

	/* exit critical section */
	Critical_Exit();

	/* reset the device */
	GPIOA->BSRR = GPIO_BSRR_BS_2;
	/* wait for 100us */
	for (volatile int i = 0; i < 1000; i++);
	/* release reset */
	GPIOA->BSRR = GPIO_BSRR_BR_2;
	/* wait for 5ms */
	for (volatile int i = 0; i < 50000; i++);

	/* report status */
	return EOK;
}

/* set current modulation scheme */
int SX1272_SetModulation(uint8_t type, uint8_t shaping)
{
	/* command buffer */
	uint8_t cmd[2];

	/* read opmode register */
	cmd[0] = FLAG_RD | REG_OPMODE;
	/* read operation */
	SX1272_SpiXfer(cmd, 2, 0);

	/* shaping is not used with lora modulation */
	if (type == SX1272_MOD_LORA)
		shaping = 0;

	/* write opmode register */
	cmd[0] = FLAG_WR | REG_OPMODE;
	cmd[1] = (cmd[1] & ~(REG_OPMODE_MODULATIONTYPE |
			REG_OPMODE_LONGRANGEMODE | REG_OPMODE_MODULATIONSHAPING)) |
			type | shaping;
	/* write new setting */
	SX1272_SpiXfer(cmd, 2, 0);

	/* report status */
	return EOK;
}

/* set bitrate */
int SX1272_SetBitrate(uint32_t bit_rate)
{
	/* command buffer */
	uint8_t cmd[3];
	/* compute bit rate word */
	uint32_t br_word = (XTAL_FREQ << 4) / bit_rate;

	/* store in command buffer: whole part */
	cmd[0] = FLAG_WR | REG_BITRATE_MSB;
	cmd[1] = br_word >> 12;
	cmd[2] = br_word >> 4;
	/* write whole part */
	SX1272_SpiXfer(cmd, 3, 0);

	/* store in command buffer: fractional part */
	cmd[0] = FLAG_WR | REG_BITRATE_FRAC;
	cmd[1] = br_word & 0xf;
	/* write fractional part */
	SX1272_SpiXfer(cmd, 2, 0);

	/* report status */
	return EOK;
}

/* set frequency deviation */
int SX1272_SetDeviation(uint32_t deviation)
{
	/* command buffer */
	uint8_t cmd[3];
	/* compute deviation word */
	uint32_t dev_word =  ((uint64_t)deviation << 19) / XTAL_FREQ;

	/* store in command buffer */
	cmd[0] = FLAG_WR | REG_FDEV_MSB;
	cmd[1] = dev_word >> 8;
	cmd[2] = dev_word >> 0;
	/* write deviation */
	SX1272_SpiXfer(cmd, 3, 0);

	/* report status */
	return EOK;
}

/* set center frequency */
int SX1272_SetFrequency(uint32_t freq)
{
	/* command buffer */
	uint8_t cmd[4];
	/* compute tuning word */
	uint32_t freq_word = ((uint64_t)freq << 19) / XTAL_FREQ;

	/* store in command buffer */
	cmd[0] = FLAG_WR | REG_FRF_MSB;
	cmd[1] = freq_word >> 16;
	cmd[2] = freq_word >>  8;
	cmd[3] = freq_word >>  0;
	/* write frequency */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);

	/* report status */
	return EOK;
}



/* set output power */
int SX1272_SetOutputPower(uint8_t pa_select, uint8_t dbm)
{
	/* command buffer */
	uint8_t cmd[4];

	/* prepare write command */
	cmd[0] = FLAG_WR | REG_PA_CONFIG;
	cmd[1] = pa_select | ((dbm - 2) & 0x0F);
	/* write back */
	SX1272_SpiXfer(cmd, 2, 0);

	/* prepare write command */
	cmd[0] = FLAG_WR | REG_PA_DAC;
	cmd[1] = 0x07;
	/* write back */
	SX1272_SpiXfer(cmd, 2, 0);

	/* report status */
	return EOK;
}

/* set preamble configuration */
int SX1272_SetPreambleConfig(uint16_t pream_len, uint8_t polarity)
{
	/* command buffer */
	uint8_t cmd[4];

	/* read sync conf register */
	cmd[0] = FLAG_RD | REG_SYNC_CONFIG;
	/* read configuration */
	SX1272_SpiXfer(cmd, 2, 0);

	/* update config */
	cmd[0] = FLAG_WR | REG_PREAMBLE_MSB;
	cmd[3] = (cmd[1] & ~REG_SYNC_CONFIG_PREAMBLEPOLARITY) | polarity;
	cmd[1] = (pream_len - 1) >> 8;
	cmd[2] = (pream_len - 1) & 0xff;
	/* write configuration */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);

	/* report status */
	return EOK;
}

/* set sync configuration */
int SX1272_SetSyncConfig(uint8_t on, uint8_t *sync, uint8_t size)
{
	/* command buffer */
	uint8_t cmd[10];

	/* read sync conf register */
	cmd[0] = FLAG_RD | REG_SYNC_CONFIG;
	/* read configuration */
	SX1272_SpiXfer(cmd, 2, 0);

	/* update configuration */
	cmd[0] = FLAG_WR | REG_SYNC_CONFIG;
	cmd[1] = (cmd[1] & ~(REG_SYNC_CONFIG_SYNC | REG_SYNC_CONFIG_SYNCSIZE)) |
			on | (size - 1);
	/* copy sync field */
	for (uint32_t i = 0; i < size; i++)
		cmd[2 + i] = sync[i];
	/* write configuration */
	SX1272_SpiXfer(cmd, 2 + size, 0);

	/* report status */
	return EOK;
}

/* set packet configuration */
int SX1272_SetPacketConfig(uint32_t flags, uint16_t length)
{
	/* command buffer */
	uint8_t cmd[4];

	/* prepare write command */
	cmd[0] = FLAG_WR | REG_PACKET_CONFIG1;
	cmd[1] = flags & 0xff;
	cmd[2] = flags >> 8 | length >> 8;
	cmd[3] = length;
	/* write configuration */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);

	/* report status */
	return EOK;
}

/* configure addresses */
int SX1272_SetAddress(uint8_t node, uint8_t bcast)
{
	/* command buffer */
	uint8_t cmd[3];

	/* prepare write command */
	cmd[0] = FLAG_WR | REG_NODE_ADRS;
	cmd[1] = node;
	cmd[2] = bcast;
	/* write configuration */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);

	/* report status */
	return EOK;
}

/* pin mapping */
int SX1272_SetDIOMapping(uint16_t mapping)
{
	/* command buffer */
	uint8_t cmd[3];

	/* prepare write command */
	cmd[0] = FLAG_WR | REG_DIO_MAPPING1;
	cmd[1] = mapping & 0xFF;
	cmd[2] = mapping >> 8;
	/* write configuration */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);

	/* report status */
	return EOK;
}

/* set operation mode */
int SX1272_SetOpMode(uint8_t mode)
{
	/* command buffer */
	uint8_t cmd[2];

	/* prepare read operation */
	cmd[0] = FLAG_RD | REG_OPMODE;
	/* read */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);

	/* prepare write command */
	cmd[0] = FLAG_WR | REG_OPMODE;
	cmd[1] = (cmd[1] & ~REG_OPMODE_STATE) | mode;
	/* write back */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);

	/* report status */
	return EOK;
}

/* configure sequencer */
int SX1272_SetSequencer(uint16_t seq)
{
	/* command buffer */
	uint8_t cmd[3];
	/* prepare read operation */
	cmd[0] = FLAG_WR | REG_SEQ_CONFIG1;
	cmd[1] = seq & 0xff;
	cmd[2] = seq >> 8;

	/* read */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);
	/* report status */
	return EOK;
}

/* configure fifo threshold and set tx start condition */
int SX1272_SetFifoThreshold(uint8_t threshold, uint8_t start_cond)
{
	/* command buffer */
	uint8_t cmd[2];
	/* prepare read operation */
	cmd[0] = FLAG_WR | REG_FIFO_THRESH;
	cmd[1] = (threshold - 1) | start_cond;

	/* read */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);
	/* report status */
	return EOK;
}

/* returns interrupt flags */
int SX1272_GetIrqFlags(uint16_t *flags)
{
	/* command buffer */
	uint8_t cmd[3];
	/* prepare read operation */
	cmd[0] = FLAG_RD | REG_IRQ_FLAGS1;
	/* read */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);
	/* store result */
	*flags = cmd[1] << 8 | cmd[2];

	/* report status */
	return EOK;
}

/* write data to fifo */
int SX1272_WriteFifo(void *ptr, size_t size)
{
	/* command buffer */
	uint8_t cmd[1];

	/* prepare write operation */
	cmd[0] = FLAG_WR | REG_FIFO;
	/* send command */
	SX1272_SpiXfer(cmd, sizeof(cmd), 1);
	/* send data */
	SX1272_SpiXfer(ptr, size, 0);

	/* report status */
	return EOK;
}

/* read data from fifo */
int SX1272_ReadFifo(void *ptr, size_t size)
{
	/* command buffer */
	uint8_t cmd[1];

	/* prepare write operation */
	cmd[0] = FLAG_RD | REG_FIFO;
	/* send command */
	SX1272_SpiXfer(cmd, sizeof(cmd), 1);
	/* send data */
	SX1272_SpiXfer(ptr, size, 0);

	/* report status */
	return EOK;
}

// LORA PART

/* configure modem */
int SX1272_LoRaConfigureModem(uint16_t flags, uint8_t rx_timeout)
{
	/* command buffer */
	uint8_t cmd[4], cmd2[2], cmd3[2];

	/* prepare write operation: MODEMCONFIG1 */
	cmd[0] = FLAG_WR | REG_LR_MODEMCONFIG1;
	cmd[1] = flags >> 0;
	cmd[2] = flags >> 8 | rx_timeout >> 8;
	cmd[3] = rx_timeout >> 0;

	/* set LowDataRateOptimize when sf >= 11 && bw == 125kHz */
	if (((cmd[2] & REG_LR_MODEMCONFIG2_SF) >= REG_LR_MODEMCONFIG2_SF_11) &&
		 (cmd[1] & REG_LR_MODEMCONFIG1_BW) == REG_LR_MODEMCONFIG1_BW_125_KHZ) {
		cmd[1] |= REG_LR_MODEMCONFIG1_LOWDATARATEOPTIMIZE_ON;
	}

	/* send data */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);

	/* configure write operations */
	cmd2[0] = FLAG_WR | REG_LR_DETECTIONOPTIMIZE;
	cmd3[0] = FLAG_WR | REG_LR_DETECTIONTHRESHOLD;

	/* prepare write operation: DETECTIONOPTIMIZE && DETECTIONTHRESH */
	if ((cmd[2] & REG_LR_MODEMCONFIG2_SF) == REG_LR_MODEMCONFIG2_SF_6) {
		cmd2[1] = REG_LR_DETECTIONOPTIMIZE_SF6;
		cmd3[1] = REG_LR_DETECTIONTHRESH_SF6;
	} else {
		cmd2[1] = REG_LR_DETECTIONOPTIMIZE_SF7_TO_SF12;
		cmd3[1] = REG_LR_DETECTIONTHRESH_SF7_TO_SF12;
	}

	/* send data */
	SX1272_SpiXfer(cmd2, sizeof(cmd2), 0);
	SX1272_SpiXfer(cmd3, sizeof(cmd3), 0);

	/* report status */
	return EOK;
}

/* set preable length */
int SX1272_LoRaSetPreamble(uint8_t length)
{
	/* command buffer */
	uint8_t cmd[3];

	/* prepare write operation */
	cmd[0] = FLAG_WR | REG_LR_PREAMBLEMSB;
	cmd[1] = length >> 8;
	cmd[2] = length >> 0;
	/* send command */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);

	/* report status */
	return EOK;
}

/* set sync word */
int SX1272_LoRaSetSyncWord(uint8_t sync)
{
	/* command buffer */
	uint8_t cmd[2];

	/* prepare write operation */
	cmd[0] = FLAG_WR | REG_LR_SYNCWORD;
	cmd[1] = sync;
	/* send command */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);

	/* report status */
	return EOK;
}

/* configure fifo */
int SX1272_LoRaConfigureFifo(uint8_t addr, uint8_t tx_base, uint8_t rx_base)
{
	/* command buffer */
	uint8_t cmd[4];
	/* prepare write operation */
	cmd[0] = FLAG_WR | REG_LR_FIFOADDRPTR;
	cmd[1] = addr;
	cmd[2] = tx_base;
	cmd[3] = rx_base;
	/* send data */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);

	/* report status */
	return EOK;
}

/* get received packet information */
int SX1272_LoRaGetRxPacketInfo(uint8_t *start_addr, uint8_t *nb_bytes)
{
	/* command buffer */
	uint8_t cmd[5];

	/* prepare read operation */
	cmd[0] = FLAG_RD | REG_LR_FIFORXCURRENTADDR;
	/* read data */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);
	/* store information */
	*start_addr = cmd[1];
	*nb_bytes = cmd[4];

	/* report status */
	return EOK;
}

/* set payload length */
int SX1272_LoRaSetPayloadLength(uint8_t length)
{
	/* command buffer */
	uint8_t cmd[2];
	/* prepare write operation */
	cmd[0] = FLAG_WR | REG_LR_PAYLOADLENGTH;
	cmd[1] = length;
	/* send data */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);

	/* report status */
	return EOK;
}

/* set interrupt mask */
int SX1272_LoRaSetIrqMask(uint8_t mask)
{
	/* command buffer */
	uint8_t cmd[2];
	/* prepare read operation */
	cmd[0] = FLAG_WR | REG_LR_IRQFLAGSMASK;
	cmd[1] = mask;
	/* send data */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);

	/* report status */
	return EOK;
}

/* read interrupt flags */
int SX1272_LoRaGetIrqFlags(uint8_t *flags)
{
	/* command buffer */
	uint8_t cmd[2];
	/* prepare read operation */
	cmd[0] = FLAG_RD | REG_LR_IRQFLAGS;
	/* send data */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);
	/* store result */
	*flags = cmd[1];

	/* report status */
	return EOK;
}

/* clear interrupt flags */
int SX1272_LoRaClearIrqFlags(uint8_t flags)
{
	/* command buffer */
	uint8_t cmd[2];
	/* prepare read operation */
	cmd[0] = FLAG_WR | REG_LR_IRQFLAGS;
	cmd[1] = flags;
	/* send data */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);

	/* report status */
	return EOK;
}

int SX1272_Test(uint8_t arg)
{
	/* command buffer */
	uint8_t cmd[2];
	/* prepare read operation */
	cmd[0] = FLAG_RD | REG_OPMODE;
	/* send data */
	SX1272_SpiXfer(cmd, sizeof(cmd), 0);


	dprintf_i("reg = %x\n", cmd[1]);


	/* report status */
	return EOK;
}
