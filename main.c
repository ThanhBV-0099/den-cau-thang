/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint16_t counter=0,counter1=0,lap,nutnhan;
volatile uint64_t time_set=5000,time=5000,time_change;
volatile uint16_t phathien1=0;
volatile uint16_t phathien2=0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define pin_set 1
#define pin_reset 0
#define out_pin4(x) HAL_GPIO_WritePin (GPIOA, GPIO_PIN_4, x);
#define out_led(x) HAL_GPIO_WritePin (GPIOC, GPIO_PIN_13, x);
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
void doccb(void);
void set_time();
void sangden();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void doccb(void)
{
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0)
	{
		HAL_Delay(2);
	//while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0);
	{
		phathien1=1;
	}
}
	
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)==0)
	{
		HAL_Delay(2);
	//while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)==0);
	{
		phathien2=1;
	}
}
	}

void sangden()
{
	counter++;
	HAL_Delay(1);
	if(counter<time_set) // tre tat den
	{
		if(phathien1==1 || phathien2==1)
	{
		counter=0;
		out_pin4(1);
		phathien1=0;
		phathien2=0;
		nutnhan=0;
}
	if(nutnhan==1)
	{
			counter=0;	
	}
	}

	else if ((counter > time_set) && nutnhan==0)
	{
		counter=0;
		out_pin4(0);
	}

}


	void set_time()
	{
		if(counter<time_set )
		{
		if(time_change==0)
		{
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0 ) 
		{ 
		counter1=0;
		lap=0;
		do
		{
		counter1++;
		HAL_Delay(2);
		}
		while ((counter1<1200) && HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0);
		{
			if(counter1==1200) // giu khoang 5s
			{
			counter1=1200;
			time_change=1;
			for(lap=0;lap<10;lap++)
			{
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
			HAL_Delay(100);
			}
			counter1=0;
		 while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0); 
		}
		else
		{
		nutnhan=1;	
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);	
		HAL_Delay(2);
		counter=0;
		}			
	}
}	
		}
		
		else if(time_change==1)
		{
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0 ) 
		{ 
		counter1=0;
		lap=0;
		do
		{
		counter1++;
		HAL_Delay(2);
		}
		while ((counter1<1200) && HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0);
		{
			if(counter1==1200) // giu khoang 5s
			{
			counter1=1200;
			time_set=time;
			for(lap=0;lap<10;lap++)
			{
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
			HAL_Delay(50);
			}
			counter1=0;
			time_change=0;
		 while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0); 
		}
			else
		{
		time+=5000;
		if(time>30000)
		{
		time=5000;
		}	
		}
		}
			}
			
		}
		}
	}
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
  /* USER CODE BEGIN 2 */
out_pin4(0);
out_led(0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		doccb();
		sangden();
		set_time();
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
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
