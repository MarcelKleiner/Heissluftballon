/*
 * AppMain.cpp
 *
 *  Created on: 13.04.2020
 *      Author: marce
 */

#include "AppMain.h"






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

	gpioHwSettings.gpioPortRST = RFM_RST_GPIO_Port;
	gpioHwSettings.gpioPinRST = RFM_RST_Pin;

	spiHwSettings.gpioPin = RFM_NSS_Pin;
	spiHwSettings.gpioPort = RFM_NSS_GPIO_Port;
	spiHwSettings.hspi = &hspi1;

	rfm95.initRFM(TRANSMIT_DATA_LENGTH, spiHwSettings, gpioHwSettings);
}

void AppMain::mainProg(){


	uint8_t transmitData[TRANSMIT_DATA_LENGTH];
	uint16_t transmitBuffer = 0;

	for(int counter = 0; counter < TRANSMIT_DATA_LENGTH; counter++){
			transmitData[counter] = 0;
	}

	HAL_Delay(100);
	max31865.init(2);
	fxps7115.fxpInit();
	gps.init();

	initRFM();


	while(1){
		/*read Sensor Data*/
		sht21.readSHT21Humidity();		//Humidity
		sht21.readSHT21Temp();			//TempOutside
		fxps7115.fxpReadPressure();		//Pressure
		max31865.readTemp();			//TempInside

		/*Prepare for Transmit*/

		transmitData[0] = '%';
		transmitBuffer = model.getHumidity();
		transmitData[1] = transmitBuffer;
		transmitData[2] = transmitBuffer>>8;
		transmitData[3] = '!';
		transmitBuffer = model.getTempOutside();
		transmitData[4] = transmitBuffer;
		transmitData[5] = transmitBuffer>>8;
		transmitData[6] = '!';
		transmitBuffer = model.getPressure();
		transmitData[7] = transmitBuffer;
		transmitData[8] = transmitBuffer>>8;
		transmitData[9] = '!';
		transmitBuffer = model.getTempInsed();
		transmitData[10] = transmitBuffer;
		transmitData[11] = transmitBuffer>>8;
		transmitData[12] = '!';
		uint8_t offset = 13;	//Fortlaufend zu vorheriger index
		uint8_t counter = 0;
		char* gpsDeviceTemp = model.getGPS_Device();
		for(counter = 0; counter < GPS_DATA_SIZE; counter++){
			transmitData[offset] = gpsDeviceTemp[counter];
			offset++;
		}
		transmitData[offset] = '*';
		transmitData[offset+1] = '!';

		/*Transmit over USB - use only in GCS*/

		rfm95.rfmTransmit(transmitData);

		/*Transmit over air - use only in device*/





		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_Delay(500);
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_Delay(500);

	}
}

