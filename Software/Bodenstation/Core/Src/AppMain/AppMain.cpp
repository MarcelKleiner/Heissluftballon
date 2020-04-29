/*
 * AppMain.cpp
 *
 *  Created on: 13.04.2020
 *      Author: marce
 */

#include "AppMain.h"

AppMain::AppMain() {
}

void AppMain::initRFM() {

	rfm95.setFrequency(868000000);
	rfm95.setSignalBandwidth(31.25E3);
	rfm95.setSpreadingFactor(12);
	rfm95.setCodingRate4(5);
	if (!rfm95.begin(866E6)) {
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	}
}

void AppMain::mainProg() {


	HAL_Delay(100);
	gps.init();
	initRFM();

	uint8_t transmitData[TRANSMIT_DATA_LENGTH];		//transmit Data

	uint8_t transmitUSB1[TRANSMIT_DATA_LENGTH/3];
	uint8_t transmitUSB2[TRANSMIT_DATA_LENGTH/3];
	uint8_t transmitUSB3[TRANSMIT_DATA_LENGTH/3];

	uint8_t txOffset 	= 0;	//offset after payload read
	uint8_t counter 	= 0;	//Payload counter
	uint8_t gpsCounter	= 0;	//GPS Counter
	uint8_t splitCnt	= 0;	//sliptcounter
	uint8_t packetSize 	= 0;	//packetsize from RFM95 receive

	bool init			= true;
	while (1) {

		if(init){
			init = false;
		}else{
			/*Prepare for Transmit*/

			//-----------------------read RFM data------------------------------
			packetSize = rfm95.parsePacket();
			if (packetSize != 0) {
				counter = 0;
				while (rfm95.available()) {
					transmitData[counter] = rfm95.read();
					counter++;
				}
				counter++;
				transmitData[counter] = rfm95.packetRssi();
				HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

			//---------------------add separator----------------------------

			transmitData[counter] = '$';
			transmitData[counter+1] = '!';


			//---------------------read GCS GPS data----------------------------
			char *gpsData = model.getGPS_GCS();
			txOffset = counter+2;

			for (gpsCounter = 0; gpsCounter < GPS_DATA_SIZE; gpsCounter++) {
				transmitData[txOffset] = gpsData[gpsCounter];
				txOffset++;
			}

			//---------------------add sync bytes----------------------------
			txOffset++;
			transmitData[txOffset] = '!';
			txOffset++;
			transmitData[txOffset] = '*';
			txOffset++;
			transmitData[txOffset] = '%';

			//---------------------split transmitData----------------------------
			splitCnt = 0;
			for(int a = 0; a<3;a++){
				for(int b = 0; b < (TRANSMIT_DATA_LENGTH/3);b++ ){
					if(splitCnt <= TRANSMIT_DATA_LENGTH){
						switch (a) {
							case 0:
								transmitUSB1[b] = transmitData[splitCnt];
								break;
							case 1:
								transmitUSB2[b] = transmitData[splitCnt];
								break;
							case 2:
								transmitUSB3[b] = transmitData[splitCnt];
								break;
							default:
								break;
						}
						splitCnt++;
					}
				}
			}

			usbCom.usbTransmit(transmitUSB1, (TRANSMIT_DATA_LENGTH/3));
			usbCom.usbTransmit(transmitUSB2, (TRANSMIT_DATA_LENGTH/3));
			usbCom.usbTransmit(transmitUSB3, (TRANSMIT_DATA_LENGTH/3));
		}
		}
	}
}

