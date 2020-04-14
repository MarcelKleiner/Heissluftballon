/*
 * GPS.h
 *
 *  Created on: 13.04.2020
 *      Author: marce
 */

#ifndef SRC_GPS_GPS_H_
#define SRC_GPS_GPS_H_

#include "stm32l4xx_hal.h"
#include "usart.h"
#include "../config/Config.h"
#include "../Model/Model.h"


class GPS {
public:
	GPS(Model* model);

	void init(void);
	char* getGPSData(void);
	void gpsInterrupt(UART_HandleTypeDef *UartHandle);
private:
	//*********************variable declaration*********************

	Model* model;

	bool recordStart = false;

	uint8_t rxByte = 0;
	char GPS_Data[GPS_DATA_SIZE];
	char data[GPS_DATA_SIZE];

	uint8_t copyCounter = 0;
	uint8_t globalArrayCnt = 0;
	uint8_t localArrayCnt = 0;

	//*************************************************************
};

#endif /* SRC_GPS_GPS_H_ */
