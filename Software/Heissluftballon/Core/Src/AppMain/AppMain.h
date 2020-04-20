/*
 * AppMain.h
 *
 *  Created on: 13.04.2020
 *      Author: marce
 */

#include "../Model/Model.h"
#include "../GPS/GPS.h"
#include "../SHT21/SHT21.h"
#include "../FXPS7115D4/FXPS7115.h"
#include "../RFM95/RFM95.h"
#include "../RFM95/RFM95_def.H"
#include "../MAX31865/MAX31865TEMP.h"
#include "stm32l4xx_hal.h"
#include "../USB/USBCom.h"
#include "i2c.h"




#ifndef SRC_APPMAIN_APPMAIN_H_
#define SRC_APPMAIN_APPMAIN_H_

#define TRANSMIT_DATA_LENGTH		(GPS_DATA_SIZE*2 + 20)



class AppMain {
public:

	Model model = Model();

	 FXPS7115 fxps7115 = FXPS7115(&model);		//Pressure sensor
	 MAX31865_TEMP max31865 = MAX31865_TEMP(&model);	//External Temperature sensor
	 SHT21 sht21 = SHT21(&model);				//Onboard Temperature & Humidity sensor
	 RFM95 rfm95_1 = RFM95();						//Radio module
	 GPS gps = GPS(&model);					//GPS
	 USB_Com usbCom = USB_Com();					//USB


	AppMain();

	void mainProg(void);
	void USB_Transmit(uint8_t* data, uint8_t size);
private:


};

#endif /* SRC_APPMAIN_APPMAIN_H_ */
