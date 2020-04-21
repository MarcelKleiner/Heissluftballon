/*
 * USBCom.h
 *
 *  Created on: Apr 17, 2020
 *      Author: marce
 */

#include "stm32l4xx_hal.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"


#ifndef SRC_USB_USBCOM_H_
#define SRC_USB_USBCOM_H_


#define USB_TIMEOUT		100



class USB_Com {
public:
	USB_Com();


	bool usbTransmit(uint8_t *data, uint8_t size);
	void usbReceive(uint8_t *data);




};

#endif /* SRC_USB_USBCOM_H_ */
