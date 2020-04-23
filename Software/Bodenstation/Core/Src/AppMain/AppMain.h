/*
 * AppMain.h
 *
 *  Created on: 13.04.2020
 *      Author: marce
 */

#include "../Model/Model.h"
#include "../GPS/GPS.h"
//#include "../RFM95/RFM95.h"
//#include "../RFM95/RFM95_def.H"
#include "../RFM95/LORA/RFM95LoRa.h"
#include "stm32l4xx_hal.h"
#include "../USB/USBCom.h"
#include "i2c.h"
#include "spi.h"



#ifndef SRC_APPMAIN_APPMAIN_H_
#define SRC_APPMAIN_APPMAIN_H_

#define TRANSMIT_DATA_LENGTH		(GPS_DATA_SIZE*2 + 20)



class AppMain {
public:

	Model model = Model();


	 RFM95_LoRa rfm95 	= RFM95_LoRa();						//Radio module
	 GPS gps 		= GPS(&model);					//GPS
	 USB_Com usbCom = USB_Com();					//USB


	AppMain();

	void mainProg(void);
	void USB_Transmit(uint8_t* data, uint8_t size);
private:

	void initRFM(void);

};

#endif /* SRC_APPMAIN_APPMAIN_H_ */
