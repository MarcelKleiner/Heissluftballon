/*
 * RFM95LoRa.cpp
 *
 *  Created on: 23.04.2020
 *      Author: marce
 */

#include "RFM95LoRa.h"
#include "../../AppMain/AppMain.h"

RFM95_LoRa::RFM95_LoRa() :
  _frequency(0),
  _packetIndex(0),
  _implicitHeaderMode(0),
  _onReceive(0)
{

}



/*
 * @brief RFM95 chip select
 *
 * @param none
 * @return none
 */
void RFM95_LoRa::selectRFM(){
	HAL_GPIO_WritePin(RFM_NSS_GPIO_Port,RFM_NSS_Pin, GPIO_PIN_RESET);
}

/*
 * @brief RFM95 chip deselect
 *
 * @param none
 * @return none
 */
void RFM95_LoRa::deselectRFM(){
	HAL_GPIO_WritePin(RFM_NSS_GPIO_Port,RFM_NSS_Pin, GPIO_PIN_SET);
}

void RFM95_LoRa::resetRFM(){
	HAL_GPIO_WritePin(RFM_RST_GPIO_Port, RFM_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(RFM_RST_GPIO_Port, RFM_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(5);
}

bool RFM95_LoRa::writeRegister(uint8_t addr, uint8_t data){
	uint8_t buff[2] = {(uint8_t)(addr | 0x80), data};
	selectRFM();
	if(HAL_SPI_Transmit(&hspi1, (uint8_t*)buff, 2, 100) != HAL_OK){
		deselectRFM();
		return false;
	}
	deselectRFM();
	return true;
}

uint8_t RFM95_LoRa::readRegister(uint8_t addr){
	uint8_t rxData[2] = {0,0};
	uint8_t txData[1] = {addr};

	selectRFM();
		HAL_SPI_TransmitReceive(&hspi1,(uint8_t*)txData,(uint8_t*)rxData,2,100);
	deselectRFM();
	return rxData[1];
}


int RFM95_LoRa::begin(long frequency){
 resetRFM();
  // check version
  uint8_t version = readRegister(REG_VERSION);
  if (version != 0x12) {
    return 0;
  }
  // put in sleep mode
  sleep();
  // set frequency
  setFrequency(frequency);
  // set base addresses
  writeRegister(REG_FIFO_TX_BASE_ADDR, 0);
  writeRegister(REG_FIFO_RX_BASE_ADDR, 0);
  // set LNA boost
  writeRegister(REG_LNA, readRegister(REG_LNA) | 0x03);
  // set auto AGC
  writeRegister(REG_MODEM_CONFIG_3, 0x04);
  // set output power to 17 dBm
  setTxPower(20);
  // put in standby mode
  idle();
  return 1;
}



void RFM95_LoRa::end(){
  // put in sleep mode
  sleep();
}



int RFM95_LoRa::beginPacket(int implicitHeader){
  // put in standby mode
  idle();

  if (implicitHeader) {
    implicitHeaderMode();
  } else {
    explicitHeaderMode();
  }

  // reset FIFO address and paload length
  writeRegister(REG_FIFO_ADDR_PTR, 0);
  writeRegister(REG_PAYLOAD_LENGTH, 0);
  return 1;
}



int RFM95_LoRa::endPacket(){
  // put in TX mode
  writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_TX);
  // wait for TX done
  while ((readRegister(REG_IRQ_FLAGS) & IRQ_TX_DONE_MASK) == 0) {

  }
  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  // clear IRQ's
  writeRegister(REG_IRQ_FLAGS, IRQ_TX_DONE_MASK);
  return 1;
}



int RFM95_LoRa::parsePacket(int size)

{
  int packetLength = 0;
  int irqFlags = readRegister(REG_IRQ_FLAGS);
  if (size > 0) {
    implicitHeaderMode();
    writeRegister(REG_PAYLOAD_LENGTH, size & 0xff);
  } else {
    explicitHeaderMode();
  }

  // clear IRQ's
  writeRegister(REG_IRQ_FLAGS, irqFlags);
  if ((irqFlags & IRQ_RX_DONE_MASK) && (irqFlags & IRQ_PAYLOAD_CRC_ERROR_MASK) == 0) {
    // received a packet
    _packetIndex = 0;
    // read packet length
    if (_implicitHeaderMode) {
      packetLength = readRegister(REG_PAYLOAD_LENGTH);
    } else {
      packetLength = readRegister(REG_RX_NB_BYTES);
    }
    // set FIFO address to current RX address
    writeRegister(REG_FIFO_ADDR_PTR, readRegister(REG_FIFO_RX_CURRENT_ADDR));
    // put in standby mode
    idle();
  } else if (readRegister(REG_OP_MODE) != (MODE_LONG_RANGE_MODE | MODE_RX_SINGLE)) {
    // not currently in RX mode
    // reset FIFO address
    writeRegister(REG_FIFO_ADDR_PTR, 0);
    // put in single RX mode
    writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_RX_SINGLE);
  }
  return packetLength;
}


int RFM95_LoRa::packetRssi(){
  return (readRegister(REG_PKT_RSSI_VALUE) - (_frequency < 868E6 ? 164 : 157));
}


float RFM95_LoRa::packetSnr(){
  return ((int8_t)readRegister(REG_PKT_SNR_VALUE)) * 0.25;
}

size_t RFM95_LoRa::write(uint8_t byte){
  return write(&byte, sizeof(byte));
}



size_t RFM95_LoRa::write(const uint8_t *buffer, size_t size){
  int currentLength = readRegister(REG_PAYLOAD_LENGTH);
  // check size
  if ((currentLength + size) > MAX_PKT_LENGTH) {
    size = MAX_PKT_LENGTH - currentLength;
  }
  // write data
  for (size_t i = 0; i < size; i++) {
    writeRegister(REG_FIFO, buffer[i]);
  }

  // update length
  writeRegister(REG_PAYLOAD_LENGTH, currentLength + size);
  return size;
}


int RFM95_LoRa::available()
{
  return (readRegister(REG_RX_NB_BYTES) - _packetIndex);
}



int RFM95_LoRa::read(){
  if (!available()) {
    return -1;
  }
  _packetIndex++;
  return readRegister(REG_FIFO);
}



int RFM95_LoRa::peek(){
  if (!available()) {
    return -1;
  }
  // store current FIFO address
  int currentAddress = readRegister(REG_FIFO_ADDR_PTR);
  // read
  uint8_t b = readRegister(REG_FIFO);
  // restore FIFO address
  writeRegister(REG_FIFO_ADDR_PTR, currentAddress);
  return b;
}


void RFM95_LoRa::receive(int size){
  if (size > 0) {
    implicitHeaderMode();
    writeRegister(REG_PAYLOAD_LENGTH, size & 0xff);
  } else {
    explicitHeaderMode();
  }
  writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_RX_CONTINUOUS);
}

void RFM95_LoRa::idle(){
  writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_STDBY);
}

void RFM95_LoRa::sleep(){
  writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_SLEEP);
}



void RFM95_LoRa::setTxPower(int level, int outputPin){
  if (PA_OUTPUT_RFO_PIN == outputPin) {
    // RFO
    if (level < 0) {
      level = 0;
    } else if (level > 14) {
      level = 14;
    }
    writeRegister(REG_PA_CONFIG, 0x70 | level);
  } else {
    // PA BOOST
    if (level < 2) {
      level = 2;
    } else if (level > 17) {
      level = 17;
    }
    writeRegister(REG_PA_CONFIG, PA_BOOST | (level - 2));
  }
}



void RFM95_LoRa::setFrequency(long frequency){
  _frequency = frequency;
  uint64_t frf = ((uint64_t)frequency << 19) / 32000000;
  writeRegister(REG_FRF_MSB, (uint8_t)(frf >> 16));
  writeRegister(REG_FRF_MID, (uint8_t)(frf >> 8));
  writeRegister(REG_FRF_LSB, (uint8_t)(frf >> 0));
}



void RFM95_LoRa::setSpreadingFactor(int sf){
  if (sf < 6) {
    sf = 6;
  } else if (sf > 12) {
    sf = 12;
  }

  if (sf == 6) {
    writeRegister(REG_DETECTION_OPTIMIZE, 0xc5);
    writeRegister(REG_DETECTION_THRESHOLD, 0x0c);
  } else {
    writeRegister(REG_DETECTION_OPTIMIZE, 0xc3);
    writeRegister(REG_DETECTION_THRESHOLD, 0x0a);
  }
  writeRegister(REG_MODEM_CONFIG_2, (readRegister(REG_MODEM_CONFIG_2) & 0x0f) | ((sf << 4) & 0xf0));
}


void RFM95_LoRa::setSignalBandwidth(long sbw){
  int bw;
  if (sbw <= 7.8E3) {
    bw = 0;
  } else if (sbw <= 10.4E3) {
    bw = 1;
  } else if (sbw <= 15.6E3) {
    bw = 2;
  } else if (sbw <= 20.8E3) {
    bw = 3;
  } else if (sbw <= 31.25E3) {
    bw = 4;
  } else if (sbw <= 41.7E3) {
    bw = 5;
  } else if (sbw <= 62.5E3) {
    bw = 6;
  } else if (sbw <= 125E3) {
    bw = 7;
  } else if (sbw <= 250E3) {
    bw = 8;
  } else /*if (sbw <= 250E3)*/ {
    bw = 9;
  }

  writeRegister(REG_MODEM_CONFIG_1, (readRegister(REG_MODEM_CONFIG_1) & 0x0f) | (bw << 4));
}



void RFM95_LoRa::setCodingRate4(int denominator){
  if (denominator < 5) {
    denominator = 5;
  } else if (denominator > 8) {
	  denominator = 8;
  }
  int cr = denominator - 4;
  writeRegister(REG_MODEM_CONFIG_1, (readRegister(REG_MODEM_CONFIG_1) & 0xf1) | (cr << 1));
}

void RFM95_LoRa::setPreambleLength(long length){
  writeRegister(REG_PREAMBLE_MSB, (uint8_t)(length >> 8));
  writeRegister(REG_PREAMBLE_LSB, (uint8_t)(length >> 0));
}


void RFM95_LoRa::setSyncWord(int sw){
  writeRegister(REG_SYNC_WORD, sw);
}


void RFM95_LoRa::enableCrc(){
  writeRegister(REG_MODEM_CONFIG_2, readRegister(REG_MODEM_CONFIG_2) | 0x04);
}


void RFM95_LoRa::disableCrc(){
  writeRegister(REG_MODEM_CONFIG_2, readRegister(REG_MODEM_CONFIG_2) & 0xfb);
}


uint8_t RFM95_LoRa::random(){
  return readRegister(REG_RSSI_WIDEBAND);
}


void RFM95_LoRa::explicitHeaderMode(){
  _implicitHeaderMode = 0;
  writeRegister(REG_MODEM_CONFIG_1, readRegister(REG_MODEM_CONFIG_1) & 0xfe);
}


void RFM95_LoRa::implicitHeaderMode(){
  _implicitHeaderMode = 1;
  writeRegister(REG_MODEM_CONFIG_1, readRegister(REG_MODEM_CONFIG_1) | 0x01);
}



void RFM95_LoRa::handleDio0Rise(){
  int irqFlags = readRegister(REG_IRQ_FLAGS);
  // clear IRQ's
  writeRegister(REG_IRQ_FLAGS, irqFlags);

  if ((irqFlags & IRQ_PAYLOAD_CRC_ERROR_MASK) == 0) {
    // received a packet
    _packetIndex = 0;
    // read packet length
    int packetLength = _implicitHeaderMode ? readRegister(REG_PAYLOAD_LENGTH) : readRegister(REG_RX_NB_BYTES);
    // set FIFO address to current RX address
    writeRegister(REG_FIFO_ADDR_PTR, readRegister(REG_FIFO_RX_CURRENT_ADDR));
    if (_onReceive) {
      _onReceive(packetLength);
    }
    // reset FIFO address
    writeRegister(REG_FIFO_ADDR_PTR, 0);
  }
}



