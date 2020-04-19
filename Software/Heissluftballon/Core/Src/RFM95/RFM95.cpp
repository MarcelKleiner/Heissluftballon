/*
 * RFM95.cpp
 *
 *  Created on: 15.04.2020
 *      Author: marce
 */

#include "RFM95.h"

RFM95::RFM95() {
	// TODO Auto-generated constructor stub
}


//void RFM95::initRFM(void){
//	const uint8_t CONFIG[][2] ={
//		/*0x01*/	{REG_OP_MOD, RF_OPMODE_FSK | RF_OPMODE_MODULATION_FSK | RF_OPMODE_LFM_OFF | RF_OPMODE_STBY },
//		/*0x02*/	{REG_BITRATE_MSB, RF_BITRATEMSB_4800 },
//		/*0x03*/	{REG_BITRATE_LSB, RF_BITRATELSB_4800 },
//		/*0x04*/	{REG_FDEV_MSB, RF_FDEVMSB_50000},
//		/*0x05*/	{REG_FDEV_LSB, RF_FDEVLSB_50000},
//
//		/*0x06*/	{REG_FRF_MSB,RF_FRFMSB_868000},
//		/*0x07*/	{REG_FRF_MID,RF_FRFMID_868000},
//		/*0x08*/	{REG_FRF_LSB,RF_FRFLSB_868000},
//
//		/*0x09*/	{REG_PA_CONFIG,RF_PA_05DBM },
//		/*0x0A*/	{REG_RX_BW, RF_RXBW_MANT_16 | RF_RXBW_EXP_2},
//
//		/*0x10*/	{REG_RSSI_THRESH, 220},	// must be set to dBm = (-Sensitivity / 2), default is 0xE4 = 228 so -114dBm
//
//		/*0x25*/	{REG_PREAMBLE_MSB, 0x00},	//preamble size MSB
//		/*0x26*/	{REG_PREAMBLE_LSB, 0x03},	//Preamble size LSB
//
//		/*0x3E*/	{REG_IRQ_FLAGS_1, 0x0A},	//clear all interrupts
//		/*0x3F*/	{REG_IRQ_FLAGS_2, 0x11},	//clear all interrupts
//
//		/*0x40*/	{REG_DIO_MAPPING_1, RF_DIO_0_TX_PAYLOADRDY | RF_DIO_1_ALL_FIFOEMPTY | RF_DIO_2_RX_RXRDY},
//		/*0x41*/	{REG_DIO_MAPPING_2, RF_DIO_4_RX_PREAMBLEDETECT},
//
//		/*0x27*/  	{REG_SYNC_CONFIG, RF_SYNC_AUTO_RESTART_ON_PLL | RF_SYNC_PREAMBLE_0XAA | RF_SYNC_FIFOFILL_INT | RF_SYNC_SYNC_SIZE_3},
//		/*0x28*/	{REG_SYNC_VALUE_1,0x2D},
//		/*0x29*/  	{REG_SYNC_VALUE_2,0x2D},
//		/*0x2A*/  	{REG_SYNC_VALUE_3,0x2D},
//
//		/*0x30*/  	{REG_PACKET_CONFIG_1, RF_PACKET1_FORMAT_VAR | RF_PACKET1_DC_OFF | RF_PACKET1_CRC_ON | RF_PACKET1_CRC_AUTOCLEAR_ON | RF_PACKET1_ADDR_FILT_OFF | RF_PACKET1_CRC_CCITT},
//		/*0x31*/  	{REG_PACKET_CONFIG_2, RF_PACKET2_DATA_MODE_PACKET | RF_PACKET2_IHOME_OFF | RF_PACKET2_BACON_OFF},
//
//		/*0x32*/	{REG_PAYLOAD_LENGTH, TRANSMIT_DATA_LENGTH},
//
//
//		/*0x36*/	{REG_FIFO_THRESH, RF_FIFOTHRESH_TXSTART_FIFOEMPTY | 0x1F},
//
//
//		{255,0}
//	};
//}
//
//void RFM95::writeReg(uint8_t addr, uint8_t data){
//
//}
//
//uint8_t RFM95::readReg(uint8_t addr){
//	return 0;
//}
//
//void RFM95::writeFIFO(void){
//
//}
//
//void RFM95::readFIFO(void){
//
//}
//
//void RFM95::setTransmitDirection(RFM_DIR rfmDir){
//
//}
//
//void RFM95::setMode(MODE mode){
//
//}
//

