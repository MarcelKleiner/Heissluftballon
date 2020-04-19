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


class RFM95 {
public:
	RFM95();

	enum RFM_DIR{
		DIR_TX,
		DIR_RX
	};

	typedef enum MODE{
		TX		= 0x0C,
		RX		= 0x10,
		SLEEP	= 0x00,
		STANDBY	= 0X04
	};

	void initRFM(void);

	void writeReg(uint8_t addr, uint8_t data);
	uint8_t readReg(uint8_t addr);

	void writeFIFO(void);
	void readFIFO(void);

	void setTransmitDirection(RFM_DIR rfmDir);
	void setMode(MODE mode);


private:





};





#endif /* SRC_RFM95_RFM95_H_ */
