/*
 * RFM95_def.H
 *
 *  Created on: 15.04.2020
 *      Author: marce
 */

#ifndef SRC_RFM95_RFM95_DEF_H_
#define SRC_RFM95_RFM95_DEF_H_



//defines for FSK Mode
#define	REG_FIFO					0x00
#define	REG_OP_MOD					0x01
#define	REG_BITRATE_MSB				0x02
#define	REG_BITRATE_LSB				0x03
#define	REG_FDEV_MSB				0x04
#define	REG_FDEV_LSB				0x05
#define	REG_FRF_MSB					0x06
#define	REG_FRF_MID					0x07
#define	REG_FRF_LSB					0x08
#define	REG_PA_CONFIG				0x09
#define	REG_PA_RAMP					0x0A
#define	REG_OCP						0x0B
#define	REG_LNA						0x0C
#define REG_RX_CONFIG				0x0D
#define	REG_RSSI_CONFIG				0x0E
#define	REG_RSSI_COLLISION			0x0F
#define	REG_RSSI_THRESH				0x10
#define	REG_RSSI_VALUE				0x11
#define	REG_RX_BW					0x12
#define	REG_AFC_BW					0x13
#define	REG_OOK_PEAK				0x14
#define	REG_OOK_FIX					0x15
#define	REG_OOK_AVG					0x16
#define	REG_AFC_FEI					0x1A
#define	REG_AFC_MSB					0x1B
#define	REG_AFC_LSB					0x1C
#define	REG_FEI_MSB					0x1D
#define	REG_FEI_LSB					0x1E
#define	REG_PREAMBLE_DETECT			0x1F
#define	REG_RX_TIMEOUT_1			0x20
#define	REG_RX_TIMEOUT_2			0x21
#define	REG_RX_TIMEOUT_3			0x22
#define	REG_RX_DELAY				0x23
#define	REG_OSC						0x24
#define	REG_PREAMBLE_MSB			0x25
#define	REG_PREAMBLE_LSB			0x26
#define	REG_SYNC_CONFIG				0x27
#define	REG_SYNC_VALUE_1			0x28
#define	REG_SYNC_VALUE_2			0x29
#define	REG_SYNC_VALUE_3			0x2A
#define	REG_SYNC_VALUE_4			0x2B
#define	REG_SYNC_VALUE_5			0x2C
#define	REG_SYNC_VALUE_6			0x2D
#define	REG_SYNC_VALUE_7			0x2E
#define	REG_SYNC_VALUE_8			0x2F
#define	REG_PACKET_CONFIG_1			0x30
#define	REG_PACKET_CONFIG_2			0x31
#define	REG_PAYLOAD_LENGTH			0x32
#define	REG_NODE_ADRS				0x33
#define	REG_BROADCAST_ADRS			0x34
#define	REG_FIFO_THRESH				0x35
#define	REG_SEQ_CONFIG_1			0x36
#define	REG_SEQ_CONFIG_2			0x37
#define	REG_TIMER_RESOL				0x38
#define	REG_TIMER_1_COEF			0x39
#define	REG_TIMER_2_COEF			0x3A
#define	REG_IMAGE_CAL				0x3B
#define	REG_TEMP					0x3C
#define	REG_LOW_BAT					0x3D
#define	REG_IRQ_FLAGS_1				0x3E
#define	REG_IRQ_FLAGS_2				0x3F

#define	REG_DIO_MAPPING_1			0x40
#define	REG_DIO_MAPPING_2			0x41
#define	REG_VERSION					0x42
#define REG_PLL_HOP					0x44
#define	REG_TCXO					0x4B
#define	REG_PA_DAC					0x4D
#define	REG_FORMER_TEMP				0x5B
#define	REG_BITRATE_FRAC			0x5D
#define	REG_AGC_REF					0x61
#define	REG_AGC_THRESH_1LF			0x62
#define	REG_AGC_THRESH_2LF			0x63
#define	REG_AGC_THRESH_3LF			0x64






//RegOpMode (0x01)
#define RF_OPMODE_LORA					0x80
#define RF_OPMODE_FSK					0x00	//default

#define RF_OPMODE_MODULATION_FSK		0x00	//default
#define RF_OPMODE_MODULATION_OOK		0x40

#define RF_OPMODE_LFM_ON				0x00
#define RF_OPMODE_LFM_OFF				0x08	//default

#define RF_OPMODE_SLEEP					0x00
#define RF_OPMODE_STBY 					0x01	//default
#define RF_OPMODE_FSTX 					0x02
#define RF_OPMODE_TX 					0x03
#define RF_OPMODE_FSRX 					0x04
#define RF_OPMODE_RX					0x05


// RegBitRate (0x01/0x02) (bits/sec) example bit rates
#define RF_BITRATEMSB_1200            0x68
#define RF_BITRATELSB_1200            0x2B

#define RF_BITRATEMSB_2400            0x34
#define RF_BITRATELSB_2400            0x15

#define RF_BITRATEMSB_4800            0x1A  // Default
#define RF_BITRATELSB_4800            0x0B  // Default

#define RF_BITRATEMSB_9600            0x0D
#define RF_BITRATELSB_9600            0x05

#define RF_BITRATEMSB_19200           0x06
#define RF_BITRATELSB_19200           0x83

#define RF_BITRATEMSB_38400           0x03
#define RF_BITRATELSB_38400           0x41

#define RF_BITRATEMSB_38323           0x03
#define RF_BITRATELSB_38323           0x43

#define RF_BITRATEMSB_34482           0x03
#define RF_BITRATELSB_34482           0xA0

#define RF_BITRATEMSB_76800           0x01
#define RF_BITRATELSB_76800           0xA1

#define RF_BITRATEMSB_153600          0x00
#define RF_BITRATELSB_153600          0xD0

#define RF_BITRATEMSB_57600           0x02
#define RF_BITRATELSB_57600           0x2C

#define RF_BITRATEMSB_115200          0x01
#define RF_BITRATELSB_115200          0x16

#define RF_BITRATEMSB_12500           0x0A
#define RF_BITRATELSB_12500           0x00

#define RF_BITRATEMSB_25000           0x05
#define RF_BITRATELSB_25000           0x00

#define RF_BITRATEMSB_50000           0x02
#define RF_BITRATELSB_50000           0x80

#define RF_BITRATEMSB_100000          0x01
#define RF_BITRATELSB_100000          0x40

#define RF_BITRATEMSB_150000          0x00
#define RF_BITRATELSB_150000          0xD5

#define RF_BITRATEMSB_200000          0x00
#define RF_BITRATELSB_200000          0xA0

#define RF_BITRATEMSB_250000          0x00
#define RF_BITRATELSB_250000          0x80

#define RF_BITRATEMSB_300000          0x00
#define RF_BITRATELSB_300000          0x6B

#define RF_BITRATEMSB_32768           0x03
#define RF_BITRATELSB_32768           0xD1

// RegFdev (0x04/0x05) - frequency deviation (Hz)
#define RF_FDEVMSB_2000             0x00
#define RF_FDEVLSB_2000             0x21

#define RF_FDEVMSB_5000             0x00  // Default
#define RF_FDEVLSB_5000             0x52  // Default

#define RF_FDEVMSB_7500             0x00
#define RF_FDEVLSB_7500             0x7B

#define RF_FDEVMSB_10000            0x00
#define RF_FDEVLSB_10000            0xA4

#define RF_FDEVMSB_15000            0x00
#define RF_FDEVLSB_15000            0xF6

#define RF_FDEVMSB_20000            0x01
#define RF_FDEVLSB_20000            0x48

#define RF_FDEVMSB_25000            0x01
#define RF_FDEVLSB_25000            0x9A

#define RF_FDEVMSB_30000            0x01
#define RF_FDEVLSB_30000            0xEC

#define RF_FDEVMSB_35000            0x02
#define RF_FDEVLSB_35000            0x3D

#define RF_FDEVMSB_40000            0x02
#define RF_FDEVLSB_40000            0x8F

#define RF_FDEVMSB_45000            0x02
#define RF_FDEVLSB_45000            0xE1

#define RF_FDEVMSB_50000            0x03
#define RF_FDEVLSB_50000            0x33

#define RF_FDEVMSB_55000            0x03
#define RF_FDEVLSB_55000            0x85

#define RF_FDEVMSB_60000            0x03
#define RF_FDEVLSB_60000            0xD7

#define RF_FDEVMSB_65000            0x04
#define RF_FDEVLSB_65000            0x29

#define RF_FDEVMSB_70000            0x04
#define RF_FDEVLSB_70000            0x7B

#define RF_FDEVMSB_75000            0x04
#define RF_FDEVLSB_75000            0xCD

#define RF_FDEVMSB_80000            0x05
#define RF_FDEVLSB_80000            0x1F

#define RF_FDEVMSB_85000            0x05
#define RF_FDEVLSB_85000            0x71

#define RF_FDEVMSB_90000            0x05
#define RF_FDEVLSB_90000            0xC3

#define RF_FDEVMSB_95000            0x06
#define RF_FDEVLSB_95000            0x14

#define RF_FDEVMSB_100000           0x06
#define RF_FDEVLSB_100000           0x66

#define RF_FDEVMSB_110000           0x07
#define RF_FDEVLSB_110000           0x0A

#define RF_FDEVMSB_120000           0x07
#define RF_FDEVLSB_120000           0xAE

#define RF_FDEVMSB_130000           0x08
#define RF_FDEVLSB_130000           0x52

#define RF_FDEVMSB_140000           0x08
#define RF_FDEVLSB_140000           0xF6

#define RF_FDEVMSB_150000           0x09
#define RF_FDEVLSB_150000           0x9A

#define RF_FDEVMSB_160000           0x0A
#define RF_FDEVLSB_160000           0x3D

#define RF_FDEVMSB_170000           0x0A
#define RF_FDEVLSB_170000           0xE1

#define RF_FDEVMSB_180000           0x0B
#define RF_FDEVLSB_180000           0x85

#define RF_FDEVMSB_190000           0x0C
#define RF_FDEVLSB_190000           0x29

#define RF_FDEVMSB_200000           0x0C
#define RF_FDEVLSB_200000           0xCD

#define RF_FDEVMSB_210000           0x0D
#define RF_FDEVLSB_210000           0x71

#define RF_FDEVMSB_220000           0x0E
#define RF_FDEVLSB_220000           0x14

#define RF_FDEVMSB_230000           0x0E
#define RF_FDEVLSB_230000           0xB8

#define RF_FDEVMSB_240000           0x0F
#define RF_FDEVLSB_240000           0x5C

#define RF_FDEVMSB_250000           0x10
#define RF_FDEVLSB_250000           0x00

#define RF_FDEVMSB_260000           0x10
#define RF_FDEVLSB_260000           0xA4

#define RF_FDEVMSB_270000           0x11
#define RF_FDEVLSB_270000           0x48

#define RF_FDEVMSB_280000           0x11
#define RF_FDEVLSB_280000           0xEC

#define RF_FDEVMSB_290000           0x12
#define RF_FDEVLSB_290000           0x8F

#define RF_FDEVMSB_300000           0x13
#define RF_FDEVLSB_300000           0x33

// RegFrf (0x06/0x07/0x08)	- FR carrier frequency

#define RF_FRFMSB_315000			0x4E
#define RF_FRFMID_315000			0xC0
#define RF_FRFLSB_315000			0x0D

#define RF_FRFMSB_434000			0x6C	//default
#define RF_FRFMID_434000			0x80	//default
#define RF_FRFLSB_434000			0x00	//default

#define RF_FRFMSB_868000			0xD9
#define RF_FRFMID_868000			0x00
#define RF_FRFLSB_868000			0x24

#define RF_FRFMSB_915000			0xE4
#define RF_FRFMID_915000			0xC0
#define RF_FRFLSB_915000			0x26

// RegPaConfig (0x09)
#define RF_PA_20DBM					0xAF
#define RF_PA_19DBM					0xAE
#define RF_PA_18DBM					0xAD
#define RF_PA_17DBM					0xAC
#define RF_PA_16DBM					0xAB
#define RF_PA_15DBM					0x7F
#define RF_PA_14DBM					0x7E
#define RF_PA_13DBM					0x7D
#define RF_PA_12DBM					0x7C
#define RF_PA_11p4DBM				0x4F	//default
#define RF_PA_11DBM					0x7B
#define RF_PA_10DBM					0x7A
#define RF_PA_09DBM					0x79
#define RF_PA_08DBM					0x78
#define RF_PA_07DBM					0x77
#define RF_PA_06DBM					0x76
#define RF_PA_05DBM					0x75
#define RF_PA_04DBM					0x74
#define RF_PA_03DBM					0x73
#define RF_PA_02DBM					0x72
#define RF_PA_01DBM					0x71
#define RF_PA_00DBM					0x70


// RegPaRamp (0x0A) (only FSK modulation -> see datasheet for OOK modulation P88)

#define REG_MOD_SHP_NO				0x00	//default
#define REG_MOD_SHP_BT10			0x20
#define REG_MOD_SHP_BT05			0x40
#define REG_MOD_SHP_BT03			0x60

#define	RF_PA_R3400					0x00
#define	RF_PA_R2000					0x01
#define	RF_PA_R1000					0x02
#define RF_PA_R500					0x03
#define RF_PA_R250					0x04
#define RF_PA_R125					0x05
#define	RF_PA_R100					0x06
#define RF_PA_R62					0x07
#define RF_PA_R50					0x08
#define RF_PA_R40					0x09	//default
#define RF_PA_R31					0x0A
#define RF_PA_R25					0x0B
#define	RF_PA_R20					0x0C
#define RF_PA_R15					0x0D
#define RF_PA_R12					0x0E
#define RF_PA_R10					0x0F

// RegOcp (0x0B)
#define RF_OCP_OCPON				0x20	//default
#define RF_OCP_OCPOFF				0x00

#define RF_OCP_TRIM100MA			0x0B
#define RF_OCP_TRIM110MA 			0x0D
#define RF_OCP_TRIM120MA			0x0F
#define RF_OCP_TRIM130MA			0x10
#define RF_OCP_TRIM140MA			0x11
#define RF_OCP_TRIM150MA			0x12
#define RF_OCP_TRIM160MA			0x13
#define RF_OCP_TRIM170MA			0x14
#define RF_OCP_TRIM180MA			0x15
#define RF_OCP_TRIM190MA			0x16
#define RF_OCP_TRIM200MA			0x17
#define RF_OCP_TRIM210MA			0x18
#define RF_OCP_TRIM220MA			0x19
#define RF_OCP_TRIM230MA			0x1A
#define RF_OCP_TRIM240MA			0x1B

// RegLNA (0x0C)
#define RF_LNA_G1					0x20	//derault
#define RF_LNA_G2					0x40
#define RF_LNA_G3					0x60
#define RF_LNA_G4					0x80
#define RF_LNA_G5					0xA0
#define RF_LNA_G6					0xC0

#define RF_LNA_BOOST_ON				0x03
#define RF_LNA_BOOST_OFF 			0x00	//default

//RegRxConfig (0x0D)
#define RF_CONF_RESTART_ON_COL_ON	0x80
#define RF_CONF_RESTART_ON_COL_OFF	0x00

#define RF_CONF_RESTART_PLLLOCK		0x40
#define RF_CONF_RESTART_NO_PLLLOCK	0x40

#define RF_CONF_AFC_AUTO_ON			0x08
#define RF_CONF_AFC_AUTO_OFF		0x00

#define RF_CONF_AGC_AUTO_ON			0x04
#define RF_CONF_AGC_AUTO_OFF		0x00

#define RF_CONFIG_RX_NONE			0x00
#define RF_CONFIG_RX_RSSI_INT		0x01
#define RF_CONFIG_RX_PREAMB_DETECT	0x06
#define RF_CONFIG_RX_RSSI_P_PREAMB	0x07

// RegRssiConfig (0x0E)
#define RF_RSSI_OFFSET				0x00	//default (see datasheet for mor information)

#define RF_RSSI_SMOOTH_2			0x00
#define RF_RSSI_SMOOTH_4			0x01
#define RF_RSSI_SMOOTH_8			0x02
#define RF_RSSI_SMOOTH_46			0x03
#define RF_RSSI_SMOOTH_32			0x04
#define RF_RSSI_SMOOTH_64			0x05
#define RF_RSSI_SMOOTH_128			0x06
#define RF_RSSI_SMOOTH_256			0x07

// RegRssiCollision (0x0F)
// -> (0x00 - 0xFF) Sets the threshold used to consider that an interferer is detected, witnessing a packet collision. 1dB/LSB (only RSSI increase) Default: 10dB

// RegRssiThresh (0x10)
// -> (0-0xFF) RSSI trigger level for the Rssi interrupt: - RssiThreshold / 2 [dBm]

// RegRssiValue
// -> (0x00 - 0xFF) Absolute value of the RSSI in dBm, 0.5dB steps. RSSI = - RssiValue/2 [dBm]


// RegRxBw (0x12)

#define RF_RXBW_MANT_16				0x00
#define RF_RXBW_MANT_20				0x08
#define RF_RXBW_MANT_24				0x10

#define RF_RXBW_EXP_0				0x00
#define RF_RXBW_EXP_1				0x01
#define RF_RXBW_EXP_2				0x02
#define RF_RXBW_EXP_3				0x03
#define RF_RXBW_EXP_4				0x04
#define RF_RXBW_EXP_5				0x05
#define RF_RXBW_EXP_6				0x06
#define RF_RXBW_EXP_7				0x07

// 0x13 - 0x1E  OOK/AFC settings-> see Datasheet for mor Information

// RegPreambleDetect (0x1F)
#define RF_PREAMB_DETECTOR_ON		0x80
#define RF_PREAMB_DETECTOR_OFF		0x00

#define RF_PREAMB_DETECTOR_SIZE_1b	0x00
#define RF_PREAMB_DETECTOR_SIZE_2b	0x20	//default
#define RF_PREAMB_DETECTOR_SIZE_3b	0x40

#define RF_PREAMB_DETECTOR_TOL_0	0x00
#define RF_PREAMB_DETECTOR_TOL_1	0x01
#define RF_PREAMB_DETECTOR_TOL_2	0x02
#define RF_PREAMB_DETECTOR_TOL_3	0x03
#define RF_PREAMB_DETECTOR_TOL_4	0x04
#define RF_PREAMB_DETECTOR_TOL_5	0x05
#define RF_PREAMB_DETECTOR_TOL_6	0x06
#define RF_PREAMB_DETECTOR_TOL_7	0x07
#define RF_PREAMB_DETECTOR_TOL_8	0x08
#define RF_PREAMB_DETECTOR_TOL_9	0x09
#define RF_PREAMB_DETECTOR_TOL_10	0x0A	//default

// Reg Timeout 1 - 3 / RxDelay (0x20 - 0x23) -> Timeout definition see Datasheet P92 for more information (default 0x00 - timeout disable)

// RegOsc (0x24)
#define RF_OSC_CAL_START_TRIGGER	0x08

#define RF_OSC_CLK_OUT_DIF0			0x00
#define RF_OSC_CLK_OUT_DIF2			0x01
#define RF_OSC_CLK_OUT_DIF4			0x02
#define RF_OSC_CLK_OUT_DIF8			0x03
#define RF_OSC_CLK_OUT_DIF16		0x04
#define RF_OSC_CLK_OUT_DIF32		0x05
#define RF_OSC_CLK_RC				0x06
#define RF_OSC_CLK_OFF				0x07	//default

// RegPreamble Msb/Lsb (0x025/0x026)
// - (0x00-0xFF) -> Size of the preamble to be sent (from TxStartCondition fulfilled)

// RegSyncConfig (0x27)
#define RF_SYNC_AUTO_RESTART_OFF		0x00
#define RF_SYNC_AUTO_RESTART_ON_NOPLL	0x40
#define RF_SYNC_AUTO_RESTART_ON_PLL		0x80	//default

#define RF_SYNC_PREAMBLE_0XAA		0x00	//default
#define RF_SYNC_PREAMBLE_0X55		0x20

#define RF_SYNC_SYNC_ON				0x10	//default
#define RF_SYNC_SYNC_OFF			0x00

#define RF_SYNC_FIFOFILL_INT		0x00	//default
#define RF_SYNC_FIFOFILL_SET		0x08

#define RF_SYNC_SYNC_SIZE_0			0x00
#define RF_SYNC_SYNC_SIZE_1			0x01
#define RF_SYNC_SYNC_SIZE_2			0x02
#define RF_SYNC_SYNC_SIZE_3			0x03	//default
#define RF_SYNC_SYNC_SIZE_4			0x04
#define RF_SYNC_SYNC_SIZE_5			0x05
#define RF_SYNC_SYNC_SIZE_6			0x06
#define RF_SYNC_SYNC_SIZE_7			0x07

// RegSyncValue (0x28 - 0x2F)
// -0x28 (0x00 - 0xFF) -> 1. byte of Sync word (MSB byte) - default 0x01
// -0x29 (0x00 - 0xFF) -> 2. byte of Sync word (MSB byte) - default 0x01
// -0x2A (0x00 - 0xFF) -> 3. byte of Sync word (MSB byte) - default 0x01
// -0x2B (0x00 - 0xFF) -> 4. byte of Sync word (MSB byte) - default 0x01
// -0x2C (0x00 - 0xFF) -> 5. byte of Sync word (MSB byte) - default 0x01
// -0x2D (0x00 - 0xFF) -> 6. byte of Sync word (MSB byte) - default 0x01
// -0x2E (0x00 - 0xFF) -> 7. byte of Sync word (MSB byte) - default 0x01
// -0x2F (0x00 - 0xFF) -> 8. byte of Sync word (MSB byte) - default 0x01

// RegPacketConfig1 (0x30)
#define RF_PACKET1_FORMAT_FIX				0x00
#define RF_PACKET1_FORMAT_VAR				0x80	//default

#define RF_PACKET1_DC_OFF					0x00	//default
#define RF_PACKET1_DC_MANCHESTER			0x20
#define RF_PACKET1_DC_WHITENING				0x40

#define RF_PACKET1_CRC_ON					0x10	//default
#define RF_PACKET1_CRC_OFF					0x00

#define RF_PACKET1_CRC_AUTOCLEAR_ON			0x00	//default
#define RF_PACKET1_CRC_AUTOCLEAR_OFF		0x04

#define RF_PACKET1_ADDR_FILT_OFF			0x00	//default
#define RF_PACKET1_ADDR_FILT_NODE			0x02
#define RF_PACKET1_ADDR_FILT_NODE_BROAD		0x04

#define RF_PACKET1_CRC_CCITT				0x00	//default
#define RF_PACKET1_CRC_IBM					0x01

// RegPacketConfig2 (0x31)
#define RF_PACKET2_DATA_MODE_CONT			0x00
#define RF_PACKET2_DATA_MODE_PACKET			0x40

#define RF_PACKET2_IHOME_ON					0x20
#define RF_PACKET2_IHOME_OFF				0x00

#define RF_PACKET2_BACON_ON					0x04
#define RF_PACKET2_BACON_OFF				0x00

// RegPayloadLength (0x32)
#define RF_PAYLOAD_LEN_10				0x0A
#define RF_PAYLOAD_LEN_20				0x14
#define RF_PAYLOAD_LEN_30				0x1E
#define RF_PAYLOAD_LEN_40				0x28
#define RF_PAYLOAD_LEN_50				0x32
#define RF_PAYLOAD_LEN_60				0x3C
#define RF_PAYLOAD_LEN_70				0x46
#define RF_PAYLOAD_LEN_80				0x50
#define RF_PAYLOAD_LEN_90				0x5A
#define RF_PAYLOAD_LEN_100				0x64
#define RF_PAYLOAD_LEN_110				0x6E
#define RF_PAYLOAD_LEN_120				0x78
#define RF_PAYLOAD_LEN_130				0x82
#define RF_PAYLOAD_LEN_140				0x8C
#define RF_PAYLOAD_LEN_150				0x96
#define RF_PAYLOAD_LEN_160				0xA0
#define RF_PAYLOAD_LEN_170				0xAA
#define RF_PAYLOAD_LEN_180				0xB4
#define RF_PAYLOAD_LEN_190				0xBE
#define RF_PAYLOAD_LEN_200				0xC8
#define RF_PAYLOAD_LEN_210				0xD2
#define RF_PAYLOAD_LEN_220				0xDC
#define RF_PAYLOAD_LEN_230				0xE6
#define RF_PAYLOAD_LEN_240				0xF0
#define RF_PAYLOAD_LEN_250				0xFA
//for larger packet length use RegPacketConfig2 bit 2-0 -> see Datasheet P94

// RegNodeAdrs (0x33)
// - (0x00-0xFF) Node address used in addressfiltering

// RegBroadcastAdrs (0x34)
// - (0x00-0xFF) Broadcast address used in addressfiltering

// RegFifoThresh
#define RF_FIFOTHRESH_TXSTART_FIFOLEVEL		0x00
#define RF_FIFOTHRESH_TXSTART_FIFOEMPTY		0x80	//default

#define RF_FIFOTHRESH_FIFO_INT_0			0x00
#define RF_FIFOTHRESH_FIFO_INT_1			0x01
#define RF_FIFOTHRESH_FIFO_INT_2			0x02
#define RF_FIFOTHRESH_FIFO_INT_3			0x03
#define RF_FIFOTHRESH_FIFO_INT_4			0x04
#define RF_FIFOTHRESH_FIFO_INT_5			0x05
#define RF_FIFOTHRESH_FIFO_INT_6			0x06
#define RF_FIFOTHRESH_FIFO_INT_7			0x07
#define RF_FIFOTHRESH_FIFO_INT_8			0x08
#define RF_FIFOTHRESH_FIFO_INT_15			0x0F
//.
//.
//.

// RegSeqConfig1 (0x36)
#define RF_SEQ1_SEQUSTART_TRIG			0x80

#define RF_SEQ1_SEQUSTOP_TRIG			0x40

#define RF_SEQ1_MODE_SLEEP				0x20
#define RF_SEQ1_MODE_STBY				0x00	//default

#define RF_SEQ1_FROM_START_00			0x00	//default
#define RF_SEQ1_FROM_START_01			0x08
#define RF_SEQ1_FROM_START_10			0x10
#define RF_SEQ1_FROM_START_11			0x18

#define RF_SEQ1_LPS_OFF					0x00	//default
#define RF_SEQ1_LPS_IDLE				0x04

#define RF_SEQ1_FROM_IDLE_TO_RX			0x00	//default
#define RF_SEQ1_FROM_IDLE_TO_TX			0x02


#define RF_SEQ1_FROM_TX_TO_LPS			0x00	//default
#define RF_SEQ1_FROM_TX_TO_RX			0x01


// RegSeqConfig1 (0x37)
#define RF_SEQ1_FROM_RX_001				0x20	// to PacketReceived state on a PayloadReady interrupt
#define RF_SEQ1_FROM_RX_010				0x40	// to LowPowerSelection on a PayloadReady interrupt
#define RF_SEQ1_FROM_RX_011				0x60	// to PacketReceived state on a CrcOk interrupt
#define RF_SEQ1_FROM_RX_100				0x80	// to SequencerOff state on a Rssi interrupt
#define RF_SEQ1_FROM_RX_101				0xA0	// to SequencerOff state on a SyncAddress interrupt
#define RF_SEQ1_FROM_RX_110				0xC0	// to SequencerOff state on a PreambleDetect interrupt

#define RF_SEQ1_FROM_RXTIMOU_00			0x00	// to Receive State, via ReceiveRestart (default)
#define RF_SEQ1_FROM_RXTIMOU_01			0x08	// to Transmit state
#define RF_SEQ1_FROM_RXTIMOU_10			0x10	// to LowPowerSelection
#define RF_SEQ1_FROM_RXTIMOU_11			0x18	// to SequencerOff state

#define RF_SEQ1_FROM_PACK_RX_000		0x00	// to SequencerOff state
#define RF_SEQ1_FROM_PACK_RX_001		0x01	// to Transmit state on a FifoEmpty interrupt
#define RF_SEQ1_FROM_PACK_RX_010		0x02	// to LowPowerSelection
#define RF_SEQ1_FROM_PACK_RX_011		0x03	// to Receive via FS mode, if frequency was changed
#define RF_SEQ1_FROM_PACK_RX_100		0x04	// to Receive state (no frequency change)

// RegTimer (0x38-0x3A)
// -> RegTimerResol - default 0x00 (Timer1+2 off) -> see Datasheet P96 for more information
// -> RegTimer1Coef - default 0xF5	-> unused if Timer1 disabled
// -> RegTimer2Coef - default 0x20	-> unused if Timer2 disabled

// RegImageCal (0x3B)
#define RF_IMG_AUTO_CAL_ON				0x80
#define RF_IMG_AUTO_CAL_OFF				0x00

#define RF_IMG_START_TRIG				0x40

#define RF_IMG_TEMP_CHANG_LOW			0x00	//default
#define RF_IMG_TEMP_CHANG_HIGH			0x08

#define RF_IMG_TEMP_THRES_5				0x00
#define RF_IMG_TEMP_THRES_10			0x02	//default
#define RF_IMG_TEMP_THRES_15			0x04
#define RF_IMG_TEMP_THRES_20			0x06

#define RF_IMG_TEMP_MONITOR_ON			0x01
#define RF_IMG_TEMP_MONITOR_OFF			0x00	//default

// RegTemp (0x3C) read only

// RegLowBat
#define RF_BAT_LOW_BAT_ON
#define RF_BAT_LOW_BAT_OFF

#define RF_BAT_LOW_BAT_TRIM_1695		0x00
#define RF_BAT_LOW_BAT_TRIM_1764		0x01
#define RF_BAT_LOW_BAT_TRIM_1835		0x02	//default
#define RF_BAT_LOW_BAT_TRIM_1905		0x03
#define RF_BAT_LOW_BAT_TRIM_1976		0x04
#define RF_BAT_LOW_BAT_TRIM_2045		0x05
#define RF_BAT_LOW_BAT_TRIM_2116		0x06
#define RF_BAT_LOW_BAT_TRIM_2185		0x07

// RegIrqFlags1+2 (0x3E/0x3F) -> most read only -> for mor information see Datashee P98

// REG_DIO_MAPPING_1 (0x40) DIO 0-3	-> datasheet P
#define RF_DIO_0_TX_PACKETSENT		0x00
#define RF_DIO_0_RX_PAYLOADRDY		0x00
#define RF_DIO_0_RX_CRCOK			0x40
#define RF_DIO_0_ALL_TEMP_LOWBAT	0xC0

#define RF_DIO_1_ALL_FIFOLEVEL		0x00
#define RF_DIO_1_ALL_FIFOEMPTY		0x10
#define RF_DIO_1_ALL_FIFOFULL		0x20

#define RF_DIO_2_ALL_FIFOFULL		0x00
#define RF_DIO_2_RX_RX_RDY			0x04
#define RF_DIO_2_RX_TIMEOUT			0x08
#define RF_DIO_2_RX_SYNCADDR		0x0C
#define RF_DIO_2_TX_FIFOFULL		0x0C

#define RF_DIO_3_TX_TX_RDY			0x01
#define RF_DIO_3_ALL_FIFOEMPTY		0x03

// REG_DIO_MAPPING_2 (0x41) DIO 4-5
#define RF_DIO_4_ALL_TEMP_LOWBAT	0x00
#define RF_DIO_4_ALL_PLLLOCK		0x40
#define RF_DIO_4_RX_TIMEOUT			0x80
#define RF_DIO_4_RX_PREAMBLEDETECT	0xC0

#define RF_DIO_5_ALL_CLKOUT			0x00
#define RF_DIO_5_TX_RX_PLLLOCK		0x10
#define RF_DIO_5_TX_RX_DATA			0x20
#define RF_DIO_5_ALL_MODERDY		0x30

#define RF_DIO_PREAMBLE_RSSI		0x01
#define RF_DIO_PREAMBLE_INT			0x00


// RegVersion (0x42) -> read only

// RegPllHop (0x44)
#define RF_PLLHOP_FAST_HOP_ON_0		0x00	// Frf is validated when FSTx or FSRx is requested (default)
#define RF_PLLHOP_FAST_HOP_ON_1		0x80	// Frf is validated triggered when RegFrfLsb is written

 // RegTcxo (0x4B)
#define RF_TCXO_INPUT_ON_0			0x00	// Crystal Oscillator with external Crystal (default)
#define RF_TCXO_INPUT_ON_1			0x10	// External clipped sine TCXO AC-connected to XTA pin

// RegPaDac (0x4D)
#define RF_PA_DAC_ON				0x07	// +20dBm on PA_BOOST when OutputPower=1111
#define RF_PA_DAC_OFF				0x04	// Default value (default)

// RegBitrateFrac (0x5D)	-> for mor information see Datasheet P99
#define RF_BITRATE_FRAC				0x00	// Fractional part of the bit rate divider (Only valid for FSK)

// RegAgc (0x61-0x64) -> for more information see Datashee P100

#endif /* SRC_RFM95_RFM95_DEF_H_ */
