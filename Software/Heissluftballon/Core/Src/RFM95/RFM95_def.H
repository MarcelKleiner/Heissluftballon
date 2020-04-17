/*
 * RFM95_def.H
 *
 *  Created on: 15.04.2020
 *      Author: marce
 */

#ifndef SRC_RFM95_RFM95_DEF_H_
#define SRC_RFM95_RFM95_DEF_H_


//defines for LoRa Mode
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


// RegBitRate (bits/sec) example bit rates
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

// RegFdev - frequency deviation (Hz)
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

// RegFrf	- FR carrier frequency

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

// RegPaConfig
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


// RegPaRamp (only FSK modulation -> see datasheet for OOK modulation P88)

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

// RegOcp
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

//RegRxConfig (0x0d)
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

// RegRxBw (0x12)

#define RF_RXBW_MANT_16				0x00
#define RF_RXBW_MANT_20				0x08
#define RF_RXBW_MANT_24				0x10

#define RF_RXBW_EXP_50000
#define RF_RXBW_EXP_
#define RF_RXBW_EXP_






// RegModemConfig
#define RF_RMC_BW7800				0x00
#define RF_RMC_BW10400				0x10
#define RF_RMC_BW15600				0x20
#define RF_RMC_BW20800				0x30
#define RF_RMC_BW31250				0x40
#define RF_RMC_BW41700				0x50
#define RF_RMC_BW62500				0x60
#define RF_RMC_BW125000				0x70	//default
#define RF_RMC_BW250000				0x80
#define RF_RMC_BW500000				0x90

#define RF_RMC_CORRAT4_5			0x02	//default
#define RF_RMC_CORRAT4_6			0x04
#define RF_RMC_CORRAT4_7			0x08
#define RF_RMC_CORRAT4_8			0x0A

#define RF_RMC_HEADER_M_IMPL		0x00	//default
#define RF_RMC_HEADER_M_EXPL 		0x01

// RegModemConfig 2

#define RF_RMC2_SFR6				0x60
#define RF_RMC2_SFR7				0x70	//default
#define RF_RMC2_SFR8				0x80
#define RF_RMC2_SFR9				0x90
#define RF_RMC2_SFR10				0xA0
#define RF_RMC2_SFR11				0xB0
#define RF_RMC2_SFR12				0xC0

#define RF_RMC2_TX_CONTON			0x08
#define RF_RMC2_TX_CONTOFF			0x00	//default

#define RF_RMC2_RX_CRCON			0x04
#define RF_RMC2_RX_CRCOFF			0x00	//default

// RegModemConfig 3
#define RF_RMC2_MOB_NODEON 			0x08
#define RF_RMC2_MOB_NODEOFF 		0x00	//default

#define RF_RMC2_AGCAUTOON			0x04
#define RF_RMC2_AGCAUTOOFF			0x00	//default


#define RF_RMC2_
#define RF_RMC2_
#define RF_RMC2_
#define RF_RMC2_



#endif /* SRC_RFM95_RFM95_DEF_H_ */
