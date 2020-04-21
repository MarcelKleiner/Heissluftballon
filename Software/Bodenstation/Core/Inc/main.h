/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RFM_DIO2_Pin GPIO_PIN_14
#define RFM_DIO2_GPIO_Port GPIOC
#define RFM_DIO1_Pin GPIO_PIN_15
#define RFM_DIO1_GPIO_Port GPIOC
#define NC_Pin GPIO_PIN_0
#define NC_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_1
#define LED_GPIO_Port GPIOA
#define PRESSURE_INT_Pin GPIO_PIN_4
#define PRESSURE_INT_GPIO_Port GPIOA
#define MAX_CS_Pin GPIO_PIN_0
#define MAX_CS_GPIO_Port GPIOB
#define MAX_DRDY_Pin GPIO_PIN_1
#define MAX_DRDY_GPIO_Port GPIOB
#define NCA8_Pin GPIO_PIN_8
#define NCA8_GPIO_Port GPIOA
#define RFM_NSS_Pin GPIO_PIN_15
#define RFM_NSS_GPIO_Port GPIOA
#define RFM_RST_Pin GPIO_PIN_3
#define RFM_RST_GPIO_Port GPIOB
#define RFM_DIO5_Pin GPIO_PIN_4
#define RFM_DIO5_GPIO_Port GPIOB
#define RFM_DIO3_Pin GPIO_PIN_5
#define RFM_DIO3_GPIO_Port GPIOB
#define RFM_DIO4_Pin GPIO_PIN_6
#define RFM_DIO4_GPIO_Port GPIOB
#define RFM_DIO0_Pin GPIO_PIN_7
#define RFM_DIO0_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
