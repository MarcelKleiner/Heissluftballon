/*
 * Model.h
 *
 *  Created on: 13.04.2020
 *      Author: marce
 */

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

	void setTempInside(uint16_t data);
	uint16_t getTempInsed(void)

};

#endif /* SRC_MODEL_MODEL_H_ */
