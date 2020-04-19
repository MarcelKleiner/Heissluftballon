/*
 * USBCom.cpp
 *
 *  Created on: Apr 17, 2020
 *      Author: marce
 */

#include "USBCom.h"

USB_Com::USB_Com() {
	// TODO Auto-generated constructor stub

}


bool USB_Com::usbTransmit(uint8_t *data, uint8_t size){
	uint16_t counter = 0;
	while(CDC_Transmit_FS((uint8_t*) data, size) != USBD_OK){
		counter++;
		if(counter >= USB_TIMEOUT){
			return false;	//Trasmit faild
		}
	}
	return true;	//Transmit successful
}


void USB_Com::usbReceive(uint8_t *data){
	//ToDo
}
