/*
 * GPS.h
 *
 *  Created on: Apr 10, 2020
 *      Author: marce
 */

#include "stm32f3xx_hal.h"

#ifndef SRC_GPS_GPS_H_
#define SRC_GPS_GPS_H_

class GPS {
public:
	GPS();

	void init(void);
	char* getGPSData(void);
	void gpsInterrupt(UART_HandleTypeDef *UartHandle);




};

#endif /* SRC_GPS_GPS_H_ */
