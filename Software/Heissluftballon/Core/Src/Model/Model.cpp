/*
 * Model.cpp
 *
 *  Created on: 13.04.2020
 *      Author: marce
 */

#include "Model.h"

Model::Model() {

	for(uint8_t counter = 0; counter<GPS_DATA_SIZE; counter++){
		 gpsGCS[counter] = 0;
		 gpsDevice[counter] = 0;
	}
	 humidity = 0;
	 pressure = 0;
	 tempOutisde = 0;
	 tempInside = 0;
}


//get/set GPS_GCS Data
void Model::Model::setGPS_GCS(char* data){
	strncpy(gpsGCS, data, GPS_DATA_SIZE);
}
char* Model::getGPS_GCS(void){
	return gpsGCS;
}

//get/set GPS_Device Data
void Model::setGPS_Device(char* data){
	strncpy(gpsDevice, data, GPS_DATA_SIZE);
}
char* Model::getGPS_Device(void){
	return gpsDevice;
}

//get/set Humidity
void Model::setHumidity(uint16_t data){
	humidity = data;
}
uint16_t Model::getHumidity(void){
	return humidity;
}

//get/set Pressure
void Model::setPressure(uint16_t data){
	pressure = data;
}
uint16_t Model::getPressure(void){
	return pressure;
}

//get/set TempOutise
void Model::setTempOutside(uint16_t data){
	tempOutisde = data;
}
uint16_t Model::getTempOutside(void){
	return tempOutisde;
}

//get/set TempInside
void Model::setTempInside(uint16_t data){
	tempInside = data;
}
uint16_t Model::getTempInsed(void){
	return tempInside;
}
