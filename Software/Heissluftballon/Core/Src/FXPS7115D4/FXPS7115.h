/*
 * FXPS7115.h
 *
 *  Created on: Apr 10, 2020
 *      Author: marce
 */

#include "i2c.h"
#include "stm32l4xx_hal.h"
#include "../config/I2C_Config.h"

#include "../Model/Model.h"


#ifndef SRC_FXPS7115D4_FXPS7115_H_
#define SRC_FXPS7115D4_FXPS7115_H_


/*FXPS7115D4 Pressure sensor register config*/
#define FXP_SLAVE_ADDR			0x60


#define FXP_DEVSTAT_REG			0x01
#define FXP_DEVSTAT1_REG		0x02
#define FXP_DEVSTAT2_REG		0x03
#define FXP_DEVSTAT3_REG		0x04
#define FXP_TEMPERATURE_REG		0x0E

#define FXP_SNSDATA0_L_REG		0x63	//READ SNSDATA0_L BEVORE SNSDATA0_H
#define FXP_SNSDATA0_H_REG		0x63

#define FXP_SNSDATA1_L_REG		0x64	//READ SNSDATA0_L BEVORE SNSDATA0_H
#define FXP_SNSDATA1_H_REG		0x65

#define FXP_DEVLOCK_WR_REG		0x10



class FXPS7115 {
public:
	FXPS7115();

	void fxpInit(void);
	uint32_t fxpReadPressure(void);
	uint32_t fxpReadTemp(void);

private:
	HAL_StatusTypeDef writeByte(uint8_t addr);


	Model* model;


};

#endif /* SRC_FXPS7115D4_FXPS7115_H_ */
