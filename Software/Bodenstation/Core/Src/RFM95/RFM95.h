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
#include "Stack.h"

#define SPI_TIMEOUT			100
#define GPIO_TIMEOUT		250

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

		GPIO_TypeDef* gpioPortRST;
		uint16_t gpioPinRST;
	};

	enum MODE{
		SLEEP	= RF_OPMODE_SLEEP,
		STANDBY	= RF_OPMODE_STBY,
		FSTX 	= RF_OPMODE_FSTX,
		TX		= RF_OPMODE_TX,
		FSRX	= RF_OPMODE_FSRX,
		RX		= RF_OPMODE_RX
	};

	enum RFM_INIT_Typedef{
		RFM_OK,
		RFM_PAYLOAD_ERROR,
		RFM_INIT_FAIL
	};

	RFM_INIT_Typedef initRFM(uint16_t maxPayloadLength, SPI_HW_SETTINGS spiHwSettings, GPIO_HW_SETTINGS gpioHwSettings);
	void setOutputPower(uint8_t outputPower);
	void resetRFM(void);
	Stack* rfmStack(void);

	void rfmTransmit(uint8_t* data);
	void rfmReceive(void);
	bool isDataReady(void);


private:

	SPI_HW_SETTINGS spiHwSettings;
	GPIO_HW_SETTINGS gpioHwSettings;
	uint16_t payloadLength;
	Stack stack;


	//local internal variable
	MODE currentMode = STANDBY;
	uint8_t userOutputPower;

	void deselectRFM(void);
	void selectRFM(void);

	void rcCalibration(void);
	void setMode(MODE mode);
	bool readGPIO(uint8_t gpioPin);

	HAL_StatusTypeDef writeReg(uint8_t addr, uint8_t data);
	uint8_t readReg(uint8_t addr);

	RFM_INIT_Typedef writeFIFO(uint8_t* data);
	void readFIFO(void);

};





#endif /* SRC_RFM95_RFM95_H_ */
