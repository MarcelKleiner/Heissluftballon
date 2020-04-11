/*
 * SHT21.cpp
 *
 *  Created on: Apr 10, 2020
 *      Author: marce
 */

#include "SHT21.h"

SHT21::SHT21() {
	// TODO Auto-generated constructor stub

}

void SHT21::initSHT21(){

}

HAL_StatusTypeDef SHT21::writeByte(uint8_t addr){

	uint8_t txBuffer[1];
	txBuffer[0] = addr;

	return(HAL_I2C_Master_Transmit(&hi2c1,SHT21_SLAVE_ADDR,(uint8_t*)txBuffer,1,I2C_Timeout));

}

uint32_t SHT21::readSHT21Temp(){
	uint8_t buffer[2];
	writeByte(SHT21_TEMP_REG);
	/*Warten bis Messung beendet*/
	while(HAL_I2C_Master_Receive(&hi2c1,SHT21_SLAVE_ADDR,buffer,2,I2C_Timeout) != HAL_OK);
	return((buffer[0]<<8)+buffer[1]);
}

uint32_t SHT21::readSHT21Humidity(){
	uint8_t buffer[2];
	writeByte(SHT21_HUMIDITY_REG);
	while(HAL_I2C_Master_Receive(&hi2c1,SHT21_SLAVE_ADDR,buffer,2,I2C_Timeout) != HAL_OK);
	return((buffer[0]<<8)+buffer[1]);
}
