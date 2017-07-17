/*
 * adf4350.c
 *
 *  Created on: 17.07.2017
 *      Author: Tomek
 */

#include <dev/spi2.h>
#include <stm32l151/rcc.h>
#include <stm32l151/gpio.h>
#include <sys/critical.h>
#include <sys/err.h>

/* register 0 */
#define R0_FRAC								0x00007FF8
#define R0_INT								0x7FFF8000

/* register 1 */
#define R1_MOD								0x00007FF8
#define R1_PHASE							0x07FF8000
#define R1_PRESCALER						0x08000000
#define R1_PRESCALER_4_5					0x00000000
#define R1_PRESCALER_8_9					0x08000000

/* register 2 */
#define R2_CNT_RESET						0x00000008
#define R2_CNT_RESET_DISABLED				0x00000000
#define R2_CNT_RESET_ENABLED				0x00000008
#define R2_CP_THREESTATE					0x00000010
#define R2_CP_THREESTATE_DISABLED			0x00000000
#define R2_CP_THREESTATE_ENABLED			0x00000010
#define R2_POWERDOWN						0x00000020
#define R2_POWERDOWN_DISABLED				0x00000000
#define R2_POWERDOWN_ENABLED				0x00000020
#define R2_PD_POLARITY						0x00000040
#define R2_PD_POLARITY_NEGATIVE				0x00000000
#define R2_PD_POLARITY_POSITIVE				0x00000040
#define R2_LDP								0x00000080
#define R2_LDP_10NS							0x00000000
#define R2_LDP_6NS							0x00000080
#define R2_LDF								0x00000100
#define R2_LDF_FRAC							0x00000000
#define R2_LDF_INT							0x00000100
#define R2_CHARGEPUMP_CURRENT				0x00001E00
#define R2_DOUBLE_BUFF						0x00002000
#define R2_R								0x00FFC000
#define R2_RDIV2							0x01000000
#define R2_RDOUBLER							0x02000000
#define R2_RDOUBLER_DISABLED				0x00000000
#define R2_RDOUBLER_ENABLED					0x02000000
#define R2_MUXOUT							0x1C000000
#define R2_MUXOUT_THREESTATE_OUTPUT			0x00000000
#define R2_MUXOUT_DVDD						0x04000000
#define R2_MUXOUT_DGND						0x08000000
#define R2_MUXOUT_RDIV						0x0C000000
#define R2_MUXOUT_NDIV						0x10000000
#define R2_MUXOUT_ANALOG_LOCK				0x14000000
#define R2_MUXOUT_DIGITAL_LOCK				0x18000000
#define R2_LOWNOISESPUR						0x60000000
#define R2_LOWNOISESPUR_NOISE				0x00000000
#define R2_LOWNOISESPUR_SPUR				0x60000000

/* register 3 */
#define R3_CLKDIV							0x00007FF8
#define R3_CLKDIV_MODE						0x00018000
#define R3_CLKDIV_MODE_OFF					0x00000000
#define R3_CLKDIV_MODE_FASTLOCK				0x00008000
#define R3_CLKDIV_MODE_RESYNC				0x00010000
#define R3_CSR								0x00040000
#define R3_CSR_DISABLED						0x00000000
#define R3_CSR_ENABLED						0x00040000

/* register 4 */
#define R4_OUTPWR							0x00000018
#define R4_OUTPWR_M4						0x00000000
#define R4_OUTPWR_M1						0x00000008
#define R4_OUTPWR_P2						0x00000010
#define R4_OUTPWR_P5						0x00000018
#define R4_RFOUT							0x00000020
#define R4_RFOUT_DISABLED					0x00000000
#define R4_RFOUT_ENABLED					0x00000020
#define R4_AUXPWR							0x000000C0
#define R4_AUXPWR_M4						0x00000000
#define R4_AUXPWR_M1						0x00000040
#define R4_AUXPWR_P2						0x00000080
#define R4_AUXPWR_P5						0x000000C0
#define R4_AUXOUT							0x00000100
#define R4_AUXOUT_DISABLED					0x00000000
#define R4_AUXOUT_ENABLED					0x00000100
#define R4_AUXSEL							0x00000200
#define R4_AUXSEL_DIVIDED					0x00000000
#define R4_AUXSEL_FUNDAMENTAL				0x00000200
#define R4_MTLD								0x00000400
#define R4_MTLD_DISABLED					0x00000000
#define R4_MTLD_ENABLED						0x00000400
#define R4_VCOPD							0x00000800
#define R4_VCOPD_DISABLED					0x00000000
#define R4_VCOPD_ENABLED					0x00000800
#define R4_BAND_CLKDIV						0x000FF000
#define R4_RFDIV							0x00700000
#define R4_RFDIV_1							0x00000000
#define R4_RFDIV_2							0x00100000
#define R4_RFDIV_4							0x00200000
#define R4_RFDIV_8							0x00300000
#define R4_RFDIV_16							0x00400000
#define R4_FDBCKSEL							0x00800000
#define R4_FDBCKSEL_DIVIDED					0x00000000
#define R4_FDBCKSEL_FUNDAMENTAL				0x00800000

/* register 5 */
#define R5_LDPIN							0x00C00000
#define R5_LDPIN_LOW						0x00000000
#define R5_LDPIN_DIGITAL_LOCK				0x00400000
#define R5_LDPIN_HIGH						0x00C00000

/* initialize Synthesizer */
int ADF4350_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable port b */
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;


	/* exit critical section */
	Critical_Exit();
	/* report status */
	return EOK;
}
