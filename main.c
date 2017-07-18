/*
 * main.c
 *
 *      Author: Tomek
 */


#include <dev/adf4350.h>
#include <dev/adf4350_regs.h>
#include <dev/cpuclock.h>
#include <dev/extimux.h>
#include <dev/spi2.h>
#include <dev/usart1.h>
#include <dev/watchdog.h>
#include <util/bn.h>
#include <util/elems.h>
#include <version.h>

#define DEBUG
#include <dev/debug.h>

/* system entry point */
int main(void)
{
	/* inital delay */
	for (volatile int i = 0; i < 200000; i++);

	/* start watchdog */
	Watchdog_Init();
	/* initial kick */
	Watchdog_Kick();

	/* initialize clock module */
	CpuClock_Init();
	/* initialize exti mux */
	ExtiMux_Init();
	/* initialize uart */
	USART1_Init();
	/* initialize spi2 */
	SPI2_Init();

	/* initialize synthesizer */
	ADF4350_Init();

	/* lets prepare initial configuration (registers shall be programmed in order
	 * r5->r0 */
	const uint32_t cfg[] = {
			/* REGISTER 5 */
			/* enable lock detect on LD pin, r5 has some reserved bits that shall be
			 * set to 1 */
			ADF4350_R5_LDPIN_DIGITAL_LOCK | ADF4350_R5_RESERVED |
			/* register address */
			ADF4350_CB_R5,

			/* REGISTER 4 */
			/* take the feedback signal directly from the VCO, no output divider */
			ADF4350_R4_FDBCKSEL_FUNDAMENTAL | ADF4350_R4_RFDIV_1 |
			/* use maximum divider for the band selector */
			255 << LSB(ADF4350_R4_BAND_CLKDIV) |
			/* disable vco power down */
			ADF4350_R4_VCOPD_DISABLED |
			/* disable mute till lock detect */
			ADF4350_R4_MTLD_ENABLED |
			/* disable aux output, enable main rf output */
			ADF4350_R4_AUXOUT_DISABLED | ADF4350_R4_RFOUT_ENABLED |
			/* set output power +5dbm */
			ADF4350_R4_OUTPWR_P5 |
			/* register address */
			ADF4350_CB_R4,

			/* REGISTER 3 */
			/* no fast lock, no cycle slip, no divider */
			0 | ADF4350_CB_R3,

			/* REGISTER 2 */
			/* low noise option */
			ADF4350_R2_LOWNOISESPUR_NOISE |
			/* muxout (R-divider) */
			ADF4350_R2_MUXOUT_RDIV |
			/* no reference doubler, no reference div2 */
			0 |
			/* divide clock by 25 to obtain 1MHz */
			25 << LSB(ADF4350_R2_R) |
			/* charge pump current setting (mid position, 2.50mA) */
			ADF4350_R2_CHARGEPUMP_CURRENT_5MA00 |
			/* digital lock detect on integer part */
			ADF4350_R2_LDF_FRAC |
			/* lock detect precision: five consecutive cycles of 10ns must occur
			 * before lock detect is advertised */
			ADF4350_R2_LDP_6NS |
			/* select phase detector polarity appropriate for passive networks */
			ADF4350_R2_PD_POLARITY_POSITIVE |
			/* disable power down */
			ADF4350_R2_POWERDOWN_DISABLED |
			/* register address */
			ADF4350_CB_R2,

			/* REGISTER 1 */
			/* use 8/9 prescaler */
			ADF4350_R1_PRESCALER_8_9 |
			/* use the recommended phase offset of 1 */
			1 << LSB(ADF4350_R1_PHASE) |
			/* set modulus for fractional divider */
			2 << LSB(ADF4350_R1_MOD) |
			/* register address */
			ADF4350_CB_R1,

			/* REGISTER 0 */
			/* set INT value to 2450, do not use frac (0) */
			2450 << LSB(ADF4350_R0_INT) | 0 << LSB(ADF4350_R0_FRAC) |
			/* register address */
			ADF4350_CB_R0,
	};


	/* send configuration */
	ADF4350_WriteRegisters(cfg, elems(cfg));

	/* endless loop */
	while (1) {
		/* kick the dog */
		Watchdog_Kick();
	}


	/* never reached */
	return 0;
}
