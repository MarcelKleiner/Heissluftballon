/*
 * IOConfig.h
 *
 *  Created on: Apr 10, 2020
 *      Author: marce
 */

#ifndef SRC_CONFIG_IOCONFIG_H_
#define SRC_CONFIG_IOCONFIG_H_


/*general definition*/
#define WRITE_LED				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET)
#define CLEAR_LED				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET)


/*RFM95 Transceiver definition*/
#define	READ_RFMDIO0			HAL_GPIO_ReadPin(RFM_DIO0_GPIO_Port, RFM_DIO0_Pin)
#define	READ_RFMDIO1			HAL_GPIO_ReadPin(RFM_DIO1_GPIO_Port, RFM_DIO1_Pin)
#define	READ_RFMDIO2			HAL_GPIO_ReadPin(RFM_DIO2_GPIO_Port, RFM_DIO2_Pin)
#define	READ_RFMDIO3			HAL_GPIO_ReadPin(RFM_DIO3_GPIO_Port, RFM_DIO3_Pin)
#define	READ_RFMDIO4			HAL_GPIO_ReadPin(RFM_DIO4_GPIO_Port, RFM_DIO4_Pin)
#define	READ_RFMDIO5			HAL_GPIO_ReadPin(RFM_DIO5_GPIO_Port, RFM_DIO5_Pin)

#define SEL_RFM					HAL_GPIO_WritePin(RFM_NSS_GPIO_Port, RFM_NSS_Pin, GPIO_PIN_RESET)
#define DESEL_RFM				HAL_GPIO_WritePin(RFM_NSS_GPIO_Port, RFM_NSS_Pin, GPIO_PIN_SET)

#define WRITE_RST_RFM			HAL_GPIO_WritePin(RFM_RST_GPIO_Port, RFM_RST_Pin, GPIO_PIN_SET)
#define CLEAR_RST_RFM			HAL_GPIO_WritePin(RFM_RST_GPIO_Port, RFM_RST_Pin, GPIO_PIN_RESET)

/*MAX31865 PT1000 RTD to Digital definition*/
#define SEL_MAX					HAL_GPIO_WritePin(MAX_CS_GPIO_Port, MAX_CS_Pin, GPIO_PIN_RESET)
#define DESEL_MAX				HAL_GPIO_WritePin(MAX_CS_GPIO_Port, MAX_CS_Pin, GPIO_PIN_SET)

#define WRITE_MAX_DRDY			HAL_GPIO_WritePin(MAX_DRDY_GPIO_Port, MAX_DRDY_Pin, GPIO_PIN_SET)
#define CLEAR_MAX_DRDY			HAL_GPIO_WritePin(MAX_DRDY_GPIO_Port, MAX_DRDY_Pin, GPIO_PIN_RESET)

#endif /* SRC_CONFIG_IOCONFIG_H_ */
