/*
 * sx1272_regs.h
 *
 *  Created on: 30.06.2017
 *      Author: Tomek
 */

#ifndef DEV_SX1272_REGS_H_
#define DEV_SX1272_REGS_H_


/* FSK MODE REGISTERS */
/* register addresses */
#define REG_FIFO									    0x00
#define REG_OPMODE									    0x01
#define REG_BITRATE_MSB								    0x02
#define REG_BITRATE_LSB								    0x03
#define REG_FDEV_MSB								    0x04
#define REG_FDEV_LSB								    0x05
#define REG_FRF_MSB									    0x06
#define REG_FRF_MID									    0x07
#define REG_FRF_LSB									    0x08
#define REG_PA_CONFIG								    0x09
#define REG_PA_RAMP									    0x0A
#define REG_OCP										    0x0B
#define REG_LNA										    0x0C
#define REG_RX_CONFIG								    0x0D
#define REG_RSSI_CONFIG								    0x0E
#define REG_RSSI_COLLISION							    0x0F
#define REG_RSSI_THRESH								    0x10
#define REG_RSSI_VALUE								    0x11
#define REG_RX_BW									    0x12
#define REG_AFC_BW									    0x13
#define REG_OOK_PEAK								    0x14
#define REG_OOK_FIX									    0x15
#define REG_OOK_AVG									    0x16
#define REG_AFC_FEI									    0x1A
#define REG_AFC_MSB									    0x1B
#define REG_AFC_LSB									    0x1C
#define REG_FEI_MSB									    0x1D
#define REG_FEI_LSB									    0x1E
#define REG_PREAMBLE_DETECT							    0x1F
#define REG_RX_TIMEOUT1								    0x20
#define REG_RX_TIMEOUT2								    0x21
#define REG_RX_TIMEOUT3								    0x22
#define REG_RX_DELAY								    0x23
#define REG_OSC										    0x24
#define REG_PREAMBLE_MSB							    0x25
#define REG_PREAMBLE_LSB							    0x26
#define REG_SYNC_CONFIG								    0x27
#define REG_SYNC_VALUE1								    0x28
#define REG_SYNC_VALUE2								    0x29
#define REG_SYNC_VALUE3								    0x2A
#define REG_SYNC_VALUE4								    0x2B
#define REG_SYNC_VALUE5								    0x2C
#define REG_SYNC_VALUE6								    0x2D
#define REG_SYNC_VALUE7								    0x2E
#define REG_SYNC_VALUE8								    0x2F
#define REG_PACKET_CONFIG1							    0x30
#define REG_PACKET_CONFIG2							    0x31
#define REG_PAYLOAD_LENGTH							    0x32
#define REG_NODE_ADRS								    0x33
#define REG_BROADCAST_ADRS							    0x34
#define REG_FIFO_THRESH								    0x35
#define REG_SEQ_CONFIG1								    0x36
#define REG_SEQ_CONFIG2								    0x37
#define REG_TIMER_RESOL								    0x38
#define REG_TIMER1_COEF								    0x39
#define REG_TIMER2_COEF								    0x3A
#define REG_IMAGE_CAL								    0x3B
#define REG_TEMP									    0x3C
#define REG_LOW_BAT									    0x3D
#define REG_IRQ_FLAGS1								    0x3E
#define REG_IRQ_FLAGS2								    0x3F
#define REG_DIO_MAPPING1							    0x40
#define REG_DIO_MAPPING2							    0x41
#define REG_VERSION									    0x42
#define REG_AGC_REF									    0x43
#define REG_AGC_TRESH1								    0x44
#define REG_AGC_TRESH2								    0x45
#define REG_AGC_TRESH3								    0x46
#define REG_PLL_HOP									    0x4B
#define REG_TCXO									    0x58
#define REG_PA_DAC									    0x5A
#define REG_PLL										    0x5C
#define REG_PLL_LOW_PN								    0x5E
#define REG_FORMER_TEMP								    0x6C
#define REG_BITRATE_FRAC							    0x70

/* bit definitions for OPMODE register */
#define REG_OPMODE_LONGRANGEMODE                	    0x80
#define REG_OPMODE_LONGRANGEMODE_OFF                    0x00
#define REG_OPMODE_LONGRANGEMODE_ON                     0x80
#define REG_OPMODE_MODULATIONTYPE               	    0x60
#define REG_OPMODE_MODULATIONTYPE_FSK                   0x00
#define REG_OPMODE_MODULATIONTYPE_OOK                   0x20
#define REG_OPMODE_MODULATIONSHAPING            	    0x18
#define REG_OPMODE_MODULATIONSHAPING_00                 0x00
#define REG_OPMODE_MODULATIONSHAPING_01                 0x08
#define REG_OPMODE_MODULATIONSHAPING_10                 0x10
#define REG_OPMODE_MODULATIONSHAPING_11                 0x18
#define REG_OPMODE_STATE                        	    0x07
#define REG_OPMODE_STATE_SLEEP                          0x00
#define REG_OPMODE_STATE_STANDBY                        0x01
#define REG_OPMODE_STATE_SYNTHESIZER_TX                 0x02
#define REG_OPMODE_STATE_TRANSMITTER                    0x03
#define REG_OPMODE_STATE_SYNTHESIZER_RX                 0x04
#define REG_OPMODE_STATE_RECEIVER                       0x05

/* bit definitions for PACONFIG register */
#define REG_PACONFIG_PASELECT                   	    0x80
#define REG_PACONFIG_PASELECT_PABOOST                   0x80
#define REG_PACONFIG_PASELECT_RFO                       0x00
#define REG_PACONFIG_OUTPUTPOWER                	    0x0F

/* bit definitions for PARAMP register */
#define REG_PARAMP_LOWPNTXPLL                   	    0x10
#define REG_PARAMP_LOWPNTXPLL_OFF                       0x10
#define REG_PARAMP_LOWPNTXPLL_ON                        0x00
#define REG_PARAMP                                      0x0F
#define REG_PARAMP_3400_US                              0x00
#define REG_PARAMP_2000_US                              0x01
#define REG_PARAMP_1000_US                              0x02
#define REG_PARAMP_0500_US                              0x03
#define REG_PARAMP_0250_US                              0x04
#define REG_PARAMP_0125_US                              0x05
#define REG_PARAMP_0100_US                              0x06
#define REG_PARAMP_0062_US                              0x07
#define REG_PARAMP_0050_US                              0x08
#define REG_PARAMP_0040_US                              0x09
#define REG_PARAMP_0031_US                              0x0A
#define REG_PARAMP_0025_US                              0x0B
#define REG_PARAMP_0020_US                              0x0C
#define REG_PARAMP_0015_US                              0x0D
#define REG_PARAMP_0012_US                              0x0E
#define REG_PARAMP_0010_US                              0x0F

/* bit definitions for OCP register */
#define REG_OCP_ON                                      0x20
#define REG_OCP_OFF                                     0x00
#define REG_OCP_TRIM                            	    0x1F
#define REG_OCP_TRIM_045_MA                             0x00
#define REG_OCP_TRIM_050_MA                             0x01
#define REG_OCP_TRIM_055_MA                             0x02
#define REG_OCP_TRIM_060_MA                             0x03
#define REG_OCP_TRIM_065_MA                             0x04
#define REG_OCP_TRIM_070_MA                             0x05
#define REG_OCP_TRIM_075_MA                             0x06
#define REG_OCP_TRIM_080_MA                             0x07
#define REG_OCP_TRIM_085_MA                             0x08
#define REG_OCP_TRIM_090_MA                             0x09
#define REG_OCP_TRIM_095_MA                             0x0A
#define REG_OCP_TRIM_100_MA                             0x0B
#define REG_OCP_TRIM_105_MA                             0x0C
#define REG_OCP_TRIM_110_MA                             0x0D
#define REG_OCP_TRIM_115_MA                             0x0E
#define REG_OCP_TRIM_120_MA                             0x0F
#define REG_OCP_TRIM_130_MA                             0x10
#define REG_OCP_TRIM_140_MA                             0x11
#define REG_OCP_TRIM_150_MA                             0x12
#define REG_OCP_TRIM_160_MA                             0x13
#define REG_OCP_TRIM_170_MA                             0x14
#define REG_OCP_TRIM_180_MA                             0x15
#define REG_OCP_TRIM_190_MA                             0x16
#define REG_OCP_TRIM_200_MA                             0x17
#define REG_OCP_TRIM_210_MA                             0x18
#define REG_OCP_TRIM_220_MA                             0x19
#define REG_OCP_TRIM_230_MA                             0x1A
#define REG_OCP_TRIM_240_MA                             0x1B

/* bit definitions for LNA register */
#define REG_LNA_GAIN                           		    0xE0
#define REG_LNA_GAIN_G1                                 0x20
#define REG_LNA_GAIN_G2                                 0x40
#define REG_LNA_GAIN_G3                                 0x60
#define REG_LNA_GAIN_G4                                 0x80
#define REG_LNA_GAIN_G5                                 0xA0
#define REG_LNA_GAIN_G6                                 0xC0
#define REG_LNA_BOOST                           	    0x03
#define REG_LNA_BOOST_OFF                               0x00
#define REG_LNA_BOOST_ON                                0x03

/* bit definitions for RXCONFIG register */
#define REG_RX_CONFIG_RESTARTRXONCOLLISION              0x80
#define REG_RX_CONFIG_RESTARTRXONCOLLISION_ON           0x80
#define REG_RX_CONFIG_RESTARTRXONCOLLISION_OFF          0x00
#define REG_RX_CONFIG_RESTARTRXWITHOUTPLLLOCK           0x40
#define REG_RX_CONFIG_RESTARTRXWITHPLLLOCK              0x20
#define REG_RX_CONFIG_AFCAUTO		                    0x10
#define REG_RX_CONFIG_AFCAUTO_ON                        0x10
#define REG_RX_CONFIG_AFCAUTO_OFF                       0x00
#define REG_RX_CONFIG_AGCAUTO		                    0x08
#define REG_RX_CONFIG_AGCAUTO_ON                        0x08
#define REG_RX_CONFIG_AGCAUTO_OFF                       0x00
#define REG_RX_CONFIG_RXTRIGER		               	    0x01
#define REG_RX_CONFIG_RXTRIGER_OFF                      0x00
#define REG_RX_CONFIG_RXTRIGER_RSSI                     0x01
#define REG_RX_CONFIG_RXTRIGER_PREAMBLEDETECT           0x06
#define REG_RX_CONFIG_RXTRIGER_RSSI_PREAMBLEDETECT      0x07

/* bit definitions for RSSICONFIG register */
#define REG_RSSI_CONFIG_OFFSET		               	    0xF8
#define REG_RSSI_CONFIG_SMOOTHING		                0x07
#define REG_RSSI_CONFIG_SMOOTHING_2                     0x00
#define REG_RSSI_CONFIG_SMOOTHING_4                     0x01
#define REG_RSSI_CONFIG_SMOOTHING_8                     0x02
#define REG_RSSI_CONFIG_SMOOTHING_16                    0x03
#define REG_RSSI_CONFIG_SMOOTHING_32                    0x04
#define REG_RSSI_CONFIG_SMOOTHING_64                    0x05
#define REG_RSSI_CONFIG_SMOOTHING_128                   0x06
#define REG_RSSI_CONFIG_SMOOTHING_256                   0x07

/* bit definitions for RSSICOLLISION register */
#define REG_RSSICOLISION_THRESHOLD                      0x0A

/* bit definitions for RSSITHRESH register */
#define REG_RSSITHRESH_THRESHOLD                        0xFF

/* bit definitions for RXBW register */
#define REG_RX_BW_MANT                           	    0x18
#define REG_RX_BW_MANT_16                               0x00
#define REG_RX_BW_MANT_20                               0x08
#define REG_RX_BW_MANT_24                               0x10
#define REG_RX_BW_EXP		                            0x07
#define REG_RX_BW_EXP_0                                 0x00
#define REG_RX_BW_EXP_1                                 0x01
#define REG_RX_BW_EXP_2                                 0x02
#define REG_RX_BW_EXP_3                                 0x03
#define REG_RX_BW_EXP_4                                 0x04
#define REG_RX_BW_EXP_5                                 0x05
#define REG_RX_BW_EXP_6                                 0x06
#define REG_RX_BW_EXP_7                                 0x07

/* bit definitions for RXBW register */
#define REG_AFC_BW_MANTAFC	                       	    0x18
#define REG_AFC_BW_MANTAFC_16                           0x00
#define REG_AFC_BW_MANTAFC_20                           0x08
#define REG_AFC_BW_MANTAFC_24                           0x10
#define REG_AFC_BW_EXPAFC		                        0x07
#define REG_AFC_BW_EXPAFC_0                             0x00
#define REG_AFC_BW_EXPAFC_1                             0x01
#define REG_AFC_BW_EXPAFC_2                             0x02
#define REG_AFC_BW_EXPAFC_3                             0x03
#define REG_AFC_BW_EXPAFC_4                             0x04
#define REG_AFC_BW_EXPAFC_5                             0x05
#define REG_AFC_BW_EXPAFC_6                             0x06
#define REG_AFC_BW_EXPAFC_7                             0x07

/* bit definitions for OOKPEAK register */
#define REG_OOK_PEAK_BITSYNC		                   	0x2F
#define REG_OOK_PEAK_BITSYNC_ON                         0x20
#define REG_OOK_PEAK_BITSYNC_OFF                        0x00
#define REG_OOK_PEAK_OOKTHRESHTYPE               	    0x18
#define REG_OOK_PEAK_OOKTHRESHTYPE_FIXED                0x00
#define REG_OOK_PEAK_OOKTHRESHTYPE_PEAK                 0x08
#define REG_OOK_PEAK_OOKTHRESHTYPE_AVERAGE              0x10
#define REG_OOK_PEAK_OOKPEAKTHRESHSTEP	           	    0x07
#define REG_OOK_PEAK_OOKPEAKTHRESHSTEP_0_5_DB           0x00
#define REG_OOK_PEAK_OOKPEAKTHRESHSTEP_1_0_DB           0x01
#define REG_OOK_PEAK_OOKPEAKTHRESHSTEP_1_5_DB           0x02
#define REG_OOK_PEAK_OOKPEAKTHRESHSTEP_2_0_DB           0x03
#define REG_OOK_PEAK_OOKPEAKTHRESHSTEP_3_0_DB           0x04
#define REG_OOK_PEAK_OOKPEAKTHRESHSTEP_4_0_DB           0x05
#define REG_OOK_PEAK_OOKPEAKTHRESHSTEP_5_0_DB           0x06
#define REG_OOK_PEAK_OOKPEAKTHRESHSTEP_6_0_DB           0x07

/* bit definitions for OOKFIX register */
#define REG_OOKFIX_OOKFIXEDTHRESHOLD                    0x0C

/* bit definitions for OOKAVG register */
#define REG_OOK_AVG_OOKPEAKTHRESHDEC             	    0xE0
#define REG_OOK_AVG_OOKPEAKTHRESHDEC_000                0x00
#define REG_OOK_AVG_OOKPEAKTHRESHDEC_001                0x20
#define REG_OOK_AVG_OOKPEAKTHRESHDEC_010                0x40
#define REG_OOK_AVG_OOKPEAKTHRESHDEC_011                0x60
#define REG_OOK_AVG_OOKPEAKTHRESHDEC_100                0x80
#define REG_OOK_AVG_OOKPEAKTHRESHDEC_101                0xA0
#define REG_OOK_AVG_OOKPEAKTHRESHDEC_110                0xC0
#define REG_OOK_AVG_OOKPEAKTHRESHDEC_111                0xE0
#define REG_OOK_AVG_AVERAGEOFFSET                	    0x0C
#define REG_OOK_AVG_AVERAGEOFFSET_0_DB                  0x00
#define REG_OOK_AVG_AVERAGEOFFSET_2_DB                  0x04
#define REG_OOK_AVG_AVERAGEOFFSET_4_DB                  0x08
#define REG_OOK_AVG_AVERAGEOFFSET_6_DB                  0x0C
#define REG_OOK_AVG_OOKAVERAGETHRESHFILT         	    0x03
#define REG_OOK_AVG_OOKAVERAGETHRESHFILT_00             0x00
#define REG_OOK_AVG_OOKAVERAGETHRESHFILT_01             0x01
#define REG_OOK_AVG_OOKAVERAGETHRESHFILT_10             0x02
#define REG_OOK_AVG_OOKAVERAGETHRESHFILT_11             0x03

/* bit definitions for AFCFEI register */
#define REG_AFC_FEI_AGCSTART                            0x10
#define REG_AFC_FEI_AFCCLEAR                            0x02
#define REG_AFC_FEI_AFCAUTOCLEAR		               	0x01
#define REG_AFC_FEI_AFCAUTOCLEAR_ON                     0x01
#define REG_AFC_FEI_AFCAUTOCLEAR_OFF                    0x00

/* bit definitions for PREAMBLEDETECT register */
#define REG_PREAMBLE_DETECT_DETECTOR             	    0x80
#define REG_PREAMBLE_DETECT_DETECTOR_ON                 0x80
#define REG_PREAMBLE_DETECT_DETECTOR_OFF                0x00
#define REG_PREAMBLE_DETECT_DETECTORSIZE         	    0x60
#define REG_PREAMBLE_DETECT_DETECTORSIZE_1              0x00
#define REG_PREAMBLE_DETECT_DETECTORSIZE_2              0x20
#define REG_PREAMBLE_DETECT_DETECTORSIZE_3              0x40
#define REG_PREAMBLE_DETECT_DETECTORSIZE_4              0x60
#define REG_PREAMBLE_DETECT_DETECTORTOL          	    0x1F
#define REG_PREAMBLE_DETECT_DETECTORTOL_0               0x00
#define REG_PREAMBLE_DETECT_DETECTORTOL_1               0x01
#define REG_PREAMBLE_DETECT_DETECTORTOL_2               0x02
#define REG_PREAMBLE_DETECT_DETECTORTOL_3               0x03
#define REG_PREAMBLE_DETECT_DETECTORTOL_4               0x04
#define REG_PREAMBLE_DETECT_DETECTORTOL_5               0x05
#define REG_PREAMBLE_DETECT_DETECTORTOL_6               0x06
#define REG_PREAMBLE_DETECT_DETECTORTOL_7               0x07
#define REG_PREAMBLE_DETECT_DETECTORTOL_8               0x08
#define REG_PREAMBLE_DETECT_DETECTORTOL_9               0x09
#define REG_PREAMBLE_DETECT_DETECTORTOL_10              0x0A
#define REG_PREAMBLE_DETECT_DETECTORTOL_11              0x0B
#define REG_PREAMBLE_DETECT_DETECTORTOL_12              0x0C
#define REG_PREAMBLE_DETECT_DETECTORTOL_13              0x0D
#define REG_PREAMBLE_DETECT_DETECTORTOL_14              0x0E
#define REG_PREAMBLE_DETECT_DETECTORTOL_15              0x0F
#define REG_PREAMBLE_DETECT_DETECTORTOL_16              0x10
#define REG_PREAMBLE_DETECT_DETECTORTOL_17              0x11
#define REG_PREAMBLE_DETECT_DETECTORTOL_18              0x12
#define REG_PREAMBLE_DETECT_DETECTORTOL_19              0x13
#define REG_PREAMBLE_DETECT_DETECTORTOL_20              0x14
#define REG_PREAMBLE_DETECT_DETECTORTOL_21              0x15
#define REG_PREAMBLE_DETECT_DETECTORTOL_22              0x16
#define REG_PREAMBLE_DETECT_DETECTORTOL_23              0x17
#define REG_PREAMBLE_DETECT_DETECTORTOL_24              0x18
#define REG_PREAMBLE_DETECT_DETECTORTOL_25              0x19
#define REG_PREAMBLE_DETECT_DETECTORTOL_26              0x1A
#define REG_PREAMBLE_DETECT_DETECTORTOL_27              0x1B
#define REG_PREAMBLE_DETECT_DETECTORTOL_28              0x1C
#define REG_PREAMBLE_DETECT_DETECTORTOL_29              0x1D
#define REG_PREAMBLE_DETECT_DETECTORTOL_30              0x1E
#define REG_PREAMBLE_DETECT_DETECTORTOL_31              0x1F

/* bit definitions for RXTIMEOUT1 register */
#define REG_RX_TIMEOUT1_TIMEOUTRXRSSI                   0x00

/* bit definitions for RXTIMEOUT2 register */
#define REG_RX_TIMEOUT2_TIMEOUTRXPREAMBLE               0x00

/* bit definitions for RXTIMEOUT3 register */
#define REG_RX_TIMEOUT3_TIMEOUTSIGNALSYNC               0x00

/* bit definitions for RXDELAY register */
#define REG_RX_DELAY_INTERPACKETRXDELAY                 0x00

/* bit definitions for OSC register */
#define REG_OSC_RCCALSTART                              0x08
#define REG_OSC_CLKOUT                          	    0x07
#define REG_OSC_CLKOUT_32_MHZ                           0x00
#define REG_OSC_CLKOUT_16_MHZ                           0x01
#define REG_OSC_CLKOUT_8_MHZ                            0x02
#define REG_OSC_CLKOUT_4_MHZ                            0x03
#define REG_OSC_CLKOUT_2_MHZ                            0x04
#define REG_OSC_CLKOUT_1_MHZ                            0x05
#define REG_OSC_CLKOUT_RC                               0x06
#define REG_OSC_CLKOUT_OFF                              0x07

/* bit definitions for SYNCCONFIG register */
#define REG_SYNC_CONFIG_AUTORESTARTRXMODE        	    0xC0
#define REG_SYNC_CONFIG_AUTORESTARTRXMODE_WAITPLL_ON    0x80
#define REG_SYNC_CONFIG_AUTORESTARTRXMODE_WAITPLL_OFF   0x40
#define REG_SYNC_CONFIG_AUTORESTARTRXMODE_OFF           0x00
#define REG_SYNC_CONFIG_PREAMBLEPOLARITY         	    0x20
#define REG_SYNC_CONFIG_PREAMBLEPOLARITY_55             0x20
#define REG_SYNC_CONFIG_PREAMBLEPOLARITY_AA             0x00
#define REG_SYNC_CONFIG_SYNC                     	    0x10
#define REG_SYNC_CONFIG_SYNC_ON                         0x10
#define REG_SYNC_CONFIG_SYNC_OFF                        0x00
#define REG_SYNC_CONFIG_FIFOFILLCONDITION       		0x08
#define REG_SYNC_CONFIG_FIFOFILLCONDITION_AUTO          0x00
#define REG_SYNC_CONFIG_FIFOFILLCONDITION_MANUAL        0x08
#define REG_SYNC_CONFIG_SYNCSIZE                 	    0x07
#define REG_SYNC_CONFIG_SYNCSIZE_1                      0x00
#define REG_SYNC_CONFIG_SYNCSIZE_2                      0x01
#define REG_SYNC_CONFIG_SYNCSIZE_3                      0x02
#define REG_SYNC_CONFIG_SYNCSIZE_4                      0x03
#define REG_SYNC_CONFIG_SYNCSIZE_5                      0x04
#define REG_SYNC_CONFIG_SYNCSIZE_6                      0x05
#define REG_SYNC_CONFIG_SYNCSIZE_7                      0x06
#define REG_SYNC_CONFIG_SYNCSIZE_8                      0x07

/* bit definitions for PACKETCONFIG1 register */
#define REG_PACKET_CONFIG1_PACKETFORMAT          	    0x80
#define REG_PACKET_CONFIG1_PACKETFORMAT_FIXED           0x00
#define REG_PACKET_CONFIG1_PACKETFORMAT_VARIABLE        0x80
#define REG_PACKET_CONFIG1_DCFREE                	    0x60
#define REG_PACKET_CONFIG1_DCFREE_OFF                   0x00
#define REG_PACKET_CONFIG1_DCFREE_MANCHESTER            0x20
#define REG_PACKET_CONFIG1_DCFREE_WHITENING             0x40
#define REG_PACKET_CONFIG1_CRC                   	    0x10
#define REG_PACKET_CONFIG1_CRC_ON                       0x10
#define REG_PACKET_CONFIG1_CRC_OFF                      0x00
#define REG_PACKET_CONFIG1_CRCAUTOCLEAR          	    0x08
#define REG_PACKET_CONFIG1_CRCAUTOCLEAR_ON              0x00
#define REG_PACKET_CONFIG1_CRCAUTOCLEAR_OFF             0x08
#define REG_PACKET_CONFIG1_ADDRSFILTERING        	    0x06
#define REG_PACKET_CONFIG1_ADDRSFILTERING_OFF           0x00
#define REG_PACKET_CONFIG1_ADDRSFILTERING_NODE          0x02
#define REG_PACKET_CONFIG1_ADDRSFILTERING_NODEBCAST 	0x04
#define REG_PACKET_CONFIG1_CRCWHITENINGTYPE      	    0x01
#define REG_PACKET_CONFIG1_CRCWHITENINGTYPE_CCITT       0x00
#define REG_PACKET_CONFIG1_CRCWHITENINGTYPE_IBM         0x01

/* bit definitions for PACKETCONFIG2 register */
#define REG_PACKET_CONFIG2_DATAMODE              	    0x40
#define REG_PACKET_CONFIG2_DATAMODE_CONTINUOUS          0x00
#define REG_PACKET_CONFIG2_DATAMODE_PACKET              0x40
#define REG_PACKET_CONFIG2_IOHOME                	    0x20
#define REG_PACKET_CONFIG2_IOHOME_ON                    0x20
#define REG_PACKET_CONFIG2_IOHOME_OFF                   0x00
#define REG_PACKET_CONFIG2_BEACON                	    0x08
#define REG_PACKET_CONFIG2_BEACON_ON                    0x08
#define REG_PACKET_CONFIG2_BEACON_OFF                   0x00
#define REG_PACKET_CONFIG2_PAYLOADLENGTH_MSB     	    0x07

/* bit definitions for FIFOTHRESH register */
#define REG_FIFO_THRESH_TXSTARTCONDITION         	    0x80
#define REG_FIFO_THRESH_TXSTARTCONDITION_FIFOTHRESH     0x00
#define REG_FIFO_THRESH_TXSTARTCONDITION_FIFONOTEMPTY   0x80
#define REG_FIFO_THRESH_FIFOTHRESHOLD            	    0x3F
#define REG_FIFO_THRESH_FIFOTHRESHOLD_THRESHOLD         0x0F

/* bit definitions for SEQCONFIG1 register */
#define REG_SEQ_CONFIG1_SEQUENCER_START                 0x80
#define REG_SEQ_CONFIG1_SEQUENCER_STOP                  0x40
#define REG_SEQ_CONFIG1_IDLEMODE                 	    0x20
#define REG_SEQ_CONFIG1_IDLEMODE_SLEEP                  0x20
#define REG_SEQ_CONFIG1_IDLEMODE_STANDBY                0x00
#define REG_SEQ_CONFIG1_FROMSTART                	    0x18
#define REG_SEQ_CONFIG1_FROMSTART_TOLPS                 0x00
#define REG_SEQ_CONFIG1_FROMSTART_TORX                  0x08
#define REG_SEQ_CONFIG1_FROMSTART_TOTX                  0x10
#define REG_SEQ_CONFIG1_FROMSTART_TOTX_ONFIFOLEVEL      0x18
#define REG_SEQ_CONFIG1_LPS                      	    0x04
#define REG_SEQ_CONFIG1_LPS_SEQUENCER_OFF               0x00
#define REG_SEQ_CONFIG1_LPS_IDLE                        0x04
#define REG_SEQ_CONFIG1_FROMIDLE                 	    0x02
#define REG_SEQ_CONFIG1_FROMIDLE_TOTX                   0x00
#define REG_SEQ_CONFIG1_FROMIDLE_TORX                   0x02
#define REG_SEQ_CONFIG1_FROMTX                   	    0x01
#define REG_SEQ_CONFIG1_FROMTX_TOLPS                    0x00
#define REG_SEQ_CONFIG1_FROMTX_TORX                     0x01

/* bit definitions for SEQCONFIG2 register */
#define REG_SEQ_CONFIG2_FROMRX                   	    0xE0
#define REG_SEQ_CONFIG2_FROMRX_TOUNUSED_000             0x00
#define REG_SEQ_CONFIG2_FROMRX_TORXPKT_ONPLDRDY         0x20
#define REG_SEQ_CONFIG2_FROMRX_TOLPS_ONPLDRDY           0x40
#define REG_SEQ_CONFIG2_FROMRX_TORXPKT_ONCRCOK          0x60
#define REG_SEQ_CONFIG2_FROMRX_TOSEQUENCEROFF_ONRSSI    0x80
#define REG_SEQ_CONFIG2_FROMRX_TOSEQUENCEROFF_ONSYNC    0xA0
#define REG_SEQ_CONFIG2_FROMRX_TOSEQUENCEROFF_ONPREA    0xC0
#define REG_SEQ_CONFIG2_FROMRX_TOUNUSED_111             0xE0
#define REG_SEQ_CONFIG2_FROMRXTIMEOUT            	    0x18
#define REG_SEQ_CONFIG2_FROMRXTIMEOUT_TORXRESTART       0x00
#define REG_SEQ_CONFIG2_FROMRXTIMEOUT_TOTX              0x08
#define REG_SEQ_CONFIG2_FROMRXTIMEOUT_TOLPS             0x10
#define REG_SEQ_CONFIG2_FROMRXTIMEOUT_TOSEQUENCEROFF    0x18
#define REG_SEQ_CONFIG2_FROMRXPKT                	    0x07
#define REG_SEQ_CONFIG2_FROMRXPKT_TOSEQUENCEROFF        0x00
#define REG_SEQ_CONFIG2_FROMRXPKT_TOTX_ONFIFOEMPTY      0x01
#define REG_SEQ_CONFIG2_FROMRXPKT_TOLPS                 0x02
#define REG_SEQ_CONFIG2_FROMRXPKT_TOSYNTHESIZERRX       0x03
#define REG_SEQ_CONFIG2_FROMRXPKT_TORX                  0x04

/* bit definitions for TIMERRESOL register */
#define REG_TIMER_RESOL_TIMER1RESO              		0x0C
#define REG_TIMER_RESOL_TIMER1RESOL_OFF                 0x00
#define REG_TIMER_RESOL_TIMER1RESOL_000064_US           0x04
#define REG_TIMER_RESOL_TIMER1RESOL_004100_US           0x08
#define REG_TIMER_RESOL_TIMER1RESOL_262000_US           0x0C
#define REG_TIMER_RESOL_TIMER2RESOL              	    0x03
#define REG_TIMER_RESOL_TIMER2RESOL_OFF                 0x00
#define REG_TIMER_RESOL_TIMER2RESOL_000064_US           0x01
#define REG_TIMER_RESOL_TIMER2RESOL_004100_US           0x02
#define REG_TIMER_RESOL_TIMER2RESOL_262000_US           0x03

/* bit definitions for IMAGECAL register */
#define REG_IMAGE_CAL_AUTOIMAGECAL               	    0x80
#define REG_IMAGE_CAL_AUTOIMAGECAL_ON                  	0x80
#define REG_IMAGE_CAL_AUTOIMAGECAL_OFF                  0x00
#define REG_IMAGE_CAL_IMAGECAL                   	    0x40
#define REG_IMAGE_CAL_IMAGECAL_START                    0x40
#define REG_IMAGE_CAL_IMAGECAL_RUNNING                  0x20
#define REG_IMAGE_CAL_IMAGECAL_DONE                     0x00
#define REG_IMAGE_CAL_TEMPCHANGE_HIGHER                 0x08
#define REG_IMAGE_CAL_TEMPCHANGE_LOWER                  0x00
#define REG_IMAGE_CAL_TEMPTHRESHOLD              	    0x06
#define REG_IMAGE_CAL_TEMPTHRESHOLD_05                  0x00
#define REG_IMAGE_CAL_TEMPTHRESHOLD_10                  0x02
#define REG_IMAGE_CAL_TEMPTHRESHOLD_15                  0x04
#define REG_IMAGE_CAL_TEMPTHRESHOLD_20                  0x06
#define REG_IMAGE_CAL_TEMPMONITOR                	    0x01
#define REG_IMAGE_CAL_TEMPMONITOR_ON                    0x00
#define REG_IMAGE_CAL_TEMPMONITOR_OFF                   0x01

/* bit definitions for LOWBAT register */
#define REG_LOWBAT                              	    0x08
#define REG_LOWBAT_ON                                   0x08
#define REG_LOWBAT_OFF                                  0x00
#define REG_LOWBAT_TRIM                         	    0x07
#define REG_LOWBAT_TRIM_1695                            0x00
#define REG_LOWBAT_TRIM_1764                            0x01
#define REG_LOWBAT_TRIM_1835                            0x02
#define REG_LOWBAT_TRIM_1905                            0x03
#define REG_LOWBAT_TRIM_1976                            0x04
#define REG_LOWBAT_TRIM_2045                            0x05
#define REG_LOWBAT_TRIM_2116                            0x06
#define REG_LOWBAT_TRIM_2185                            0x07

/* bit definitions for IRQFLAGS1 register */
#define REG_IRQ_FLAGS1_MODEREADY                        0x80
#define REG_IRQ_FLAGS1_RXREADY                          0x40
#define REG_IRQ_FLAGS1_TXREADY                          0x20
#define REG_IRQ_FLAGS1_PLLLOCK                          0x10
#define REG_IRQ_FLAGS1_RSSI                             0x08
#define REG_IRQ_FLAGS1_TIMEOUT                          0x04
#define REG_IRQ_FLAGS1_PREAMBLEDETECT                   0x02
#define REG_IRQ_FLAGS1_SYNCADDRESSMATCH                 0x01

/* bit definitions for IRQFLAGS2 register */
#define REG_IRQ_FLAGS2_FIFOFULL                         0x80
#define REG_IRQ_FLAGS2_FIFOEMPTY                        0x40
#define REG_IRQ_FLAGS2_FIFOLEVEL                        0x20
#define REG_IRQ_FLAGS2_FIFOOVERRUN                      0x10
#define REG_IRQ_FLAGS2_PACKETSENT                       0x08
#define REG_IRQ_FLAGS2_PAYLOADREADY                     0x04
#define REG_IRQ_FLAGS2_CRCOK                            0x02
#define REG_IRQ_FLAGS2_LOWBAT                           0x01

/* bit definitions for DIOMAPPING1 register */
#define REG_DIO_MAPPING1_DIO0                           0xC0
#define REG_DIO_MAPPING1_DIO0_00                        0x00
#define REG_DIO_MAPPING1_DIO0_01                        0x40
#define REG_DIO_MAPPING1_DIO0_10                        0x80
#define REG_DIO_MAPPING1_DIO0_11                        0xC0
#define REG_DIO_MAPPING1_DIO1                           0x30
#define REG_DIO_MAPPING1_DIO1_00                        0x00
#define REG_DIO_MAPPING1_DIO1_01                        0x10
#define REG_DIO_MAPPING1_DIO1_10                        0x20
#define REG_DIO_MAPPING1_DIO1_11                        0x30
#define REG_DIO_MAPPING1_DIO2                           0x0C
#define REG_DIO_MAPPING1_DIO2_00                        0x00
#define REG_DIO_MAPPING1_DIO2_01                        0x04
#define REG_DIO_MAPPING1_DIO2_10                        0x08
#define REG_DIO_MAPPING1_DIO2_11                        0x0C
#define REG_DIO_MAPPING1_DIO3                           0x03
#define REG_DIO_MAPPING1_DIO3_00                        0x00
#define REG_DIO_MAPPING1_DIO3_01                        0x01
#define REG_DIO_MAPPING1_DIO3_10                        0x02
#define REG_DIO_MAPPING1_DIO3_11              			0x03

/* bit definitions for DIOMAPPING2 register */
#define REG_DIO_MAPPING2_DIO4                          	0xC0
#define REG_DIO_MAPPING2_DIO4_00                       	0x00
#define REG_DIO_MAPPING2_DIO4_01                       	0x40
#define REG_DIO_MAPPING2_DIO4_10                       	0x80
#define REG_DIO_MAPPING2_DIO4_11                       	0xC0
#define REG_DIO_MAPPING2_DIO5                          	0x30
#define REG_DIO_MAPPING2_DIO5_00                       	0x00
#define REG_DIO_MAPPING2_DIO5_01                       	0x10
#define REG_DIO_MAPPING2_DIO5_10                       	0x20
#define REG_DIO_MAPPING2_DIO5_11                       	0x30
#define REG_DIO_MAPPING2_MAP                           	0x01
#define REG_DIO_MAPPING2_MAP_PREAMBLEDETECT            	0x01
#define REG_DIO_MAPPING2_MAP_RSSI                      	0x00

/* bit definitions for PLLHOP register */
#define REG_PLL_HOP_FASTHOP                            	0x80
#define REG_PLL_HOP_FASTHOP_ON                         	0x80
#define REG_PLL_HOP_FASTHOP_OFF                        	0x00

/* bit definitions for TCXO register */
#define REG_TCXO_TCXOINPUT                             	0x10
#define REG_TCXO_TCXOINPUT_ON                          	0x10
#define REG_TCXO_TCXOINPUT_OFF                         	0x00

/* bit definitions for PADAC register */
#define REG_PA_DAC_20DBM                               	0x07
#define REG_PA_DAC_20DBM_ON                            	0x07
#define REG_PA_DAC_20DBM_OFF                           	0x04

/* bit definitions for PLL register */
#define REG_PLL_BANDWIDTH                               0xC0
#define REG_PLL_BANDWIDTH_75                            0x00
#define REG_PLL_BANDWIDTH_150                           0x40
#define REG_PLL_BANDWIDTH_225                           0x80
#define REG_PLL_BANDWIDTH_300                         	0xC0

/* bit definitions for PLLLOWPN register */
#define REG_PLL_LOW_PN_BANDWIDTH                        0xC0
#define REG_PLL_LOW_PN_BANDWIDTH_75                     0x00
#define REG_PLL_LOW_PN_BANDWIDTH_150                    0x40
#define REG_PLL_LOW_PN_BANDWIDTH_225                    0x80
#define REG_PLL_LOW_PN_BANDWIDTH_300                    0xC0


/* LORA MODE REGISTERS */
/* register addresses */
#define REG_LR_OPMODE                               	0x01
#define REG_LR_FIFOADDRPTR                          	0x0D
#define REG_LR_FIFOTXBASEADDR                       	0x0E
#define REG_LR_FIFORXBASEADDR                       	0x0F
#define REG_LR_FIFORXCURRENTADDR                    	0x10
#define REG_LR_IRQFLAGSMASK                         	0x11
#define REG_LR_IRQFLAGS                             	0x12
#define REG_LR_RXNBBYTES                            	0x13
#define REG_LR_RXHEADERCNTVALUEMSB                  	0x14
#define REG_LR_RXHEADERCNTVALUELSB                  	0x15
#define REG_LR_RXPACKETCNTVALUEMSB                  	0x16
#define REG_LR_RXPACKETCNTVALUELSB                  	0x17
#define REG_LR_MODEMSTAT                            	0x18
#define REG_LR_PKTSNRVALUE                          	0x19
#define REG_LR_PKTRSSIVALUE                         	0x1A
#define REG_LR_RSSIVALUE                            	0x1B
#define REG_LR_HOPCHANNEL                           	0x1C
#define REG_LR_MODEMCONFIG1                         	0x1D
#define REG_LR_MODEMCONFIG2                         	0x1E
#define REG_LR_SYMBTIMEOUTLSB                       	0x1F
#define REG_LR_PREAMBLEMSB                          	0x20
#define REG_LR_PREAMBLELSB                          	0x21
#define REG_LR_PAYLOADLENGTH                        	0x22
#define REG_LR_PAYLOADMAXLENGTH                     	0x23
#define REG_LR_HOPPERIOD                            	0x24
#define REG_LR_FIFORXBYTEADDR                       	0x25
#define REG_LR_FEIMSB                               	0x28
#define REG_LR_FEIMID                               	0x29
#define REG_LR_FEILSB                               	0x2A
#define REG_LR_RSSIWIDEBAND                         	0x2C
#define REG_LR_DETECTOPTIMIZE                       	0x31
#define REG_LR_INVERTIQ                             	0x33
#define REG_LR_DETECTIONTHRESHOLD                   	0x37
#define REG_LR_SYNCWORD                             	0x39
#define REG_LR_INVERTIQ2                            	0x3B

/* bit definitions for OPMODE register */
#define REG_LR_OPMODE_LONGRANGEMODE                     0x80
#define REG_LR_OPMODE_LONGRANGEMODE_OFF                 0x00
#define REG_LR_OPMODE_LONGRANGEMODE_ON                  0x80
#define REG_LR_OPMODE_ACCESSSHAREDREG                   0x40
#define REG_LR_OPMODE_ACCESSSHAREDREG_ENABLE            0x40
#define REG_LR_OPMODE_ACCESSSHAREDREG_DISABLE           0x00
#define REG_LR_OPMODE_STATE                           	0x07
#define REG_LR_OPMODE_STATE_SLEEP                       0x00
#define REG_LR_OPMODE_STATE_STANDBY                     0x01
#define REG_LR_OPMODE_STATE_SYNTHESIZER_TX              0x02
#define REG_LR_OPMODE_STATE_TRANSMITTER                 0x03
#define REG_LR_OPMODE_STATE_SYNTHESIZER_RX              0x04
#define REG_LR_OPMODE_STATE_RECEIVER                    0x05
#define REG_LR_OPMODE_STATE_RECEIVER_SINGLE             0x06
#define REG_LR_OPMODE_STATE_CAD                         0x07

/* bit definitions for IRQFLAGMASK register */
#define REG_LR_IRQFLAGSMASK_RXTIMEOUT                   0x80
#define REG_LR_IRQFLAGSMASK_RXDONE                      0x40
#define REG_LR_IRQFLAGSMASK_PAYLOADCRCERROR             0x20
#define REG_LR_IRQFLAGSMASK_VALIDHEADER                 0x10
#define REG_LR_IRQFLAGSMASK_TXDONE                      0x08
#define REG_LR_IRQFLAGSMASK_CADDONE                     0x04
#define REG_LR_IRQFLAGSMASK_FHSSCHANGEDCHANNEL          0x02
#define REG_LR_IRQFLAGSMASK_CADDETECTED                 0x01

/* bit definitions for IRQFLAG register */
#define REG_LR_IRQFLAGS_RXTIMEOUT                       0x80
#define REG_LR_IRQFLAGS_RXDONE                          0x40
#define REG_LR_IRQFLAGS_PAYLOADCRCERROR                 0x20
#define REG_LR_IRQFLAGS_VALIDHEADER                     0x10
#define REG_LR_IRQFLAGS_TXDONE                          0x08
#define REG_LR_IRQFLAGS_CADDONE                         0x04
#define REG_LR_IRQFLAGS_FHSSCHANGEDCHANNEL              0x02
#define REG_LR_IRQFLAGS_CADDETECTED                     0x01

/* bit definitions for MODEMSTAT register */
#define REG_LR_MODEMSTAT_RX_CR                          0x1F
#define REG_LR_MODEMSTAT_MODEM_STATUS                   0xE0

/* bit definitions for HOPCHANNEL registers */
#define REG_LR_HOPCHANNEL_PLL_LOCK_TIMEOUT              0x80
#define REG_LR_HOPCHANNEL_PLL_LOCK_FAIL                 0x80
#define REG_LR_HOPCHANNEL_PLL_LOCK_SUCCEED              0x00
#define REG_LR_HOPCHANNEL_CRCONPAYLOAD                  0x40
#define REG_LR_HOPCHANNEL_CRCONPAYLOAD_ON               0x40
#define REG_LR_HOPCHANNEL_CRCONPAYLOAD_OFF              0x00
#define REG_LR_HOPCHANNEL_CHANNEL                       0x3F

/* bit definitions for MODEMCONFIG1 registers */
#define REG_LR_MODEMCONFIG1_BW                          0xC0
#define REG_LR_MODEMCONFIG1_BW_125_KHZ                  0x00
#define REG_LR_MODEMCONFIG1_BW_250_KHZ                  0x40
#define REG_LR_MODEMCONFIG1_BW_500_KHZ                  0x80
#define REG_LR_MODEMCONFIG1_CODINGRATE                  0x38
#define REG_LR_MODEMCONFIG1_CODINGRATE_4_5              0x08
#define REG_LR_MODEMCONFIG1_CODINGRATE_4_6              0x10
#define REG_LR_MODEMCONFIG1_CODINGRATE_4_7              0x18
#define REG_LR_MODEMCONFIG1_CODINGRATE_4_8              0x20
#define REG_LR_MODEMCONFIG1_IMPLICITHEADER              0x04
#define REG_LR_MODEMCONFIG1_IMPLICITHEADER_ON           0x04
#define REG_LR_MODEMCONFIG1_IMPLICITHEADER_OFF          0x00
#define REG_LR_MODEMCONFIG1_RXPAYLOADCRC                0x02
#define REG_LR_MODEMCONFIG1_RXPAYLOADCRC_ON             0x02
#define REG_LR_MODEMCONFIG1_RXPAYLOADCRC_OFF            0x00
#define REG_LR_MODEMCONFIG1_LOWDATARATEOPTIMIZE         0x01
#define REG_LR_MODEMCONFIG1_LOWDATARATEOPTIMIZE_ON      0x01
#define REG_LR_MODEMCONFIG1_LOWDATARATEOPTIMIZE_OFF     0x00

/* bit definitions for MODEMCONFIG2 registers */
#define REG_LR_MODEMCONFIG2_SF                          0xF0
#define REG_LR_MODEMCONFIG2_SF_6                        0x60
#define REG_LR_MODEMCONFIG2_SF_7                        0x70
#define REG_LR_MODEMCONFIG2_SF_8                        0x80
#define REG_LR_MODEMCONFIG2_SF_9                        0x90
#define REG_LR_MODEMCONFIG2_SF_10                       0xA0
#define REG_LR_MODEMCONFIG2_SF_11                       0xB0
#define REG_LR_MODEMCONFIG2_SF_12                       0xC0
#define REG_LR_MODEMCONFIG2_TXCONTINUOUSMODE            0x08
#define REG_LR_MODEMCONFIG2_TXCONTINUOUSMODE_ON         0x08
#define REG_LR_MODEMCONFIG2_TXCONTINUOUSMODE_OFF        0x00
#define REG_LR_MODEMCONFIG2_AGCAUTO                     0x04
#define REG_LR_MODEMCONFIG2_AGCAUTO_ON                  0x04
#define REG_LR_MODEMCONFIG2_AGCAUTO_OFF                 0x00
#define REG_LR_MODEMCONFIG2_SYMBTIMEOUTMSB              0x03

/* bit definitions for DETECTIONOPTIMIZE registers */
#define REG_LR_DETECTIONOPTIMIZE                        0x07
#define REG_LR_DETECTIONOPTIMIZE_SF7_TO_SF12            0x03
#define REG_LR_DETECTIONOPTIMIZE_SF6                    0x05

/* bit definitions for INVERTIQ registers */
#define REG_LR_INVERTIQ_RX                              0x40
#define REG_LR_INVERTIQ_RX_OFF                          0x00
#define REG_LR_INVERTIQ_RX_ON                           0x40
#define REG_LR_INVERTIQ_TX                              0x01
#define REG_LR_INVERTIQ_TX_OFF                          0x01
#define REG_LR_INVERTIQ_TX_ON                           0x00

/* bit definitions for DETECTIONTHRESH registers */
#define REG_LR_DETECTIONTHRESH_SF7_TO_SF12              0x0A
#define REG_LR_DETECTIONTHRESH_SF6                      0x0C

/* bit definitions for INVERTIQ2 registers */
#define REG_LR_INVERTIQ2_ON                             0x19
#define REG_LR_INVERTIQ2_OFF                            0x1D


#endif /* DEV_SX1272_REGS_H_ */
