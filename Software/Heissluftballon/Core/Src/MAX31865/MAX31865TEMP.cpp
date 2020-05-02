/*
 * MAX31865TEMP.cpp
 *
 *  Created on: Apr 17, 2020
 *      Author: marce
 */

#include "MAX31865TEMP.h"

HAL_StatusTypeDef def;

MAX31865_TEMP::MAX31865_TEMP(Model *model) {
	// TODO Auto-generated constructor stub
	this->model = model;
}

void MAX31865_TEMP::init(uint8_t wires){
	uint8_t buff[1];
 HAL_Delay(100);
  setWires(wires);           // Set 2,3 or 4 wire sensor
  HAL_Delay(100);
  enableBias(OFF);           // Disable bias voltage
  HAL_Delay(100);
  autoConvert(OFF);          // Disable auto conversion
  HAL_Delay(100);

}


bool MAX31865_TEMP::readTemp(){

	uint8_t error;
	uint8_t buff[1];
	MAX31865_read(0x07, buff, 1);

    // Activate bias voltage to read sensor data, and wait for the capacitors to fill
    enableBias(ON);
    HAL_Delay(20);
    // Perform a single conversion, and wait for the result
    single_shot();
    HAL_Delay(100);
    // Read data from max31865 data registers
    uint8_t buffer[2];
     MAX31865_read(MAX31856_RTDMSB_REG, buffer,2);
    // Combine 2 bytes into 1 number, and shift 1 down to remove fault bit
    uint16_t data = buffer[0] << 8;
    data |= buffer[1];
  //  data <<= 1;
    // Disable bias voltage to reduce power usage
    enableBias(OFF);


    // Calculate the actual resistance of the sensor
    float resistance = ((float) data * RREF) / FACTOR;
    // Calculate the temperature from the measured resistance
    float temp = ((resistance / 100) - 1) / ALPHA;



	model->setTempInside(data);
	return true;
}



/**
 * Read x bytes from MAX31865 starting from addr
 *
 * @param addr      Register addr to read from
 * @param buffer    Pointer to rx buffer
 * @param len       Amount of bytes to read
 */
void MAX31865_TEMP::MAX31865_read(uint8_t addr, uint8_t *buffer, uint8_t size)
{
	HAL_StatusTypeDef test;
	uint8_t txBuffer[1];
    addr &= ~MAX31865_READ;                             		// Force read bit on address
    txBuffer[0] = addr;
    CLEAR_MAX_CS;          										// Enable CE
    test = HAL_SPI_Transmit(&hspi1,(uint8_t*)txBuffer,1,500);	//write addr
    test =HAL_SPI_Receive(&hspi1,(uint8_t*)buffer,size,500);	// Read data
    SET_MAX_CS;          										// Disable CE
}

/**
 * Write a byte in a MAX13865 register
 *
 * @param addr      Register addr to write to
 * @param buffer    Tx data
 */
void MAX31865_TEMP::MAX31865_write(uint8_t addr, uint8_t data){
	HAL_StatusTypeDef test;

	uint8_t txBuffer[2];

	addr |= MAX31865_WRITE;                             // Force write bit on address
    txBuffer[0] = addr;
    txBuffer[1] = data;
    CLEAR_MAX_CS; 									    // Enable CE
    test = HAL_SPI_Transmit(&hspi1,(uint8_t*)txBuffer,2,500);				//write addr

    SET_MAX_CS;          								// Disable CE
    HAL_Delay(10);
}




/**
 * Enable of disable MAX831865 bias voltage
 * @param enable Enable of disable
 */
void MAX31865_TEMP::enableBias(uint8_t enable)
{
    uint8_t status;
    /*MAX31865_read(MAX31856_CONFIG_REG, &status,1);
    if (enable)
    {
        status |= MAX31856_CONFIG_BIAS;
    } else
    {
        status &= ~MAX31856_CONFIG_BIAS;
    }*/
    status = 0x80;
    MAX31865_write(MAX31856_CONFIG_REG, status);
}



/**
 * Enable of disable MAX831865 auto convert
 * @param enable Enable of disable
 */
void MAX31865_TEMP::autoConvert(uint8_t enable)
{
    uint8_t status;
    MAX31865_read(MAX31856_CONFIG_REG, &status,1);
    if (enable)
    {
        status |= MAX31856_CONFIG_MODEAUTO;
    } else
    {
        status &= ~MAX31856_CONFIG_MODEAUTO;
    }
    MAX31865_write(MAX31856_CONFIG_REG, status);
}



/**
 * Set the amount of wires the temperature sensor uses
 * @param numwires 2,3 or 4 wires
 */
void MAX31865_TEMP::setWires(uint8_t numwires)
{
    uint8_t status;
    MAX31865_read(MAX31856_CONFIG_REG, &status,1);
    if (numwires == 3) // 3-wire
    {
        status |= MAX31856_CONFIG_3WIRE;
    } else // 2-4 wire
    {
        status &= ~MAX31856_CONFIG_3WIRE;
    }
    MAX31865_write(MAX31856_CONFIG_REG, status);
}



/**
 * Perform a single shot conversion
 */
void MAX31865_TEMP::single_shot(void)
{
    uint8_t status;
    // Read config register
   // MAX31865_read(MAX31856_CONFIG_REG, &status,1);
    // Enable 1shot bit, and write back
    //status = MAX31856_CONFIG_1SHOT;
    status = 0xA0;
    MAX31865_write(MAX31856_CONFIG_REG, status);
}






