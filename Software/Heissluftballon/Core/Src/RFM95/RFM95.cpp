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

void RFM95::initRFM(void){
	const uint8_t CONFIG[][2] ={
		/*0x01*/	{REG_OP_MOD, RF_OPMODE_FSK | RF_OPMODE_MODULATION_FSK | RF_OPMODE_LFM_OFF | RF_OPMODE_STBY },
		/*0x02*/	{REG_BITRATE_MSB, RF_BITRATEMSB_4800 },
		/*0x03*/	{REG_BITRATE_LSB, RF_BITRATELSB_4800 },
		/*0x04*/	{REG_FDEV_MSB, RF_FDEVMSB_50000},
		/*0x05*/	{REG_FDEV_LSB, RF_FDEVLSB_50000},

		/*0x06*/	{REG_FRF_MSB,RF_FRFMSB_868000},
		/*0x07*/	{REG_FRF_MID,RF_FRFMID_8680000},
		/*0x08*/	{REG_FRF_LSB,RF_FRFLSB_868000},

		/*0x09*/	{REG_PA_CONFIG,RF_PA_05DBM },
		/*0x0A*/	{REG_RX_BW, RF_RXBW_MANT_16 | RF_RXBW_EXP_2},
		/*0x0B*/



		{255,0}
	};
}

void RFM95::writeReg(uint8_t addr, uint8_t data){

}

uint8_t RFM95::readReg(uint8_t addr){

}

void RFM95::writeFIFO(void){

}

void RFM95::readFIFO(void){

}

void RFM95::setTransmitDirection(RFM_DIR rfmDir){

}

void RFM95::setMode(MODE mode){

}


