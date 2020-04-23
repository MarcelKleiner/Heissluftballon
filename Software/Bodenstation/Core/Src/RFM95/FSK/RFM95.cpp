/*
 * RFM95.cpp
 *
 *  Created on: 15.04.2020
 *      Author: marce
 */

#include "RFM95.h"
#include "../../AppMain/AppMain.h"

/*	RFM95::GPIO_HW_SETTINGS gpioHwSettings;
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

	rfm95.initRFM(TRANSMIT_DATA_LENGTH, spiHwSettings, gpioHwSettings);*/
//extern SPI_HandleTypeDef hspi1;




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
/*
		writeReg(REG_OP_MOD, 0x01);
		writeReg(REG_IRQ_FLAGS_1, 0xFF);
		writeReg(REG_IRQ_FLAGS_2, 0xFF);
		writeReg(REG_BITRATE_MSB, 0x1A);
		writeReg(REG_BITRATE_LSB, 0x0B);

		writeReg(REG_FDEV_LSB,0x52);		//hat funktioniert mit 0x52
		writeReg(REG_FDEV_MSB,0x00);		//hat funktioniert mit 0x00

		writeReg(REG_FRF_MSB,0xD9);
		writeReg(REG_FRF_MID,0x00);
		writeReg(REG_FRF_LSB,0x00);
		writeReg(REG_PA_CONFIG,0x8F);	//change
		writeReg(REG_PA_RAMP, 0x09);
		writeReg(REG_OCP, 0x3F);
		writeReg(REG_LNA, 0xC3);
		writeReg(REG_RX_CONFIG, 0xBE);
		writeReg(REG_RSSI_CONFIG,0x02);
		writeReg(REG_RSSI_COLLISION, 0x0A);
		writeReg(REG_RSSI_THRESH,0xFF);
		writeReg(REG_RX_BW,0x17);
		writeReg(REG_AFC_BW,0x07);
		writeReg(REG_PREAMBLE_DETECT, 0xAA);
		writeReg(REG_OSC, 0x0F);
		writeReg(REG_PREAMBLE_MSB,0x00);
		writeReg(REG_PREAMBLE_LSB, 0x03);
		writeReg(REG_SYNC_CONFIG, 0x93);
		writeReg(REG_SYNC_VALUE_1,0x4D);
		writeReg(REG_SYNC_VALUE_2,0x4D);
		writeReg(REG_SYNC_VALUE_3,0x4D);
		writeReg(REG_SYNC_VALUE_4,0x4D);
		writeReg(REG_PACKET_CONFIG_1, 0x50);
		writeReg(REG_PACKET_CONFIG_2, 0x40);
		writeReg(REG_PAYLOAD_LENGTH, 0x40);
		writeReg(REG_FIFO_THRESH, 0x80);
		writeReg(REG_IMAGE_CAL, 0xC2);
		writeReg(REG_PA_DAC, 0x07);
		writeReg(REG_OOK_PEAK, 0x20);
		 rcCalibration();
		 writeReg(REG_AFC_FEI, 0x11);

		 writeReg(REG_SEQ_CONFIG_1, 0x80);


		writeReg(REG_OP_MOD, 0x04);
		HAL_Delay(100);
*/

		const uint8_t CONFIG[][2] ={
			/*0x01*/	{REG_OP_MOD, RF_OPMODE_FSK | RF_OPMODE_MODULATION_FSK | RF_OPMODE_LFM_OFF | RF_OPMODE_STBY },

			/*0x44*///	{REG_PLL_HOP, 0xAD},	//Frf is validated triggered when RegFrfLsb is written


			/*0x02*/	{REG_BITRATE_MSB, RF_BITRATEMSB_4800 },
			/*0x03*/	{REG_BITRATE_LSB, RF_BITRATELSB_4800 },

			/*0x04*/	{REG_FDEV_MSB, RF_FDEVMSB_5000},
			/*0x05*/	{REG_FDEV_LSB, RF_FDEVLSB_5000},

			/*0x06*/	{REG_FRF_MSB,RF_FRFMSB_868000},
			/*0x07*/	{REG_FRF_MID,RF_FRFMID_868000},
			/*0x08*/	{REG_FRF_LSB,RF_FRFLSB_868000},

			/*0x30*/  	{REG_PACKET_CONFIG_1, RF_PACKET1_FORMAT_FIX | RF_PACKET1_DC_OFF | RF_PACKET1_CRC_ON | RF_PACKET1_CRC_AUTOCLEAR_OFF | RF_PACKET1_ADDR_FILT_OFF | RF_PACKET1_CRC_CCITT},
			/*0x31*/  	{REG_PACKET_CONFIG_2, RF_PACKET2_DATA_MODE_PACKET | RF_PACKET2_IHOME_OFF | RF_PACKET2_BACON_OFF | 0x00},
			/*0x32*/	{REG_PAYLOAD_LENGTH, 0x05},

			/*0x12*/	{REG_RX_BW, RF_RXBW_MANT_16 | RF_RXBW_EXP_2},
			/*0x0A*/	{REG_PA_RAMP, REG_MOD_SHP_NO | RF_PA_R40},

			/*0x3F*/	{REG_IRQ_FLAGS_2, RF_FIFO_OVERRUN},	//clear all interrupts

			/*0x10*/	{REG_RSSI_THRESH, 220},	// must be set to dBm = (-Sensitivity / 2), default is 0xE4 = 228 so -114dBm

			/*0x40*/	{REG_DIO_MAPPING_1, RF_DIO_0_RX_PAYLOADRDY | RF_DIO_1_ALL_FIFOEMPTY | RF_DIO_2_RX_RX_RDY},
			/*0x41*/	{REG_DIO_MAPPING_2, RF_DIO_4_RX_PREAMBLEDETECT | RF_DIO_5_ALL_MODERDY | RF_DIO_PREAMBLE_INT},

			/*0x27*/  	{REG_SYNC_CONFIG, RF_SYNC_AUTO_RESTART_ON_PLL | RF_SYNC_PREAMBLE_0XAA | RF_SYNC_SYNC_ON | RF_SYNC_FIFOFILL_INT | RF_SYNC_SYNC_SIZE_4},
			/*0x28*/	{REG_SYNC_VALUE_1,0xAA},
			/*0x29*/  	{REG_SYNC_VALUE_2,0xAA},
			/*0x2A*/  	{REG_SYNC_VALUE_3,0xAA},
			/*0x2B*/  	{REG_SYNC_VALUE_4,0xAA},
			/*0x2C*/	{REG_SYNC_VALUE_5,0xAA},

			/*0x09*/	{REG_PA_CONFIG,RF_PA_20DBM },
			/*0x25*/	{REG_PREAMBLE_MSB, 0x00},	//preamble size MSB
			/*0x26*/	{REG_PREAMBLE_LSB, 0x03},	//Preamble size LSB

			/*0x36*/	{REG_FIFO_THRESH, RF_FIFOTHRESH_TXSTART_FIFOEMPTY | RF_FIFOTHRESH_FIFO_INT_15},

			/*0x3E*/	{REG_IRQ_FLAGS_1, 0x0A},	//clear all interrupts

			/*0x61*/	{REG_AGC_REF,0x1C},
			/*0x62*/	{REG_AGC_THRESH_1LF,0x0E},
			/*0x63*/	{REG_AGC_THRESH_2LF,0x5B},
			/*0x64*/	{REG_AGC_THRESH_3LF,0xCC},
			/*0x70*/	{REG_PLL_HF,0x70},
			/*0x1A*/	{REG_AFC_FEI, 0x10},

			/*0x01*/	{REG_OP_MOD, 0x02},

			{REG_OOK_PEAK, 0x20},
			{255,0}
		};


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
	while((readReg(REG_IRQ_FLAGS_1) & 0x80) != 0x80);

	writeFIFO(0x00);	//write data to RFM fifo
	setMode(TX);		// set TX Mode
	readGPIO(0);		// wait until packet is sent
	setMode(STANDBY);	// set Standby Mode
	while((readReg(REG_IRQ_FLAGS_1) & 0x80) != 0x80);

}

bool RFM95::isDataReady(void){
	if(currentMode != RX){
		setMode(RX);
	}
	//check if Data in FIFO
	if(HAL_GPIO_ReadPin(gpioHwSettings.gpioPort0, gpioHwSettings.gpioPin0) == GPIO_PIN_SET){
		setMode(STANDBY);
		readFIFO();
		return true;
	}else{
		return false;
	}
}

void RFM95::rfmReceive(void){
	setMode(RX);
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
	uint8_t addr[1] = {0x80 | REG_FIFO};
	uint16_t dataSize = sizeof(data)/sizeof(data[0]);


	uint8_t txData[6] = {0x80,0xAA,0xAA,0xAA,0xAA,0xAA};
	selectRFM();
	HAL_SPI_Transmit(spiHwSettings.hspi, txData, 6, SPI_TIMEOUT);
	deselectRFM();
	return RFM_OK;

/*	if(dataSize > payloadLength){
		return RFM_PAYLOAD_ERROR;
	}else{
		selectRFM();
		HAL_SPI_Transmit(spiHwSettings.hspi, addr, 1, SPI_TIMEOUT);
		HAL_SPI_Transmit(spiHwSettings.hspi, data, dataSize, SPI_TIMEOUT);
		deselectRFM();
		return RFM_OK;
	}*/
}

void RFM95::readFIFO(void){
	uint8_t addr[1] = {REG_FIFO};
	uint8_t rxData[1] = {0};
	selectRFM();
	HAL_SPI_Transmit(spiHwSettings.hspi, addr, 1, SPI_TIMEOUT);
	uint16_t payloadCounter = 0;
	while(HAL_GPIO_ReadPin(gpioHwSettings.gpioPort1, gpioHwSettings.gpioPin1) != GPIO_PIN_SET && payloadCounter<=(payloadLength+1))
	{
		HAL_SPI_Receive(spiHwSettings.hspi, rxData, 1,SPI_TIMEOUT);
		if(!stack.isFull()){
			stack.push(rxData[0]);
		}
		payloadCounter++;
	}
	deselectRFM();
}


void RFM95::setMode(MODE mode){
	if(currentMode != mode){
		switch (mode){
		case RX:
			writeReg(REG_DIO_MAPPING_1, RF_DIO_0_RX_PAYLOADRDY | RF_DIO_1_ALL_FIFOEMPTY | RF_DIO_2_RX_RX_RDY);
			writeReg(REG_PA_CONFIG, RF_PA_00DBM);
			break;
		case TX:
			writeReg(REG_DIO_MAPPING_1, RF_DIO_0_TX_PACKETSENT | RF_DIO_1_ALL_FIFOFULL | RF_DIO_3_TX_TX_RDY);
			//setOutputPower(userOutputPower);
			writeReg(REG_PA_CONFIG, RF_PA_20DBM);
			break;
		default:
			break;
		}
		uint8_t currentMode = readReg(REG_OP_MOD);
		currentMode &= 0xF8;
		currentMode |= mode;
		writeReg(REG_OP_MOD, currentMode);
		HAL_Delay(1);
		if(mode == RX){
			readGPIO(2);
		}else if(mode == TX){
			readGPIO(3);
		}
		HAL_Delay(5);
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


