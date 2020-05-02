/*
 * GPS.cpp
 *
 *  Created on: 13.04.2020
 *      Author: marce
 */

#include "GPS.h"


	//extern UART_HandleTypeDef huart2;


GPS::GPS(Model* model) {
	this->model = model;
	init();
}



/*
 * Initialize GPS
 *
 * @param none
 * @return none
 *
 */
void GPS::init(){
	for (int i = 0; i < GPS_DATA_SIZE; i++) {
		data[i] = '0';
		GPS_Data[i] = '0';
	}
}



/*
 * returns the GPS data array
 *
 * @param none
 * @return GPS data array
 *
 */
char* GPS::getGPSData(void) {
	return GPS_Data;
}



/*
* Rx Transfer completed callback.
*
*
* @param huart UART handle.
* @return None
 */
void GPS::gpsInterrupt(uint8_t rxData) {

	static uint8_t i = 0;
		/* Receive one byte in interrupt mode */


		/*Check if received byte is a '$' (begin of record) */
		if ((char) rxData == '$') {
			recordStart = true;
			i = 0;
		}
		/*Check if received byte is a '\n' (end of record)*/
		if ((char) rxData == '\n') {
			recordStart = false;

			if (i > GPS_DATA_SIZE-10) {
				copyCounter = 0;
				for (int i = 0; i < GPS_DATA_SIZE; i++) {
					GPS_Data[i] = '0';
				}
				while (data[copyCounter] != '\r' && copyCounter <= 80) {
					GPS_Data[copyCounter] = data[copyCounter];
					copyCounter++;
				}
			}
			model->setGPS_GCS(GPS_Data);	//set GPS data in Model
			for (int count = 0; count < GPS_DATA_SIZE; count++) {
				data[count] = '0';
			}
			i = 0;
		}

		if (recordStart) {
			data[i] = rxData;
			i++;
		}



	}

