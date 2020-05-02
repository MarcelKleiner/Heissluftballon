/*
 * Model.cpp
 *
 *  Created on: 13.04.2020
 *      Author: marce
 */

#include "Model.h"

Model::Model() {

	for(uint8_t counter = 0; counter<GPS_DATA_SIZE; counter++){
		 gpsGCS[counter] = 11;
		 gpsDevice[counter] = 22;
	}
	 humidity = 0;
	 pressure = 0;
	 tempOutisde = 0;
	 tempOutisde8Bit = 0;
	 tempInside = 0;
}


//get/set GPS_GCS Data
void Model::Model::setGPS_GCS(char* data){
	//not implemented in Device
	strncpy(gpsGCS, data, GPS_DATA_SIZE);
}
char* Model::getGPS_GCS(void){
	//not implemented in Device
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
	pressure = (data -32768);
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

//get/set TempOutside from Pressure Sensor (Res 8Bit)
void  Model::setTempOutside8Bit(uint8_t data){
	tempOutisde8Bit = data;
}

uint8_t  Model::getTempOutside8Bit(){
	return tempOutisde8Bit;
}

//get/set TempInside
void Model::setTempInside(uint16_t data){
	tempInside = data;
}
uint16_t Model::getTempInsed(void){
	return tempInside;
}
