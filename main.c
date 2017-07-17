/*
 * main.c
 *
 *      Author: Tomek
 */

#include <dev/cpuclock.h>
#include <dev/extimux.h>
#include <dev/spi1.h>
#include <dev/sx1272.h>
#include <dev/usart1.h>
#include <dev/watchdog.h>
#include <version.h>

#define DEBUG
#include <dev/debug.h>


/* lora modes */
#define LORA_RX									0
#define LORA_TX									1
/* current lora mode */
static int lora_mode;


/* sx interrupt callback in fsk mode */
void RadioFSK_SX1272Callback(void *arg)
{
	/* sequencer: set start bit, set low power mode to sequencer off and go back to
	 * init state (state that the device was in before enabling the sequencer) */
	uint16_t seq = SX1272_SEQ_START | SX1272_SEQ_LOWPOWER_SEQOFF_INIT;
	/* set up transitions: start -> tx -> pktsent -> idle */
	seq |= SX1272_SEQ_FROMSTART_TX_FIFOLVL | SX1272_SEQ_FROMTX_LOWPOWER;

	/* enable sequencer */
	SX1272_SetSequencer(seq);
}

/* configure radio to operate in fsk mode */
void RadioFSK_Init(void)
{
	/* payload */
	uint8_t data[] = "tomek";

	/* subscribe to events */
	Ev_RegisterCallback(&sx1272_ev, RadioFSK_SX1272Callback);

	/* set power */
	SX1272_SetOutputPower(SX1272_PA_BOOST, 2);

	/* need to enter sleep mode in order to change modulation */
	SX1272_SetOpMode(SX1272_OPMODE_SLEEP);
	/* set modulation scheme */
	SX1272_SetModulation(SX1272_MOD_OOK, SX1272_SHAPEOOK_2BITRATE);
	/* set frequency */
	SX1272_SetFrequency(868000000);

	/* packet configuration */
	/* configure DIO0 to indicate */
	SX1272_SetDIOMapping(SX1272_DIOMAP_D0PKT_PAYLOAD_RDY_PCKT_SENT);
	/* configure packetisation layer */
	SX1272_SetPacketConfig(SX1272_PKTCFG_LENGTH_FIX | SX1272_PKTCFG_DATAMODE_PKT |
			SX1272_PKTCFG_BEACON, sizeof(data));
	/* configure preamble */
	SX1272_SetPreambleConfig(1, SX1272_PREAMBLE_55);
	/* configure sync pattern */
	SX1272_SetSyncConfig(SX1272_SYNC_ON, (uint8_t *)"\xFF\xFF\xFF\xFF\xFF\xFF", 6);

	/* set fifo threshold */
	SX1272_SetFifoThreshold(sizeof(data), SX1272_TXSTARTCOND_FIFOEMPTY);
	/* store data */
	SX1272_WriteFifo(data, sizeof(data));

	/* this shall start packet generation */
	RadioFSK_SX1272Callback(0);
}

/* main callback routine */
void RadioLoRa_SX1272Callback(void *arg)
{
	/* interrupt flags */
	uint8_t irq_flags;
	/* packet information */
	uint8_t rx_addr = 0, rx_size = 0;
	/* data buffer */
	uint8_t buf[256];
	/* payload */
	uint8_t data[] = "tomek";

	/* read flags */
	SX1272_LoRaGetIrqFlags(&irq_flags);

	/* was in tx mode? */
	if (lora_mode == LORA_TX) {
		/* clear irq */
		SX1272_LoRaClearIrqFlags(SX1272_LORAIRQ_TX_DONE);
		/* show flags */
		dprintf_i("lora tx done\n", 0);

		/* prepare rx mode */
		/* re-configure dios: DIO0 - RX Done, DIO1 - RX Timeout */
		SX1272_SetDIOMapping(SX1272_DIOMAP_D0LORA_RX_DONE |
				SX1272_DIOMAP_D1LORA_RX_TIMEOUT);
		/* configure fifo: starting address = 0, tx_base = 0, rx_base = 0 */
		SX1272_LoRaConfigureFifo(0, 0, 0);

		/* store new mode */
		lora_mode = LORA_RX;
		/* switch to rx mode */
		SX1272_SetOpMode(SX1272_OPMODE_RECEIVER_SINGLE);
	/* was in rx mode? */
	} else {
		/* clear irqs */
		SX1272_LoRaClearIrqFlags(SX1272_LORAIRQ_RX_DONE | SX1272_LORAIRQ_RX_TIMEOUT);

		/* got frame? */
		if (irq_flags & SX1272_LORAIRQ_RX_DONE) {
			/* read packet information */
			SX1272_LoRaGetRxPacketInfo(&rx_addr, &rx_size);
			/* configure fifo for reading */
			SX1272_LoRaConfigureFifo(rx_addr, 0, 0);
			/* read data */
			SX1272_ReadFifo(buf, rx_size);

			/* zero terminate string */
			buf[rx_size] = 0;
			/* show data */
			dprintf_i("lora rx got data, len = %d, data = %s\n", rx_size, buf);
		/* no data for us ;-( */
		} else {
			dprintf_i("rx timeout\n", 0);
		}


		/* prepare tx */
		/* configure digital pins */
		SX1272_SetDIOMapping(SX1272_DIOMAP_D0LORA_TX_DONE);
		/* set payload size */
		SX1272_LoRaSetPayloadLength(sizeof(data));
		/* configure fifo: starting address = 0, tx_base = 0, rx_base = 0 */
		SX1272_LoRaConfigureFifo(0, 0, 0);
		/* store data in fifo */
		SX1272_WriteFifo(data, sizeof(data));

		/* store new mode */
		lora_mode = LORA_TX;
		/* switch to tx mode to start tx */
		SX1272_SetOpMode(SX1272_OPMODE_TRANSMITTER);
	}
}

/* initialize lora test */
void RadioLoRa_Init(void)
{
	/* payload */
	uint8_t data[] = "tomek";
	/* subscribe to events */
	Ev_RegisterCallback(&sx1272_ev, RadioLoRa_SX1272Callback);

	/* set power */
	SX1272_SetOutputPower(SX1272_PA_BOOST, 2);

	/* need to enter sleep mode in order to change modulation */
	SX1272_SetOpMode(SX1272_OPMODE_SLEEP);
	/* set modulation scheme */
	SX1272_SetModulation(SX1272_MOD_LORA, 0);
	/* set frequency */
	SX1272_SetFrequency(868000000);

	/* configure digital pins */
	SX1272_SetDIOMapping(SX1272_DIOMAP_D0LORA_TX_DONE);

	/* modem configuration */
	SX1272_LoRaConfigureModem(SX1272_LORAMODEM_BW_500K |
			SX1272_LORAMODEM_CODING_4_5 |
			SX1272_LORAMODEM_HDR_IMPLICIT |
			SX1272_LORAMODEM_CRC_OFF |
			SX1272_LORAMODEM_SF_6 |
			SX1272_LORAMODEM_TX_SINGLE, 30);


	/* set payload size */
	SX1272_LoRaSetPayloadLength(sizeof(data));
	/* configure fifo: starting address = 0, tx_base = 0, rx_base = 0 */
	SX1272_LoRaConfigureFifo(0, 0, 0);

	/* switch to standby mode: needed for fifo access in LoRa mode */
	SX1272_SetOpMode(SX1272_OPMODE_STANDBY);
	/* some delay is needed? */
	for (volatile int i = 0; i < 10000; i++);
	/* store data in fifo */
	SX1272_WriteFifo(data, sizeof(data));

	/* store mode */
	lora_mode = LORA_TX;
	/* switch to tx mode to start tx */
	SX1272_SetOpMode(SX1272_OPMODE_TRANSMITTER);
}

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
	/* initialize spi */
	SPI1_Init();

	/* display version information */
	dprintf("LoRa hw = %s, sw = %s\n", HW_VER, SW_VER);

	/* initialize radio support */
	SX1272_Init();

	/* perform fsk experiment */
//	RadioFSK_Init();
	/* perform lora test */
	RadioLoRa_Init();

	/* endless loop */
	while (1) {
		/* kick the dog */
		Watchdog_Kick();
	}


	/* never reached */
	return 0;
}
