/*
 * MAX31865TEMP.h
 *
 *  Created on: Apr 17, 2020
 *      Author: marce
 */

#ifndef SRC_MAX31865_MAX31865TEMP_H_
#define SRC_MAX31865_MAX31865TEMP_H_


#include "stm32l4xx_hal.h"
#include "spi.h"

#include "../Model/Model.h"


#define MAX_CONFIG 			0x80
#define MAX_RTD_MSB			0x01
#define MAX_RTD_LSB			0x02
#define MAX_FAULT_STATUS	0x07

#define SET_MAX_CS				HAL_GPIO_WritePin(MAX_CS_GPIO_Port,MAX_CS_Pin,GPIO_PIN_SET)
#define CLEAR_MAX_CS			HAL_GPIO_WritePin(MAX_CS_GPIO_Port,MAX_CS_Pin,GPIO_PIN_RESET)

/********************* MAX31865 registers and config bits *********************/

#define MAX31865_READ                   0x00
#define MAX31865_WRITE                  0x80
#define MAX31856_RTDMSB_REG             0x01
#define MAX31856_CONFIG_REG             0x00
#define MAX31856_CONFIG_BIAS            0x80
#define MAX31856_CONFIG_1SHOT           0x20
#define MAX31856_CONFIG_3WIRE           0x10
#define MAX31856_CONFIG_MODEAUTO        0x40


/********************* General defines *********************/
#define ON 1
#define OFF 0


#define RREF 390                        // Reference resistor
#define FACTOR 32768                    // 2^15 used for data to resistance conversion
#define ALPHA 0.003851                  // PT-100 temperature coefficient


class MAX31865_TEMP {
public:
	MAX31865_TEMP(Model *model);

	void init(uint8_t wires);
	bool readTemp(void);



private:

	Model *model;


	void MAX31865_read(uint8_t addr, uint8_t *buffer, uint8_t size);
	void MAX31865_write(uint8_t addr, uint8_t data);
	void enableBias(uint8_t enable);
	void autoConvert(uint8_t enable);
	void setWires(uint8_t numwires);
	void single_shot(void);



};

#endif /* SRC_MAX31865_MAX31865TEMP_H_ */
