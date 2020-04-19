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

HAL_StatusTypeDef FXPS7115::writeByte(uint8_t addr, uint8_t data){
	uint8_t txBuffer[1];
	txBuffer[0] = addr;
	return(HAL_I2C_Master_Transmit(&hi2c1,FXP_SLAVE_ADDR<<1,(uint8_t*)txBuffer,1,I2C_Timeout));
}



bool FXPS7115::fxpReadPressure(){
	uint8_t data[2] = {0,0};

	if(HAL_I2C_Mem_Read(&hi2c1, FXP_SLAVE_ADDR<<1, FXP_SNSDATA0_L_REG, 1, data, 2, I2C_Timeout) != HAL_OK){
		return 0;
	}

	model->setPressure((data[1]<<8) + data[0]);
	return 1;
}


bool FXPS7115::fxpReadTemp(){
	uint8_t data[1] = {0};

	if(HAL_I2C_Mem_Read(&hi2c1, FXP_SLAVE_ADDR<<1, FXP_SNSDATA0_L_REG, 1, data, 1, I2C_Timeout) != HAL_OK){
		return 0;
	}

	model->setTempOutside8Bit(data[0]);

	return 1;
}
