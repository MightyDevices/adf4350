/*
 * main.c
 *
 *      Author: Tomek
 */

#include <dev/cpuclock.h>
#include <dev/extimux.h>
#include <dev/spi2.h>
#include <dev/usart1.h>
#include <dev/watchdog.h>
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

	/* display version information */
	dprintf("LoRa hw = %s, sw = %s\n", HW_VER, SW_VER);

	/* endless loop */
	while (1) {
		SPI2_Send("tomek", 5, 0);
		/* display version information */
		dprintf("LoRa hw = %s, sw = %s\n", HW_VER, SW_VER);
		/* kick the dog */
		Watchdog_Kick();
	}


	/* never reached */
	return 0;
}
