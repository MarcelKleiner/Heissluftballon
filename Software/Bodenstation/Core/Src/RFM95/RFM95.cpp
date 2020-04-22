/*
 * RFM95.cpp
 *
 *  Created on: 15.04.2020
 *      Author: marce
 */

#include "RFM95.h"
#include "../AppMain/AppMain.h"

RFM95::RFM95() {
	// TODO Auto-generated constructor stub
	userOutputPower = 0;
}



RFM95::RFM_INIT_Typedef RFM95::initRFM(uint16_t maxPayloadLength, SPI_HW_SETTINGS spiHwSettings, GPIO_HW_SETTINGS gpioHwSettings){
	this->spiHwSettings = spiHwSettings;
		this->gpioHwSettings = gpioHwSettings;
		this->payloadLength = maxPayloadLength;

		if(payloadLength > 1024){
			return RFM_PAYLOAD_ERROR;	//payload length size too big
		}

		resetRFM();
//
	const uint8_t CONFIG[][2] ={
//		/*0x01*/	{REG_OP_MOD, RF_OPMODE_FSK | RF_OPMODE_MODULATION_FSK | RF_OPMODE_LFM_OFF | RF_OPMODE_STBY },
//
//		/*0x02*/	{REG_BITRATE_MSB, RF_BITRATEMSB_4800 },
//		/*0x03*/	{REG_BITRATE_LSB, RF_BITRATELSB_4800 },
//		/*0x04*/	{REG_FDEV_MSB, 0x00},
//		/*0x05*/	{REG_FDEV_LSB, 0x52},
//
		/*0x06*/	{REG_FRF_MSB,RF_FRFMSB_868000},
		/*0x07*/	{REG_FRF_MID,RF_FRFMID_868000},
		/*0x08*/	{REG_FRF_LSB,RF_FRFLSB_868000},
//
//		/*0x09*/	{REG_PA_CONFIG,RF_PA_10DBM },
//		/*0x0A*/	{REG_RX_BW, RF_RXBW_MANT_16 | RF_RXBW_EXP_2},
//
//		/*0x10*/	{REG_RSSI_THRESH, 220},	// must be set to dBm = (-Sensitivity / 2), default is 0xE4 = 228 so -114dBm
//
//		/*0x25*/	{REG_PREAMBLE_MSB, 0x00},	//preamble size MSB
//		/*0x26*/	{REG_PREAMBLE_LSB, 0x03},	//Preamble size LSB
//
		/*0x3E*/	{REG_IRQ_FLAGS_1, 0x0A},	//clear all interrupts
		/*0x3F*/	{REG_IRQ_FLAGS_2, 0x11},	//clear all interrupts
//
//		/*0x40*/	{REG_DIO_MAPPING_1, RF_DIO_0_RX_PAYLOADRDY | RF_DIO_1_ALL_FIFOEMPTY | RF_DIO_2_RX_RX_RDY},
//		/*0x41*/	{REG_DIO_MAPPING_2, RF_DIO_4_RX_PREAMBLEDETECT | RF_DIO_5_ALL_MODERDY},
//
//		/*0x27*/  	{REG_SYNC_CONFIG, RF_SYNC_AUTO_RESTART_ON_PLL | RF_SYNC_PREAMBLE_0XAA | RF_SYNC_SYNC_ON | RF_SYNC_FIFOFILL_INT | RF_SYNC_SYNC_SIZE_3},
//		/*0x28*/	{REG_SYNC_VALUE_1,0xAA},
//		/*0x29*/  	{REG_SYNC_VALUE_2,0xAA},
//		/*0x2A*/  	{REG_SYNC_VALUE_3,0xAA},
//		/*0x2A*/  	{REG_SYNC_VALUE_4,0xAA},
//		/*0x30*/  	{REG_PACKET_CONFIG_1, RF_PACKET1_FORMAT_VAR | RF_PACKET1_DC_OFF | RF_PACKET1_CRC_ON | RF_PACKET1_CRC_AUTOCLEAR_OFF | RF_PACKET1_ADDR_FILT_OFF | RF_PACKET1_CRC_CCITT},
//
//
//
//		/*0x31*/  	{REG_PACKET_CONFIG_2, RF_PACKET2_DATA_MODE_PACKET | RF_PACKET2_IHOME_OFF | RF_PACKET2_BACON_OFF | (uint8_t)((payloadLength>>8) & 0x03)},
//		/*0x32*/	{REG_PAYLOAD_LENGTH, (uint8_t)(payloadLength)},
//
//
		/*0x36*/	{REG_FIFO_THRESH, RF_FIFOTHRESH_TXSTART_FIFOEMPTY | RF_FIFOTHRESH_FIFO_INT_0},
//
//
//
		{255,0}
	};
//
//	//write config array
	  for (uint8_t i = 0;CONFIG[i][0] != 255; i++){
		  if(writeReg(CONFIG[i][0], CONFIG[i][1]) == HAL_ERROR){
			return RFM_INIT_FAIL;
		  }
	  }

	 rcCalibration();
	 return RFM_OK;
}


void RFM95::rfmTransmit(uint8_t* data){
	setMode(STANDBY);	// set Standby Mode
	uint8_t localData[100];
	for(int i = 0; i<50; i++){
		localData[i] = data[i];
	}
	writeFIFO(localData);	//write data to RFM fifo
	setMode(TX);		// set TX Mode
	readGPIO(0);		// wait until packet is sent
	setMode(STANDBY);	// set Standby Mode

}

bool RFM95::isDataReady(void){
	if(currentMode != RX){
		setMode(RX);
	}
	//check if Data in FIFO
	if(HAL_GPIO_ReadPin(gpioHwSettings.gpioPort0, gpioHwSettings.gpioPin0) == GPIO_PIN_RESET){
		setMode(STANDBY);
		readFIFO();
		return true;
	}else{
		return false;
	}
}

void RFM95::rfmReceive(void){
	setMode(RX);
	uint8_t irq = readReg(REG_IRQ_FLAGS_1);
	uint8_t irq2 = readReg(REG_IRQ_FLAGS_2);
	if(irq != 216){
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	}
}



/*
 * @brief RFM95 chip select
 *
 * @param none
 * @return none
 */
void RFM95::selectRFM(){
	HAL_GPIO_WritePin(spiHwSettings.gpioPort,spiHwSettings.gpioPin, GPIO_PIN_RESET);
}

/*
 * @brief RFM95 chip deselect
 *
 * @param none
 * @return none
 */
void RFM95::deselectRFM(){
	HAL_GPIO_WritePin(spiHwSettings.gpioPort,spiHwSettings.gpioPin, GPIO_PIN_SET);
}

/*
 * @brief write reg in RFM95
 *
 * @param addr specific register address
 * @param data data to be written
 *
 * @return none
 */
HAL_StatusTypeDef RFM95::writeReg(uint8_t addr, uint8_t data){
	uint8_t buff[2] = {(uint8_t)(addr | 0x80), data};
	selectRFM();
	if(HAL_SPI_Transmit(spiHwSettings.hspi, (uint8_t*)buff, 2, SPI_TIMEOUT) != HAL_OK){
		deselectRFM();
		return HAL_ERROR;
	}
	deselectRFM();
	return HAL_OK;
}

/*
 * @brief read reg from RFM95
 *
 * @param addr specific register address
 * @return data from register
 *
 * @return none
 */
uint8_t RFM95::readReg(uint8_t addr){
	uint8_t rxData[2] = {0,0};
	uint8_t txData[1] = {addr};

	selectRFM();
		HAL_SPI_TransmitReceive(spiHwSettings.hspi,(uint8_t*)txData,(uint8_t*)rxData,2,100);
	deselectRFM();
	return rxData[1];
}


/*
 * @brief write data to RFM95 FIFO
 *
 * @param uint8_t data array
 * @return status successful/not successful (true/false)
 */
RFM95::RFM_INIT_Typedef RFM95::writeFIFO(uint8_t* data){
		uint8_t addr[1];
		addr[0] = (REG_FIFO | 0x80);
		selectRFM();
		HAL_SPI_Transmit(spiHwSettings.hspi, addr, 1, SPI_TIMEOUT);
		HAL_SPI_Transmit(spiHwSettings.hspi, data, sizeof(data)/sizeof(data[0]), SPI_TIMEOUT);
		deselectRFM();

		return RFM_OK;
}

void RFM95::readFIFO(void){
	setMode(STANDBY);
	uint8_t rxAddr[1] = {REG_FIFO};
	uint8_t rxData[2] = {0,0};
	selectRFM();
	HAL_SPI_Transmit(spiHwSettings.hspi, rxAddr, 1, SPI_TIMEOUT);
	uint16_t payloadCounter = 0;
	while(HAL_GPIO_ReadPin(gpioHwSettings.gpioPort1, gpioHwSettings.gpioPin1) == GPIO_PIN_RESET)// && payloadCounter<=(payloadLength+1))
	{
		HAL_SPI_Receive(spiHwSettings.hspi, rxData, 1,SPI_TIMEOUT);
	//	if(!stack.isFull()){
	//		stack.push(rxData[0]);
	//	}
		//payloadCounter++;
	}
	deselectRFM();
}


void RFM95::setMode(MODE mode){
	if(currentMode != mode){
		switch (mode){
		case RX:
			writeReg(REG_DIO_MAPPING_1, RF_DIO_0_RX_PAYLOADRDY | RF_DIO_1_ALL_FIFOEMPTY | RF_DIO_2_RX_RX_RDY);
			writeReg(REG_DIO_MAPPING_2, RF_DIO_4_RX_PREAMBLEDETECT);
			setOutputPower(0);
			break;
		case TX:
			writeReg(REG_DIO_MAPPING_1, RF_DIO_0_TX_PACKETSENT | RF_DIO_1_ALL_FIFOFULL | RF_DIO_3_TX_TX_RDY);
			setOutputPower(userOutputPower);
			break;
		case STANDBY:
			writeReg(REG_DIO_MAPPING_1, RF_DIO_1_ALL_FIFOEMPTY|RF_DIO_3_ALL_FIFOEMPTY);
			break;
		default:
			break;
		}
		uint8_t actMode = readReg(REG_OP_MOD);
		actMode &= 0xF8;
		actMode |= mode;
		writeReg(REG_OP_MOD, actMode);
		HAL_Delay(1);
		if(mode == RX){
			readGPIO(2);
		}else if(mode == TX){
			readGPIO(3);
		}
		this->currentMode = mode;
	}
}


bool RFM95::readGPIO(uint8_t gpioPin){
	uint8_t timeout = 0;
	uint16_t tempGpioPin;
	GPIO_TypeDef *tempGpioPort;
	switch (gpioPin) {
		case 0:
			tempGpioPin = gpioHwSettings.gpioPin0;
			tempGpioPort = gpioHwSettings.gpioPort0;
			break;
		case 1:
			tempGpioPin = gpioHwSettings.gpioPin1;
			tempGpioPort = gpioHwSettings.gpioPort1;
			break;
		case 2:
			tempGpioPin = gpioHwSettings.gpioPin2;
			tempGpioPort = gpioHwSettings.gpioPort2;
			break;
		case 3:
			tempGpioPin = gpioHwSettings.gpioPin3;
			tempGpioPort = gpioHwSettings.gpioPort3;
			break;
		case 4:
			tempGpioPin = gpioHwSettings.gpioPin4;
			tempGpioPort = gpioHwSettings.gpioPort4;
			break;
		case 5:
			tempGpioPin = gpioHwSettings.gpioPin5;
			tempGpioPort = gpioHwSettings.gpioPort5;
			break;
		default:
			break;
	}
	HAL_Delay(10);
	while(HAL_GPIO_ReadPin(tempGpioPort, tempGpioPin) == GPIO_PIN_RESET);

	if(timeout >= GPIO_TIMEOUT){
		return false;
	}else{
		return true;
	}
}

/*
 * @brief set outputpower
 *
 * @param uint8_t outputpower in dBm (0-20)
 * @return none
 */
void RFM95::setOutputPower(uint8_t outputPower){
	userOutputPower = outputPower;
	if(outputPower <= 15){
		writeReg(REG_PA_CONFIG, (uint8_t)(RF_PA_00DBM + outputPower));
	}else if(outputPower < 20){
		writeReg(REG_PA_CONFIG, (uint8_t)(RF_PA_16DBM - 16 + outputPower));
	}else{
		writeReg(REG_PA_CONFIG, RF_PA_20DBM);
	}
}


void RFM95::resetRFM(void){
	HAL_GPIO_WritePin(gpioHwSettings.gpioPortRST, gpioHwSettings.gpioPinRST, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(gpioHwSettings.gpioPortRST, gpioHwSettings.gpioPinRST, GPIO_PIN_SET);
	HAL_Delay(5);
}

void RFM95::rcCalibration(){
	setMode(STANDBY);
	writeReg(REG_OSC,RF_OSC_CAL_START_TRIGGER);
	HAL_Delay(100);
}

Stack* RFM95::rfmStack(){
	return &stack;
}


