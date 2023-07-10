/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rtc.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "math.h"
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//重定向c库函数printf到串口DEBUG_USART，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
	/* 发送一个字节数据到串口DEBUG_USART */
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);	
	
	return (ch);
}
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
const unsigned char XYDIAN[1024] __attribute__((section(".progmem_data"))) ={
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x79,0xE0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xE0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x67,0x60,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x60,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0xE0,0x00,0x00,0x00,
	0x00,0x01,0xF7,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3D,0xC0,0x00,0x00,0x00,
	0x00,0x03,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x80,0x00,0x00,0x00,
	0x00,0x03,0xBE,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xC6,0x00,0x00,0x00,0x00,
	0x00,0x03,0x08,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xE0,0x00,0x00,0x00,0x00,
	0x00,0x03,0x80,0xE0,0x00,0x00,0x00,0x01,0x83,0x00,0x1F,0x80,0x00,0x00,0x00,0x00,
	0x00,0x03,0x81,0xE0,0x00,0x00,0x00,0x01,0x83,0x00,0x1C,0x60,0x00,0x00,0x00,0x00,
	0x00,0x01,0xC3,0x80,0x00,0x1F,0xFE,0x01,0x87,0xF0,0x18,0xE0,0x00,0x00,0x00,0x00,
	0x00,0x00,0xE7,0x01,0x00,0x1F,0xFE,0x01,0x8F,0xF8,0x18,0x70,0x00,0x00,0x00,0x00,
	0x00,0x00,0xFF,0x0F,0x80,0x0C,0x06,0x01,0xC3,0x18,0x1F,0xFF,0x00,0x00,0x00,0x00,
	0x00,0x00,0x3E,0x1D,0x98,0x0C,0x06,0x07,0xE3,0x1F,0x1F,0xFF,0x00,0x00,0x00,0x00,
	0x00,0x00,0x1C,0x3F,0xFC,0x0C,0x06,0x0F,0x8F,0xFF,0x09,0x3A,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x3F,0xFC,0x0C,0x06,0x0D,0x9F,0xF8,0x03,0xBF,0x80,0x00,0x00,0x00,
	0x00,0x00,0x00,0x7F,0x80,0x0F,0xF6,0x0D,0x83,0x38,0x03,0xBB,0x80,0x00,0x00,0x00,
	0x00,0x00,0x00,0xE1,0x80,0x0F,0xF6,0x01,0x83,0x3C,0x03,0xB9,0xC0,0x00,0x00,0x00,
	0x00,0x00,0x01,0xE1,0xF8,0x0C,0x06,0x01,0x87,0x1E,0x03,0x79,0x80,0x00,0x00,0x00,
	0x00,0x00,0x01,0xDF,0xFC,0x0C,0x06,0x01,0x87,0x0E,0x00,0x70,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x1F,0xF8,0x0C,0x06,0x01,0x8E,0x06,0x00,0x70,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x03,0x80,0x0C,0x06,0x01,0x9C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x03,0x80,0x0F,0xFE,0x00,0x00,0x00,0x3B,0xC0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x03,0x80,0x0F,0xFE,0x00,0x00,0x00,0x7F,0xE0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0xFF,0xFE,0x0C,0x00,0x00,0x00,0x00,0x7F,0x60,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x66,0x60,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0xE0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x79,0xE0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x80,0x00,0x00,0x1F,0xC0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xC0,0x00,0x00,0x07,0x80,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x03,0xFC,0x00,0xF9,0xE0,0x00,0x00,0x01,0x83,0x80,0x00,0x00,0x00,
	0x00,0x00,0x00,0x03,0xFF,0x83,0xE0,0xE0,0x00,0x00,0x00,0x03,0xE0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x07,0x9F,0xE7,0x80,0x70,0x00,0x00,0x3C,0x0F,0xE0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x0F,0x03,0xFF,0x00,0x70,0x00,0x00,0x7F,0xBF,0xE0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x0E,0x00,0xFC,0x00,0x70,0x00,0x00,0x73,0xFC,0xE0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x1E,0x00,0x38,0x00,0x70,0x00,0x00,0x7C,0xF9,0xE0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x1C,0x00,0x00,0x00,0xE0,0x00,0x00,0x1F,0x7D,0xC0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x1C,0x00,0x00,0x01,0xE0,0x00,0x00,0x0F,0xDF,0xC0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x1E,0x00,0x00,0x01,0xC0,0x00,0x00,0x07,0xCF,0xE0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x0F,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0xFB,0xF8,0x00,0x00,0x00,
	0x00,0x00,0x00,0x07,0x80,0x00,0x07,0x80,0x00,0x00,0x01,0xFC,0x7C,0x00,0x00,0x00,
	0x00,0x00,0x00,0x03,0xC0,0x00,0x0F,0x00,0x00,0x00,0x07,0xBF,0x3E,0x00,0x00,0x00,
	0x00,0x00,0x00,0x01,0xF0,0x00,0x1E,0x00,0x00,0x00,0x0F,0xCF,0x0F,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xF8,0x00,0x3C,0x00,0x00,0x00,0x0F,0xF7,0x07,0x80,0x00,0x00,
	0x00,0x00,0x00,0x00,0x7E,0x00,0x38,0x00,0x00,0x00,0x1C,0xFC,0x07,0xC0,0x00,0x00,
	0x00,0x00,0x00,0x00,0x1F,0x80,0x78,0x00,0x00,0x00,0x7C,0x7E,0x01,0xC0,0x00,0x00,
	0x00,0x00,0x00,0x00,0x07,0xC0,0xF0,0x00,0x00,0x00,0x7F,0x9E,0x01,0xC0,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0xE1,0xE0,0x00,0x00,0x00,0x7F,0xCE,0x01,0xC0,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xFB,0xC0,0x00,0x00,0x00,0x3B,0xF0,0x01,0xC0,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x7F,0x80,0x00,0x00,0x00,0x18,0xF8,0x03,0xC0,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x0E,0x3C,0x03,0x80,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x1E,0x00,0x00,0x00,0x00,0x03,0x9C,0x07,0x80,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x01,0xC0,0x07,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x0F,0x00,0x00,0x00};//图像数据

uint8_t xydraw[1024];
	
void LCD_sin(int8_t A,double w,double k);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	memset(xydraw,0x00,1024);
	for(uint8_t i = 0;i<16;i++)*(xydraw+31*16+i)=0xff;
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
		LCD_Init();//液晶初始化
		LCD_Drawing(XYDIAN);
		LCD_sin(15,30,0.1);
		LCD_Drawing(xydraw);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void delay_us(uint32_t us)
{	
	uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * us);
  while (delay--)
	{
		;
	}
}
void LCD_sin(int8_t A,double w,double k) //-15<A<15 w是频率(角度) 128
{
	double temp;
	int Int,Float,x__p,y__p=0,bit_F=0;
	const double pi=acos(-1.0);
	w=w*pi/180;
	for(double i=0;i<128;i++){
		temp=A*sin(w*i*k);
		Int=(int)(temp*10)/10;
		Float=(int)(temp*10)%10;
		if(Float>5)x__p=2+2*Int;else x__p=1+2*Int;
		if(bit_F==8)bit_F=0,y__p++;
		*(xydraw+16*31-16*x__p+y__p)=(*(xydraw+16*31+y__p)&(0x80>>bit_F))|*(xydraw+16*31-16*x__p+y__p);
		delay_us(2);
		bit_F++;
	}
	//xydraw[16*16]
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
