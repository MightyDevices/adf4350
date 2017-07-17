/*
 * sx1272.h
 *
 *  Created on: 29.06.2017
 *      Author: Tomek
 */

#ifndef DEV_SX1272_H_
#define DEV_SX1272_H_

#include <stdint.h>
#include <sys/cb.h>
#include <sys/ev.h>
#include <sys/sem.h>
#include <util/size.h>

/* semaphore */
extern sem_t sx1272_sem;
/* event */
extern ev_t sx1272_ev;

/* modulations */
#define SX1272_MOD_FSK								0x00
#define SX1272_MOD_OOK								0x20
#define SX1272_MOD_LORA								0x80

/* pulse shaping for fsk mode */
#define SX1272_SHAPEFSK_NONE						0x00
#define SX1272_SHAPEFSK_GAUSS_BT1_0					0x08
#define SX1272_SHAPEFSK_GAUSS_BT0_5					0x10
#define SX1272_SHAPEFSK_GAUSS_BT0_3					0x18

/* pulse shaping for ook mode */
#define SX1272_SHAPEOOK_NONE						0x00
#define SX1272_SHAPEOOK_BITRATE						0x08
#define SX1272_SHAPEOOK_2BITRATE					0x10

/* operation modes */
#define SX1272_OPMODE_SLEEP							0x00
#define SX1272_OPMODE_STANDBY						0x01
#define SX1272_OPMODE_SYNTHESIZER_TX				0x02
#define SX1272_OPMODE_TRANSMITTER					0x03
#define SX1272_OPMODE_SYNTHESIZER_RX				0x04
#define SX1272_OPMODE_RECEIVER						0x05
#define SX1272_OPMODE_RECEIVER_SINGLE				0x06
#define SX1272_OPMODE_CAD							0x07

/* pa select field */
#define SX1272_PA_RFO								0x00
#define SX1272_PA_BOOST								0x80

/* packet configuration */
#define SX1272_PKTCFG_LENGTH_FIX					0x0000
#define SX1272_PKTCFG_LENGTH_VAR					0x0080
#define SX1272_PKTCFG_ENC_NONE						0x0000
#define SX1272_PKTCFG_ENC_MANCHESTER				0x0020
#define SX1272_PKTCFG_ENC_WHITENING					0x0040
#define SX1272_PKTCFG_CRC_ON						0x0010
#define SX1272_PKTCFG_CRC_OFF						0x0000
#define SX1272_PKTCFG_CRC_AUTOCLEAR					0x0008
#define SX1272_PKTCFG_ADDRFLT_NONE					0x0000
#define SX1272_PKTCFG_ADDRFLT_NODE					0x0002
#define SX1272_PKTCFG_ADDRFLT_NODE_BCAST			0x0004
#define SX1272_PKTCFG_CRC_WHITEN_CCITT				0x0000
#define SX1272_PKTCFG_CRC_WHITEN_IBM				0x0001
#define SX1272_PKTCFG_DATAMODE_CONT					0x0000
#define SX1272_PKTCFG_DATAMODE_PKT					0x4000
#define SX1272_PKTCFG_BEACON						0x0800

/* dio mapping in continuous mode */
#define SX1272_DIOMAP_D0CNT_RX_SYNCADDR_TX_RDY		0x0000
#define SX1272_DIOMAP_D0CNT_RSSI_PREAMBLE_DET		0x0040
#define SX1272_DIOMAP_D0CNT_RX_RDY_TX_RDY			0x0080
#define SX1272_DIOMAP_D1CNT_DCLK					0x0000
#define SX1272_DIOMAP_D1CNT_RSSI_PREAMBLE_DET		0x0010
#define SX1272_DIOMAP_D2CNT_DATA					0x0000
#define SX1272_DIOMAP_D3CNT_RX_TOUT					0x0000
#define SX1272_DIOMAP_D3CNT_RSSI_PREAMBLE_DET		0x0001
#define SX1272_DIOMAP_D3CNT_TEMP_BATT				0x0003
#define SX1272_DIOMAP_D4CNT_TEMP_BATT				0x0000
#define SX1272_DIOMAP_D4CNT_PLL_LOCK				0x4000
#define SX1272_DIOMAP_D4CNT_RX_TOUT					0x8000
#define SX1272_DIOMAP_D4CNT_MODE_READY				0xC000
#define SX1272_DIOMAP_D5CNT_CLK_OUT					0x0000
#define SX1272_DIOMAP_D5CNT_PLL_LOCK				0x0100
#define SX1272_DIOMAP_D5CNT_RSSI_PREAMBLE_DET		0x0200
#define SX1272_DIOMAP_D5CNT_MODE_READY				0x0300

/* dio mapping in packet mode */
#define SX1272_DIOMAP_D0PKT_PAYLOAD_RDY_PCKT_SENT	0x0000
#define SX1272_DIOMAP_D0PKT_CRCOK					0x0040
#define SX1272_DIOMAP_D0PKT_TEMP_BATT				0x00C0
#define SX1272_DIOMAP_D1PKT_FIFO_LVL				0x0000
#define SX1272_DIOMAP_D1PKT_FIFO_EMPTY				0x0010
#define SX1272_DIOMAP_D1PKT_FIFO_FULL				0x0020
#define SX1272_DIOMAP_D2PKT_FIFO_FULL				0x0000
#define SX1272_DIOMAP_D2PKT_RX_RDY					0x0004
#define SX1272_DIOMAP_D2PKT_FIFO_FULL_RX_TOUT		0x0008
#define SX1272_DIOMAP_D2PKT_FIFO_FULL_RX_SYNCADDR	0x000C
#define SX1272_DIOMAP_D3PKT_FIFO_EMPTY				0x0000
#define SX1272_DIOMAP_D3PKT_TX_RDY					0x0004
#define SX1272_DIOMAP_D4PKT_TEMP_BATT				0x0000
#define SX1272_DIOMAP_D4PKT_PLL_LOCK				0x4000
#define SX1272_DIOMAP_D4PKT_RX_TOUT					0x8000
#define SX1272_DIOMAP_D4PKT_RSSI_PREAMBLE_DET		0xC000
#define SX1272_DIOMAP_D5PKT_CLK_OUT					0x0000
#define SX1272_DIOMAP_D5PKT_PLL_LOCK				0x0100
#define SX1272_DIOMAP_D5PKT_DATA					0x0200
#define SX1272_DIOMAP_D5PKT_MODE_READY				0x0300

/* dio mapping in LoRa mode */
#define SX1272_DIOMAP_D0LORA_RX_DONE				0x0000
#define SX1272_DIOMAP_D0LORA_TX_DONE				0x0040
#define SX1272_DIOMAP_D0LORA_CAD_DONE				0x0080
#define SX1272_DIOMAP_D1LORA_RX_TIMEOUT				0x0000
#define SX1272_DIOMAP_D1LORA_FHSS					0x0010
#define SX1272_DIOMAP_D1LORA_CAD_DETECTED			0x0020
#define SX1272_DIOMAP_D2LORA_FHSS					0x0000
#define SX1272_DIOMAP_D3LORA_CAD_DONE				0x0000
#define SX1272_DIOMAP_D3LORA_VALID_HDR				0x0001
#define SX1272_DIOMAP_D3LORA_CRC_ERR				0x0002
#define SX1272_DIOMAP_D4LORA_CAD_DETECTED			0x0000
#define SX1272_DIOMAP_D4LORA_PLL					0x4000
#define SX1272_DIOMAP_D5LORA_MODE_READY				0x0000
#define SX1272_DIOMAP_D5LORA_CLKOUT					0x1000


/* preamble polarity */
#define SX1272_PREAMBLE_AA							0x00
#define SX1272_PREAMBLE_55							0x20

/* sync config */
#define SX1272_SYNC_ON								0x10
#define SX1272_SYNC_OFF								0x00

/* sequencer modes */
#define SX1272_SEQ_START							0x0080
#define SX1272_SEQ_STOP								0x0040
#define SX1272_SEQ_IDLE_MODE_STDBY					0x0000
#define SX1272_SEQ_IDLE_MODE_SLEEP					0x0020
#define SX1272_SEQ_FROMSTART_LOWPOWER				0x0000
#define SX1272_SEQ_FROMSTART_RX						0x0008
#define SX1272_SEQ_FROMSTART_TX						0x0010
#define SX1272_SEQ_FROMSTART_TX_FIFOLVL				0x0018
#define SX1272_SEQ_LOWPOWER_SEQOFF_INIT				0x0000
#define SX1272_SEQ_LOWPOWER_IDLE					0x0004
#define SX1272_SEQ_FROMIDLE_TX						0x0000
#define SX1272_SEQ_FROMIDLE_RX						0x0002
#define SX1272_SEQ_FROMTX_LOWPOWER					0x0000
#define SX1272_SEQ_FROMTX_RX						0x0001
#define SX1272_SEQ_FROMRX_PKTRECVD_PLDRDY			0x2000
#define SX1272_SEQ_FROMRX_LOWPOWER_PLDRDY			0x4000
#define SX1272_SEQ_FROMRX_PKTRECVD_CRCOK			0x6000
#define SX1272_SEQ_FROMRX_SEQOFF_RSSI				0x8000
#define SX1272_SEQ_FROMRX_SEQOFF_SYNCADDR			0xA000
#define SX1272_SEQ_FROMRX_SEQOFF_PREAM				0xC000
#define SX1272_SEQ_FROMRXTOUT_RX_RESTART			0x0000
#define SX1272_SEQ_FROMRXTOUT_TX					0x0800
#define SX1272_SEQ_FROMRXTOUT_LOWPOWER				0x1000
#define SX1272_SEQ_FROMRXTOUT_SEQOFF				0x1800
#define SX1272_SEQ_FROMPKTRECVD_SEQOFF				0x0000
#define SX1272_SEQ_FROMPKTRECVD_TX_FIFOEMPTY		0x0100
#define SX1272_SEQ_FROMPKTRECVD_LOWPOWER			0x0200
#define SX1272_SEQ_FROMPKTRECVD_RX_FS				0x0300
#define SX1272_SEQ_FROMPKTRECVD_RX					0x0400

/* tx start modes */
#define SX1272_TXSTARTCOND_FIFOLVL					0x00
#define SX1272_TXSTARTCOND_FIFOEMPTY				0x80

/* lora modem configuration */
#define SX1272_LORAMODEM_BW_125K					0x0000
#define SX1272_LORAMODEM_BW_250K					0x0040
#define SX1272_LORAMODEM_BW_500K					0x0080
#define SX1272_LORAMODEM_CODING_4_5					0x0008
#define SX1272_LORAMODEM_CODING_4_6					0x0010
#define SX1272_LORAMODEM_CODING_4_7					0x0018
#define SX1272_LORAMODEM_CODING_4_8					0x0020
#define SX1272_LORAMODEM_HDR_IMPLICIT				0x0004
#define SX1272_LORAMODEM_HDR_EXPLICIT				0x0000
#define SX1272_LORAMODEM_CRC_ON						0x0002
#define SX1272_LORAMODEM_CRC_OFF					0x0000
#define SX1272_LORAMODEM_SF_6						0x6000
#define SX1272_LORAMODEM_SF_7						0x7000
#define SX1272_LORAMODEM_SF_8						0x8000
#define SX1272_LORAMODEM_SF_9						0x9000
#define SX1272_LORAMODEM_SF_10						0xA000
#define SX1272_LORAMODEM_SF_11						0xB000
#define SX1272_LORAMODEM_SF_12						0xC000
#define SX1272_LORAMODEM_TX_SINGLE					0x0000
#define SX1272_LORAMODEM_TX_CONT					0x0800
#define SX1272_LORAMODEM_AGC_OFF					0x0000
#define SX1272_LORAMODEM_AGC_ON						0x0800

/* lora interrupt flags */
#define SX1272_LORAIRQ_RX_TIMEOUT					0x80
#define SX1272_LORAIRQ_RX_DONE						0x40
#define SX1272_LORAIRQ_CRC_ERR						0x20
#define SX1272_LORAIRQ_VALID_HDR					0x10
#define SX1272_LORAIRQ_TX_DONE						0x08
#define SX1272_LORAIRQ_CAD_DONE						0x04
#define SX1272_LORAIRQ_FHSS							0x02
#define SX1272_LORAIRQ_CAD_DETECTED					0x01

/* interrupt routine for DIO0 */
void SX1272_Dio0Exti1Isr(void);
/* interrupt routine for DIO1 */
void SX1272_Dio1Exti10Isr(void);
/* interrupt routine for DIO2 */
void SX1272_Dio2Exti11Isr(void);
/* interrupt routine for DIO3 */
void SX1272_Dio3Exti7Isr(void);
/* interrupt routine for DIO4 */
void SX1272_Dio4Exti5Isr(void);
/* interrupt routine for DIO5 */
void SX1272_Dio5Exti4Isr(void);


/* initialize sx chip */
int SX1272_Init(void);

/* set current modulation scheme */
int SX1272_SetModulation(uint8_t type, uint8_t shaping);
/* set bitrate */
int SX1272_SetBitrate(uint32_t bit_rate);
/* set frequency deviation */
int SX1272_SetDeviation(uint32_t deviation);
/* set center frequency */
int SX1272_SetFrequency(uint32_t freq);
/* set output power */
int SX1272_SetOutputPower(uint8_t pa_select, uint8_t dbm);
/* set preamble and sync */
int SX1272_SetPreambleConfig(uint16_t pream_len, uint8_t polarity);
/* set sync configuration */
int SX1272_SetSyncConfig(uint8_t on, uint8_t *sync, uint8_t size);
/* set packet configuration */
int SX1272_SetPacketConfig(uint32_t flags, uint16_t length);
/* configure addresses */
int SX1272_SetAddress(uint8_t node, uint8_t bcast);
/* pin mapping */
int SX1272_SetDIOMapping(uint16_t mapping);
/* set operation mode */
int SX1272_SetOpMode(uint8_t mode);
/* prepare sequencer */
int SX1272_SetSequencer(uint16_t seq);
/* configure fifo threshold and set tx start condition */
int SX1272_SetFifoThreshold(uint8_t threshold, uint8_t start_cond);
/* returns interrupt flags */
int SX1272_GetIrqFlags(uint16_t *flags);
/* returns current mode */
int SX1272_GetOpMode(uint8_t *mode);
/* write data to fifo */
int SX1272_WriteFifo(void *ptr, size_t size);
/* read data from fifo */
int SX1272_ReadFifo(void *ptr, size_t size);


/* configure modem */
int SX1272_LoRaConfigureModem(uint16_t flags, uint8_t rx_timeout);
/* set preable length */
int SX1272_LoRaSetPreamble(uint8_t length);
/* set sync word */
int SX1272_LoRaSetSyncWord(uint8_t sync);
/* configure fifo */
int SX1272_LoRaConfigureFifo(uint8_t addr, uint8_t tx_base, uint8_t rx_base);
/* get received packet information */
int SX1272_LoRaGetRxPacketInfo(uint8_t *start_addr, uint8_t *nb_bytes);
/* set payload length */
int SX1272_LoRaSetPayloadLength(uint8_t length);
/* set interrupt mask */
int SX1272_LoRaSetIrqMask(uint8_t mask);
/* read interrupt flags */
int SX1272_LoRaGetIrqFlags(uint8_t *flags);
/* clear interrupt flags */
int SX1272_LoRaClearIrqFlags(uint8_t flags);

int SX1272_Test(uint8_t arg);

#endif /* DEV_SX1272_H_ */
