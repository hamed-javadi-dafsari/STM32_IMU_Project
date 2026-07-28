/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
#include <stdio.h>
#include <string.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
char msg[150];


uint8_t icm_ok=0;
uint8_t qmc_ok=0;
uint8_t bmp_ok=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */
void I2C_Scan(void);


void ICM42688_Init(void);
void ICM42688_Read(void);


void QMC5883P_Init(void);
void QMC5883P_Read(void);


void BMP388_Init(void);
void BMP388_Read(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define ICM42688_ADDR (0x69<<1)

#define QMC5883P_ADDR (0x2C<<1)

#define BMP388_ADDR   (0x77<<1)
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

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(100);


  I2C_Scan();


  ICM42688_Init();


  QMC5883P_Init();


  BMP388_Init();




















  while(1)
  {




    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  ICM42688_Read();


	  QMC5883P_Read();


	  BMP388_Read();


	  HAL_Delay(200);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

//****************************ICM Read***********************
void ICM42688_Read(void)
{

if(!icm_ok)
return;



uint8_t reg=0x1F;

uint8_t data[12];



HAL_I2C_Master_Transmit(
&hi2c1,
ICM42688_ADDR,
&reg,
1,
1000);



HAL_I2C_Master_Receive(
&hi2c1,
ICM42688_ADDR,
data,
12,
1000);



int16_t ax =
(data[0]<<8)|data[1];


int16_t ay =
(data[2]<<8)|data[3];


int16_t az =
(data[4]<<8)|data[5];


int16_t gx =
(data[6]<<8)|data[7];


int16_t gy =
(data[8]<<8)|data[9];


int16_t gz =
(data[10]<<8)|data[11];



sprintf(msg,
"ICM ACC X:%d Y:%d Z:%d | GYRO X:%d Y:%d Z:%d\r\n",
ax,ay,az,
gx,gy,gz);



HAL_UART_Transmit(
&huart2,
(uint8_t*)msg,
strlen(msg),
1000);


}

//****************************QMC Read***********************
void QMC5883P_Read(void)
{


if(!qmc_ok)
return;


uint8_t data[6];


HAL_I2C_Mem_Read(
&hi2c1,
QMC5883P_ADDR,
0x01,
I2C_MEMADD_SIZE_8BIT,
data,
6,
1000);



int16_t x=
(int16_t)(data[0]|data[1]<<8);


int16_t y=
(int16_t)(data[2]|data[3]<<8);


int16_t z=
(int16_t)(data[4]|data[5]<<8);



sprintf(msg,
"MAG X:%d Y:%d Z:%d\r\n",
x,y,z);



HAL_UART_Transmit(
&huart2,
(uint8_t*)msg,
strlen(msg),
1000);


}

//****************************BMP388 Read***********************
void BMP388_Read(void)
{

if(!bmp_ok)
return;



uint8_t data[6];


HAL_I2C_Mem_Read(
&hi2c1,
BMP388_ADDR,
0x04,
I2C_MEMADD_SIZE_8BIT,
data,
6,
1000);



uint32_t p=
(data[2]<<16)|
(data[1]<<8)|
data[0];



uint32_t t=
(data[5]<<16)|
(data[4]<<8)|
data[3];



sprintf(msg,
"BMP388 P:%lu T:%lu\r\n",
p,t);



HAL_UART_Transmit(
&huart2,
(uint8_t*)msg,
strlen(msg),
1000);


}

//****************************I2C Scan***********************************
void I2C_Scan(void)
{

uint8_t addr;


sprintf(msg,"\r\nI2C SCAN\r\n");


HAL_UART_Transmit(
&huart2,
(uint8_t*)msg,
strlen(msg),
1000);



for(addr=1; addr<127; addr++)
{

if(HAL_I2C_IsDeviceReady(
&hi2c1,
addr<<1,
3,
100)==HAL_OK)
{

sprintf(msg,"FOUND 0x%02X\r\n",addr);


HAL_UART_Transmit(
&huart2,
(uint8_t*)msg,
strlen(msg),
1000);

}

}

HAL_Delay(100);

}





//================ ICM-42688-P INIT =================

void ICM42688_Init(void)
{


uint8_t init[2];


init[0]=0x4E;
init[1]=0x0F;



if(HAL_I2C_Master_Transmit(
&hi2c1,
ICM42688_ADDR,
init,
2,
1000)==HAL_OK)
{


icm_ok=1;


sprintf(msg,"ICM42688 OK\r\n");


HAL_UART_Transmit(
&huart2,
(uint8_t*)msg,
strlen(msg),
1000);


}


}


//================ QMC5883P INIT =================
void QMC5883P_Init(void)
{

uint8_t data;


if(HAL_I2C_IsDeviceReady(
&hi2c1,
QMC5883P_ADDR,
3,
100)==HAL_OK)
{


qmc_ok=1;


data=0xCF;

HAL_I2C_Mem_Write(
&hi2c1,
QMC5883P_ADDR,
0x0A,
I2C_MEMADD_SIZE_8BIT,
&data,
1,
1000);



data=0x08;


HAL_I2C_Mem_Write(
&hi2c1,
QMC5883P_ADDR,
0x0B,
I2C_MEMADD_SIZE_8BIT,
&data,
1,
1000);



sprintf(msg,"QMC5883P OK\r\n");


HAL_UART_Transmit(
&huart2,
(uint8_t*)msg,
strlen(msg),
1000);


}

}



//================ BMP388 INIT =================
void BMP388_Init(void)
{

uint8_t id;


HAL_I2C_Mem_Read(
&hi2c1,
BMP388_ADDR,
0x00,
I2C_MEMADD_SIZE_8BIT,
&id,
1,
1000);



if(id==0x50)
{

bmp_ok=1;


sprintf(msg,"BMP388 OK ID=0x50\r\n");


HAL_UART_Transmit(
&huart2,
(uint8_t*)msg,
strlen(msg),
1000);



uint8_t cfg[2];


cfg[0]=0x1B;
cfg[1]=0x33;


HAL_I2C_Master_Transmit(
&hi2c1,
BMP388_ADDR,
cfg,
2,
1000);



}

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
#ifdef USE_FULL_ASSERT
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
