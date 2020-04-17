/*
 * SHT21.h
 *
 *  Created on: Apr 10, 2020
 *      Author: marce
 */

#include "i2c.h"
#include "stm32l4xx_hal.h"
#include "../config/I2C_Config.h"


#ifndef SRC_SHT21_SHT21_H_
#define SRC_SHT21_SHT21_H_



/*STH21 Temp/Humidity register config*/
#define SHT21_SLAVE_ADDR		0x80

#define SHT21_TEMP_REG			0xE3
#define SHT21_HUMIDITY_REG		0xE5

#define SHT21_SOFT_RST_REG		0XFE




class SHT21 {
public:
	SHT21();
	void initSHT21(void);
	uint32_t readSHT21Temp(void);
	uint32_t readSHT21Humidity(void);


private:
	HAL_StatusTypeDef writeByte(uint8_t addr);
};

#endif /* SRC_SHT21_SHT21_H_ */
