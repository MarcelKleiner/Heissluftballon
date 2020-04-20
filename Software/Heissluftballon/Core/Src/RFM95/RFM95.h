/*
 * RFM95.h
 *
 *  Created on: 15.04.2020
 *      Author: marce
 */

#ifndef SRC_RFM95_RFM95_H_
#define SRC_RFM95_RFM95_H_

#include "stm32l4xx_hal.h"
#include "RFM95_def.H"

#define SPI_TIMEOUT			100

class RFM95 {
public:
	RFM95();

	struct SPI_HW_SETTINGS{
		SPI_HandleTypeDef *hspi;
		GPIO_TypeDef* gpioPort;
		uint16_t gpioPin;
	};

	struct GPIO_HW_SETTINGS{
		GPIO_TypeDef* gpioPort0;
		uint16_t gpioPin0;
		GPIO_TypeDef* gpioPort1;
		uint16_t gpioPin1;
		GPIO_TypeDef* gpioPort2;
		uint16_t gpioPin2;
		GPIO_TypeDef* gpioPort3;
		uint16_t gpioPin3;
		GPIO_TypeDef* gpioPort4;
		uint16_t gpioPin4;
		GPIO_TypeDef* gpioPort5;
		uint16_t gpioPin5;
	};

	enum RFM_DIR{
		DIR_TX,
		DIR_RX
	};

	enum MODE{
		TX		= 0x0C,
		RX		= 0x10,
		SLEEP	= 0x00,
		STANDBY	= 0X04
	};

	void initRFM(uint8_t payloadLength, SPI_HW_SETTINGS spiHwSettings, GPIO_HW_SETTINGS gpioHwSettings);

	void writeReg(uint8_t addr, uint8_t data);
	uint8_t readReg(uint8_t addr);

	void writeFIFO(void);
	void readFIFO(void);

	void setTransmitDirection(RFM_DIR rfmDir);
	void setMode(MODE mode);


private:

	SPI_HW_SETTINGS spiHwSettings;
	GPIO_HW_SETTINGS gpioHwSettings;
	uint16_t payloadLength;

	void deselectRFM(void);
	void selectRFM(void);;
	GPIO_PinState readGPIO(GPIO_TypeDef* gpioPort, uint16_t gpioPin );

};





#endif /* SRC_RFM95_RFM95_H_ */
