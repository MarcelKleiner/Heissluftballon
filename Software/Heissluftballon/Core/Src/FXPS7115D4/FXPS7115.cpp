/*
 * FXPS7115.cpp
 *
 *  Created on: Apr 10, 2020
 *      Author: marce
 */

#include "FXPS7115.h"



FXPS7115::FXPS7115(Model *model) {
	// TODO Auto-generated constructor stub
	this->model = model;
}



void FXPS7115::fxpInit(){

}

HAL_StatusTypeDef FXPS7115::writeByte(uint8_t addr){
	uint8_t txBuffer[1];
	txBuffer[0] = addr;
	return(HAL_I2C_Master_Transmit(&hi2c1,FXP_SLAVE_ADDR,(uint8_t*)txBuffer,1,I2C_Timeout));
}


uint32_t FXPS7115::fxpReadPressure(){
	uint8_t* data_L;
	uint8_t* data_H;
	writeByte(FXP_SNSDATA0_L_REG);
	if(HAL_I2C_Master_Receive(&hi2c1, FXP_SLAVE_ADDR<<1, data_L, 1, I2C_Timeout) != HAL_OK){
		return 0;
	}
	writeByte(FXP_SNSDATA0_H_REG);
	if(HAL_I2C_Master_Receive(&hi2c1, FXP_SLAVE_ADDR<<1, data_H, 1, I2C_Timeout) == HAL_OK){
		return 0;
	}

	model->setPressure(data_H<<8 + data_L);
}


uint32_t FXPS7115::fxpReadTemp(){
	uint8_t* buffer;
	writeByte(FXP_TEMPERATURE_REG);
	if(HAL_I2C_Master_Receive(&hi2c1, FXP_SLAVE_ADDR<<1, buffer, 1, I2C_Timeout) == HAL_OK){
		model->setTempOutside8Bit(buffer);
	}

}
