/*
 * GPS.cpp
 *
 *  Created on: Apr 10, 2020
 *      Author: marce
 */

#include "GPS.h"
#include "main.h"


//*********************variable declaration*********************
extern UART_HandleTypeDef huart2;

bool recordStart = false;

uint8_t rxByte = 0;
char GPS_Data[80];
char data[80];

uint8_t copyCounter = 0;

uint8_t globalArrayCnt = 0;
uint8_t localArrayCnt = 0;

//*************************************************************




GPS::GPS() {
	// TODO Auto-generated constructor stub

}


/*
 * Initialize GPS
 *
 * @param none
 * @return none
 *
 */
void GPS::init(){
	for (int i = 0; i < 80; i++) {
		data[i] = '0';
		GPS_Data[i] = '0';
	}
	HAL_UART_Receive_IT(&huart2, &rxByte, 1);
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
void GPS::gpsInterrupt(UART_HandleTypeDef *UartHandle) {

	static uint8_t i = 0;


		/* Receive one byte in interrupt mode */
		HAL_UART_Receive_IT(UartHandle, &rxByte, 1);

		/*Check if received byte is a '$' (begin of record) */
		if ((char) rxByte == '$') {
			recordStart = true;
			i = 0;
		}
		/*Check if received byte is a '\n' (end of record)*/
		if ((char) rxByte == '\n') {
			recordStart = false;

			if (i > 70) {
				copyCounter = 0;
				while (data[copyCounter] != '\r') {
					GPS_Data[copyCounter] = data[copyCounter];
					copyCounter++;
				}
				HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			}else{
				GPS_Data[0] = 'T';
				GPS_Data[1] = 'X';
				GPS_Data[2] = ' ';
				GPS_Data[3] = 'N';
				GPS_Data[4] = 'o';
				GPS_Data[5] = ' ';
				GPS_Data[6] = 'G';
				GPS_Data[7] = 'P';
				GPS_Data[8] = 'S';
				GPS_Data[9] = ' ';
				GPS_Data[10] = 'S';
				GPS_Data[11] = 'i';
				GPS_Data[12]= 'g';
				GPS_Data[13] = 'n';
				GPS_Data[14] = 'a';
				GPS_Data[15] = 'l';
				copyCounter =  16;
			}
			for (int count = 0; count < 80; count++) {
				data[count] = '0';
			}
			i = 0;
		}

		if (recordStart) {
			data[i] = rxByte;
			i++;
		}

	}








