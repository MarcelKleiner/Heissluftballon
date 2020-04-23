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
	rfm95.setTxPower(17, PA_OUTPUT_PA_BOOST_PIN);
	rfm95.setSignalBandwidth(31.25E3);
	rfm95.setSpreadingFactor(12);
	rfm95.setCodingRate4(5);
	if (!rfm95.begin(866E6)) {
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	}

}

void AppMain::mainProg() {

	uint8_t transmitData[TRANSMIT_DATA_LENGTH];
	uint16_t transmitBuffer = 0;

	for (int counter = 0; counter < TRANSMIT_DATA_LENGTH; counter++) {
		transmitData[counter] = 0;
	}

	HAL_Delay(100);
	max31865.init(2);
	fxps7115.fxpInit();
	gps.init();

	initRFM();

	while (1) {
		/*read Sensor Data*/
		sht21.readSHT21Humidity();		//Humidity
		sht21.readSHT21Temp();			//TempOutside
		fxps7115.fxpReadPressure();		//Pressure
		max31865.readTemp();			//TempInside

		/*Prepare for Transmit*/

		transmitData[0] = '%';
		transmitData[1] = '*';
		transmitData[2] = '!';
		/*-------------Humidity Balloon----------------*/
		transmitBuffer = model.getHumidity();
		transmitData[3] = transmitBuffer;
		transmitData[4] = transmitBuffer >> 8;
		/*-------------Temp Outside----------------*/
		transmitBuffer = model.getTempOutside();
		transmitData[5] = transmitBuffer;
		transmitData[6] = transmitBuffer >> 8;
		/*-------------Pressure----------------*/
		transmitBuffer = model.getPressure();
		transmitData[7] = transmitBuffer;
		transmitData[8] = transmitBuffer >> 8;
		/*-------------Temp Balloon----------------*/
		transmitBuffer = model.getTempInsed();
		transmitData[9] = transmitBuffer;
		transmitData[10] = transmitBuffer >> 8;
		uint8_t offset = 11;	//Fortlaufend zu vorheriger index
		/*-------------GPS Data----------------*/
		char *gpsDeviceTemp = model.getGPS_Device();
		for (uint8_t counter = 0; counter < GPS_DATA_SIZE; counter++) {
			transmitData[offset] = gpsDeviceTemp[counter];
			offset++;
		}

		/*Transmit over USB - use only in GCS*/
		//usbCom.usbTransmit(transmitData, offset);
		//rfm95.rfmTransmit(transmitData);
		rfm95.beginPacket();
		rfm95.write(transmitData, offset);
		rfm95.endPacket();
		HAL_Delay(1000);
	}

}

