/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/*******引用*******/
#include "w25qxx.h"
#include "oled.h"
#include "bmp.h"
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/*******typedef类型定义*******/

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/*******宏定义*******/

//****************************************
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/*******宏处理*******/
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/*******变量定义*******/

uint8_t Uart1_RxBuff[22] = { 0 };		//接收缓冲
uint8_t Uart1_Rx_Cnt = 0;		//接收缓冲计数

uint8_t ShowData[512] = { 0 };
uint16_t data[5] = { 0 };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/*******函数声明*******/

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	//short read;
	uint8_t startIndex[] = "startlds$";
	uint16_t angle = 0;
	uint8_t x = 0;
	uint8_t y = 0;
	uint16_t distance1 = 0;
	uint16_t distance2 = 0;
	uint16_t distance3 = 0;
	uint16_t distance4 = 0;
	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_SPI1_Init();
	MX_TIM3_Init();
	MX_SPI2_Init();
	MX_USART1_UART_Init();
	MX_I2C1_Init();
	/* USER CODE BEGIN 2 */
	OLED_Init();
//	HAL_UART_Transmit(&huart1, data, 9, 100);
//	HAL_UART_Receive_IT(&huart1, buf, 22);
	HAL_Delay(1000);
	LL_USART_EnableIT_RXNE(USART1);
	LL_USART_EnableIT_PE(USART1);
	HAL_Delay(1000);
	for (int i = 0; i < 9; i++) {
		LL_USART_TransmitData8(USART1, startIndex[i]);
		HAL_Delay(10);
	}

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		while (1) {
			LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13);
			//OLED_DrawBMP(0, 0, 64, 8, BMP0);
			angle = data[0];
			distance1 = data[1] / 65536.0 * 32;
			x = 31 + cos(angle * 3.14 / 180.0) * distance1;
			y = 31 + sin(angle * 3.14 / 180.0) * distance1;
			ShowData[(y / 8) * 64 + x] |= (0x80 >> (y % 8));
			OLED_DrawBMP(0, 0, 64, 8, ShowData);
//			OLED_ShowNum(0, 1, angle);
//			OLED_ShowNum(0, 2, distance1);
//			OLED_ShowNum(0, 3, x);
//			OLED_ShowNum(0, 4, y);
			HAL_Delay(100);
		}
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
	/** Enables the Clock Security System
	 */
	HAL_RCC_EnableCSS();
}

/* USER CODE BEGIN 4 */

//void USART1_IRQHandler(void)
//{
//	uint8_t tmp;
//	if(LL_USART_IsActiveFlag_RXNE(USART1)) //检测是否接收中断
//	{
//		LL_GPIO_ResetOutputPin(GPIOA,LL_GPIO_PIN_5);
//		tmp=LL_USART_ReceiveData8(USART1);   //读取出来接收到的数据
//		LL_USART_TransmitData8(USART6,tmp);  //把数据再从串口发送出去
//	}
//
//}
void USART_RxIdleCallback(void) {
	if (LL_USART_IsActiveFlag_RXNE(USART1)) //检测是否接收中断
			{
		LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_13);
		Uart1_RxBuff[Uart1_Rx_Cnt++] = LL_USART_ReceiveData8(USART1); //读取出来接收到的数据
		if (Uart1_RxBuff[0] != 0xfa) {
			Uart1_Rx_Cnt = 0;
			return;
		}
		if ((Uart1_RxBuff[1] < 0xa0 || Uart1_RxBuff[1] > 0xF9)
				&& Uart1_Rx_Cnt > 1) {
			Uart1_Rx_Cnt = 0;
			return;
		}
		if (Uart1_Rx_Cnt < 22)  //溢出判断
				{
			return;
		} else {
			data[0] = (uint16_t) (Uart1_RxBuff[1] & 0x00ff) - 0x009f;
			data[1] = Uart1_RxBuff[5] + ((Uart1_RxBuff[6]& 0x3F) << 8);
			data[2] = Uart1_RxBuff[9] + ((Uart1_RxBuff[10]& 0x3F) << 8);
			data[3] = Uart1_RxBuff[13] + ((Uart1_RxBuff[14]& 0x3F) << 8);
			data[4] = Uart1_RxBuff[17] + ((Uart1_RxBuff[15]& 0x3F) << 8);
			Uart1_Rx_Cnt = 0;
		}

	}
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
