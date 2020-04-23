/*
 * RFM95LoRa.h
 *
 *  Created on: 23.04.2020
 *      Author: marce
 */
#include "stm32l4xx_hal.h"
#include "main.h"
#include "spi.h"
#include "gpio.h"


#ifndef SRC_RFM95_LORA_RFM95LORA_H_
#define SRC_RFM95_LORA_RFM95LORA_H_


// registers
#define REG_FIFO                 0x00
#define REG_OP_MODE              0x01
#define REG_FRF_MSB              0x06
#define REG_FRF_MID              0x07
#define REG_FRF_LSB              0x08
#define REG_PA_CONFIG            0x09
#define REG_LNA                  0x0c
#define REG_FIFO_ADDR_PTR        0x0d
#define REG_FIFO_TX_BASE_ADDR    0x0e
#define REG_FIFO_RX_BASE_ADDR    0x0f
#define REG_FIFO_RX_CURRENT_ADDR 0x10
#define REG_IRQ_FLAGS            0x12
#define REG_RX_NB_BYTES          0x13
#define REG_PKT_SNR_VALUE        0x19
#define REG_PKT_RSSI_VALUE       0x1a
#define REG_MODEM_CONFIG_1       0x1d
#define REG_MODEM_CONFIG_2       0x1e
#define REG_PREAMBLE_MSB         0x20
#define REG_PREAMBLE_LSB         0x21
#define REG_PAYLOAD_LENGTH       0x22
#define REG_MODEM_CONFIG_3       0x26
#define REG_RSSI_WIDEBAND        0x2c
#define REG_DETECTION_OPTIMIZE   0x31
#define REG_DETECTION_THRESHOLD  0x37
#define REG_SYNC_WORD            0x39
#define REG_DIO_MAPPING_1        0x40
#define REG_VERSION              0x42


// modes
#define MODE_LONG_RANGE_MODE     0x80
#define MODE_SLEEP               0x00
#define MODE_STDBY               0x01
#define MODE_TX                  0x03
#define MODE_RX_CONTINUOUS       0x05
#define MODE_RX_SINGLE           0x06


// PA config
#define PA_BOOST                 0x80


// IRQ masks
#define IRQ_TX_DONE_MASK           0x08
#define IRQ_PAYLOAD_CRC_ERROR_MASK 0x20
#define IRQ_RX_DONE_MASK           0x40


#define MAX_PKT_LENGTH           255

#define PA_OUTPUT_RFO_PIN      0
#define PA_OUTPUT_PA_BOOST_PIN 1



class RFM95_LoRa {

public:

	RFM95_LoRa();

  int begin(long frequency);
  void end();

  int beginPacket(int implicitHeader = false);
  int endPacket();

  int parsePacket(int size = 0);
  int packetRssi();
  float packetSnr();

  // from Print
  virtual size_t write(uint8_t byte);
  virtual size_t write(const uint8_t *buffer, size_t size);

  // from Stream
  virtual int available();
  virtual int read();
  virtual int peek();
 // virtual void flush();

  void onReceive(void(*callback)(int));
  void receive(int size = 0);
  void idle();
  void sleep();
  void setTxPower(int level, int outputPin = PA_OUTPUT_PA_BOOST_PIN);
  void setFrequency(long frequency);
  void setSpreadingFactor(int sf);
  void setSignalBandwidth(long sbw);
  void setCodingRate4(int denominator);
  void setPreambleLength(long length);
  void setSyncWord(int sw);
  void enableCrc();
  void disableCrc();

  // deprecated
  void crc() { enableCrc(); }
  void noCrc() { disableCrc(); }
  uint8_t random();


private:
  void explicitHeaderMode();
  void implicitHeaderMode();
  void handleDio0Rise();

  uint8_t singleTransfer(uint8_t address, uint8_t value);
  static void onDio0Rise();



  void resetRFM(void);
  uint8_t readRegister(uint8_t addr);
  bool writeRegister(uint8_t addr, uint8_t data);

  void deselectRFM(void);
  void selectRFM(void);
private:

  int _ss;
  int _reset;
  int _dio0;
  int _frequency;
  int _packetIndex;
  int _implicitHeaderMode;
  void (*_onReceive)(int);

};



#endif /* SRC_RFM95_LORA_RFM95LORA_H_ */
