/*
 * Model.h
 *
 *  Created on: 13.04.2020
 *      Author: marce
 */

#include "../config/Config.h"
#include "stm32l4xx_hal.h"
#include "string.h"

#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_




class Model {
public:
	Model();



	void setGPS_GCS(char* data);
	char* getGPS_GCS(void);

	void setGPS_Device(char* data);
	char* getGPS_Device(void);

	void setHumidity(uint16_t data);
	uint16_t getHumidity(void);

	void setPressure(uint16_t data);
	uint16_t getPressure(void);

	void setTempOutside(uint16_t data);
	uint16_t getTempOutside(void);

	void setTempOutside8Bit(uint8_t data);
	uint8_t getTempOutside8Bit(void);

	void setTempInside(uint16_t data);
	uint16_t getTempInsed(void);

private:

	char gpsGCS[GPS_DATA_SIZE];
	char gpsDevice[GPS_DATA_SIZE];
	uint16_t humidity;
	uint16_t pressure;
	uint16_t tempOutisde;
	uint8_t tempOutisde8Bit;
	uint16_t tempInside;


};

#endif /* SRC_MODEL_MODEL_H_ */
