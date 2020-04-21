/*
 * AppMain.cpp
 *
 *  Created on: 13.04.2020
 *      Author: marce
 */

#include "AppMain.h"


//extern SPI_HandleTypeDef hspi1;

AppMain::AppMain() {
}


void AppMain::initRFM(){
	RFM95::GPIO_HW_SETTINGS gpioHwSettings;
	RFM95::SPI_HW_SETTINGS spiHwSettings;

	gpioHwSettings.gpioPin0 = RFM_DIO0_Pin;
	gpioHwSettings.gpioPin1 = RFM_DIO1_Pin;
	gpioHwSettings.gpioPin2 = RFM_DIO2_Pin;
	gpioHwSettings.gpioPin3 = RFM_DIO3_Pin;
	gpioHwSettings.gpioPin4 = RFM_DIO4_Pin;
	gpioHwSettings.gpioPin5 = RFM_DIO5_Pin;

	gpioHwSettings.gpioPort0 = RFM_DIO0_GPIO_Port;
	gpioHwSettings.gpioPort1 = RFM_DIO1_GPIO_Port;
	gpioHwSettings.gpioPort2 = RFM_DIO2_GPIO_Port;
	gpioHwSettings.gpioPort3 = RFM_DIO3_GPIO_Port;
	gpioHwSettings.gpioPort4 = RFM_DIO4_GPIO_Port;
	gpioHwSettings.gpioPort5 = RFM_DIO5_GPIO_Port;

	gpioHwSettings.gpioPortRST = RFM_NSS_GPIO_Port;
	gpioHwSettings.gpioPinRST = RFM_NSS_Pin;

	spiHwSettings.gpioPin = RFM_NSS_Pin;
	spiHwSettings.gpioPort = RFM_NSS_GPIO_Port;
	spiHwSettings.hspi = &hspi1;

	rfm95.initRFM(100, spiHwSettings, gpioHwSettings);
}





void AppMain::mainProg(){


	uint8_t transmitData[TRANSMIT_DATA_LENGTH];
	uint16_t transmitBuffer = 0;

	for(int counter = 0; counter < TRANSMIT_DATA_LENGTH; counter++){
			transmitData[counter] = 0;
	}

	HAL_Delay(100);
	gps.init();
	initRFM();
	rfm95.rfmReceive();
	Stack *rfmStack = rfm95.rfmStack();

	while(1){
		/*Prepare for Transmit*/

		uint16_t stackCounter = 1;
		transmitData[0] = '%';

		if(rfm95.isDataReady()){
			while(!rfmStack->isEmpty()){
				transmitData[stackCounter] = rfmStack->pop();
				stackCounter++;
			}
		}
		uint8_t offset = stackCounter;	//Fortlaufend zu vorheriger index
		uint8_t counter = 0;
		char *gpsGCSTemp = model.getGPS_GCS();
		for(counter = 0; counter < GPS_DATA_SIZE; counter++){
			transmitData[offset] = gpsGCSTemp[counter];
			offset++;

		}
		transmitData[offset] = '*';
		transmitData[offset+1] = '!';

		/*Transmit over USB - use only in GCS*/

		usbCom.usbTransmit(transmitData, TRANSMIT_DATA_LENGTH);

		/*Transmit over air - use only in device*/





		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_Delay(500);
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_Delay(500);

	}
}

