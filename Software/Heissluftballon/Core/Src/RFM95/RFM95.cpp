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
}

void RFM95::setHardwareOutput(UART_HandleTypeDef *uart, ){

}


void RFM95::initRFM(uint16_t maxPayloadLength, SPI_HW_SETTINGS spiHwSettings, GPIO_HW_SETTINGS gpioHwSettings){

		this->spiHwSettings = spiHwSettings;
		this->gpioHwSettings = gpioHwSettings;
		this->payloadLength = maxPayloadLength;

		if(payloadLength > 1024){
			return 1;	//payload length size too big
		}

	const uint8_t CONFIG[][2] ={
		/*0x01*/	{REG_OP_MOD, RF_OPMODE_FSK | RF_OPMODE_MODULATION_FSK | RF_OPMODE_LFM_OFF | RF_OPMODE_STBY },
		/*0x02*/	{REG_BITRATE_MSB, RF_BITRATEMSB_4800 },
		/*0x03*/	{REG_BITRATE_LSB, RF_BITRATELSB_4800 },
		/*0x04*/	{REG_FDEV_MSB, RF_FDEVMSB_50000},
		/*0x05*/	{REG_FDEV_LSB, RF_FDEVLSB_50000},

		/*0x06*/	{REG_FRF_MSB,RF_FRFMSB_868000},
		/*0x07*/	{REG_FRF_MID,RF_FRFMID_868000},
		/*0x08*/	{REG_FRF_LSB,RF_FRFLSB_868000},

		/*0x09*/	{REG_PA_CONFIG,RF_PA_05DBM },
		/*0x0A*/	{REG_RX_BW, RF_RXBW_MANT_16 | RF_RXBW_EXP_2},

		/*0x10*/	{REG_RSSI_THRESH, 220},	// must be set to dBm = (-Sensitivity / 2), default is 0xE4 = 228 so -114dBm

		/*0x25*/	{REG_PREAMBLE_MSB, 0x00},	//preamble size MSB
		/*0x26*/	{REG_PREAMBLE_LSB, 0x03},	//Preamble size LSB

		/*0x3E*/	{REG_IRQ_FLAGS_1, 0x0A},	//clear all interrupts
		/*0x3F*/	{REG_IRQ_FLAGS_2, 0x11},	//clear all interrupts

		/*0x40*/	{REG_DIO_MAPPING_1, RF_DIO_0_TX_PAYLOADRDY | RF_DIO_1_ALL_FIFOEMPTY | RF_DIO_2_RX_RXRDY},
		/*0x41*/	{REG_DIO_MAPPING_2, RF_DIO_4_RX_PREAMBLEDETECT},

		/*0x27*/  	{REG_SYNC_CONFIG, RF_SYNC_AUTO_RESTART_ON_PLL | RF_SYNC_PREAMBLE_0XAA | RF_SYNC_FIFOFILL_INT | RF_SYNC_SYNC_SIZE_3},
		/*0x28*/	{REG_SYNC_VALUE_1,0x2D},
		/*0x29*/  	{REG_SYNC_VALUE_2,0x2D},
		/*0x2A*/  	{REG_SYNC_VALUE_3,0x2D},

		/*0x30*/  	{REG_PACKET_CONFIG_1, RF_PACKET1_FORMAT_VAR | RF_PACKET1_DC_OFF | RF_PACKET1_CRC_ON | RF_PACKET1_CRC_AUTOCLEAR_ON | RF_PACKET1_ADDR_FILT_OFF | RF_PACKET1_CRC_CCITT},



		/*0x31*/  	{REG_PACKET_CONFIG_2, RF_PACKET2_DATA_MODE_PACKET | RF_PACKET2_IHOME_OFF | RF_PACKET2_BACON_OFF | ((payloadLength>>8) & 0x03)},
		/*0x32*/	{REG_PAYLOAD_LENGTH, (payloadLength&0xFF)},


		/*0x36*/	{REG_FIFO_THRESH, RF_FIFOTHRESH_TXSTART_FIFOEMPTY | 0x1F},


		{255,0}
	};

	deselectRFM();


	//write config array
	  for (uint8_t i = 0; CONFIG[i][0] != 255; i++){
		  writeReg(CONFIG[i][0], CONFIG[i][1]);
	  }
}

/*
 * @brief RFM95 chip select
 *
 * @param none
 * @return none
 */
void RFM95::selectRFM(){
	HAL_GPIO_WritePin(spiHwSettings.gpioPort, spiHwSettings.gpioPin, GPIO_PIN_RESET);
}

/*
 * @brief RFM95 chip deselect
 *
 * @param none
 * @return none
 */
void RFM95::deselectRFM(){
	HAL_GPIO_WritePin(spiHwSettings.gpioPort, spiHwSettings.gpioPin, GPIO_PIN_SET);
}

/*
 * @brief write reg in RFM95
 *
 * @param addr specific register address
 * @param data data to be written
 *
 * @return none
 */
void RFM95::writeReg(uint8_t addr, uint8_t data){
	uint8_t buff[2] = {(addr | 0x80), data};
	selectRFM();
	HAL_SPI_Transmit(spiHwSettings.hspi, buff, 2, SPI_TIMEOUT);
	deselectRFM();
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
	uint8_t *buff = {0};
	selectRFM();
	HAL_SPI_TransmitReceive(spiHwSettings.hspi, &addr, buff, 1, SPI_TIMEOUT);
	deselectRFM();
	return 0;
}


/*
 * @brief write data to RFM95 FIFO
 *
 * @param uint8_t data array
 *
 * @return status successful/not successful (true/false)
 */
bool RFM95::writeFIFO(uint8_t *data){
	uint8_t *addr = {0x80 | REG_FIFO};
	uint16_t dataSize = sizeof(data)/sizeof(data[0]);
	if(dataSize > payloadLength){
		return false;
	}else{
		selectRFM();
		HAL_SPI_Transmit(spiHwSettings.hspi, addr, 1, SPI_TIMEOUT);
		HAL_SPI_Transmit(spiHwSettings.hspi, data, dataSize, SPI_TIMEOUT);
		deselectRFM();
	}
}

void RFM95::readFIFO(void){
	uint8_t *addr = {REG_FIFO};
	uint8_t rxData[1] = {0};
	selectRFM();
	HAL_SPI_Transmit(spiHwSettings.hspi, addr, 1, SPI_TIMEOUT);

	while(!readGPIO(gpioHwSettings.gpioPort1, gpioHwSettings.gpioPin1))
	{
		HAL_SPI_Receive(spiHwSettings.hspi, rxData, 1,SPI_TIMEOUT);
	}

	deselectRFM();

}

void RFM95::setTransmitDirection(RFM_DIR rfmDir){

}

void RFM95::setMode(MODE mode){

}


GPIO_PinState RFM95::readGPIO(GPIO_TypeDef* gpioPort, uint16_t gpioPin ){
	return (HAL_GPIO_ReadPin(gpioPort, gpioPin));
}


