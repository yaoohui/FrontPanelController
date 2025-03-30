/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

#include "io.h"
#include "stdio.h"
#include "string.h"
#include "commandprocess.h"
#include "fingerprint.h"
#include "lcd_st7789v.h"
#include "touch_CST816D.h"
#include "lvgl.h"
#include "lv_conf.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
//#include "ui.h"
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "eeprom_24c02.h"
#include "usbd_cdc_if.h"

/*############################################################################*/

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

/* USER CODE BEGIN PV */

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

volatile unsigned int LocalTime;	// 本地时间，单位：ms
bool tp_flag = false;		// 触摸标志位
bool fp_flag = false;		// 指纹触摸标志位
bool timer_500ms_flag = false; //500ms定时器标志位
bool begin_fb_flag = false;
lv_ui guider_ui;
volatile uint8_t touch_IRQ = 0;		// 触摸中断次数
char password[8] = {0,0,0,0,0,0,0,0};
uint8_t black_screen_settings[2] = {0,0};
uint8_t screensaver_settings[2] = {0,0};
uint16_t power_off_count = 0; //关机计数器
uint16_t screensaver_count = 0; // 屏幕保护计数器
uint8_t ver[4] = {0,1,0,1};

/*############################################################################*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

// 输出时钟信息
static void Output_System_Clock_Info(void);

// 串口初始化
void Serial_Init(void);

/*############################################################################*/

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
	
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

	// 串口初始化
	Serial_Init();
	
	// 输出时钟信息
	Output_System_Clock_Info();
	
	// 屏幕初始化
	ST7789V_Init();
	ST7789V_Display_On();
	LCD_BL(1);
	
	// 触摸初始化
	CST816D_Init();
	
	// 开启TIM7，1ms，用于LVGL心跳
	HAL_TIM_Base_Start_IT(&htim7);
	
	lv_init();
	lv_port_disp_init();
	lv_port_indev_init();
	printf("LVGL初始化完成!\r\n");

	// 输出指纹模块信息
	Fingerprintf_Init();
	
	// 开启TIM6，500ms，用于指纹检测定时
	HAL_TIM_Base_Start_IT(&htim6);
	
	// 检查24C02并读取密码
	if(AT24CXX_Check() == 0)
	{
		printf("24C02读取正常!\r\n");
		
		// 读取密码
		AT24C02_read(0, (uint8_t*)password, 7);
		
		printf("password: %s\r\n", password);
    
    // 读取关机黑屏设置
		AT24C02_read(9, black_screen_settings, 2);
		
		printf("black_screen_enable = %d\r\n", black_screen_settings[0]);
		printf("black_screen_delay = %dS\r\n", black_screen_settings[1]);
    
    if(black_screen_settings[0])
    {
      black_screen_mode = true;
    }
    else
    {
      black_screen_mode = false;
    }
    
    black_screen_delay = black_screen_settings[1];
    
    // 读取屏保设置
		AT24C02_read(11, screensaver_settings, 2);
		
		printf("screensaver_enable = %d\r\n", screensaver_settings[0]);
		printf("screensaver_delay = %dS\r\n", screensaver_settings[1]);
    
    if(black_screen_settings[0])
    {
      screensaver_mode = true;
    }
    else
    {
      screensaver_mode = false;
    }
    
    screensaver_delay = screensaver_settings[1];
	}
	else
	{
		printf("24C02读取失败!\r\n");
	}
	
//	lv_demo_widgets();
//	lv_demo_benchmark();
//	lv_demo_stress();
//	lv_demo_keypad_encoder();
//	lv_demo_music();

//	ui_init();
	setup_ui(&guider_ui);
	events_init(&guider_ui);
	custom_init(&guider_ui);
	
/*############################################################################*/

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
		
		// 处理串口数据
		Command_Process();
    
    // 检测开机状态
    Check_PWR_Std();
    
    // 关机后30秒没有动作，屏幕进入黑屏状态
    if((pwr_flag == 0) && timer_500ms_flag && LED_BL_STD && black_screen_mode)
    {
      power_off_count++;
      timer_500ms_flag = false;
      if(power_off_count > black_screen_delay * 120)
      {
        LCD_BL(0); // LCD背光熄灭
      }
    }
    
    // 3分钟无操作，进入屏幕保护模式，黑屏
    if(timer_500ms_flag && LED_BL_STD && screensaver_mode)
    {
      screensaver_count++;
      timer_500ms_flag = false;
      if(screensaver_count > (screensaver_delay * 120)) // 3分钟
      {
        LCD_BL(0); // LCD背光熄灭
      }
    }
		
		// 检查指纹，指纹识别模式，并且屏幕亮的时候检测
		if(fp_flag && begin_fb_flag && LED_BL_STD)
		{
			Check_Fingerprint();
			fp_flag = false;
		}
		
		// 读取触摸位置
		if(tp_flag)
		{
			LCD_BL(1); // LCD背光点亮
      power_off_count = 0;
      screensaver_count = 0;
			tp_pressed = 1;
		
//      touch_IRQ++;
//			if(touch_IRQ > 13)
//			{
//				touch_IRQ = 0;
//				CST816D_Scan();
//			}
			tp_flag = false;
//			HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
		}
		
		if(Fingerprint_Register_Flag)
		{
			Fingerprint_Register_At(FP_Num);
		}
		
		lv_task_handler();

/*############################################################################*/

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**
  * @brief  微秒延时 。
  * @param  us：时长。
  * @retval None.
  */
void HAL_Delay_us(uint32_t us)
{
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000000);
	HAL_Delay(us - 1);
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
}


/**
  * @brief  输出时钟频率。
  * @param  None. 
  * @retval None.
  */
static void Output_System_Clock_Info(void)
{
	uint32_t SysClock = 0, HclkClock = 0, Pclk1Clock = 0, Pclk2Clock = 0;

	SysClock = HAL_RCC_GetSysClockFreq();
	HclkClock = HAL_RCC_GetHCLKFreq();
	Pclk1Clock = HAL_RCC_GetPCLK1Freq();
	Pclk2Clock = HAL_RCC_GetPCLK2Freq();

	printf("SYSCLK= %d Hz, HCLK= %d Hz, PCLK1= %d Hz, PCLK2= %d Hz\r\n",
					SysClock, HclkClock, Pclk1Clock, Pclk2Clock);
	printf("\r\n");
}


/**
  * @brief  串口接收回调函数
  * @param  None. 
  * @retval None.
  */
void Serial_Init(void)
{
	/* 需要在初始化时调用一次否则无法接收到内容 */
	HAL_UARTEx_ReceiveToIdle_DMA(&huart2, Usart2RxBuffer, MAX_USART_SIZE);
	__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);		   // 手动关闭DMA_IT_HT中断	

	/* 需要在初始化时调用一次否则无法接收到内容 */
	HAL_UARTEx_ReceiveToIdle_DMA(&huart3, Usart3RxBuffer, MAX_USART_SIZE);
	__HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);		   // 手动关闭DMA_IT_HT中断	
}


/**
  * @brief  串口接收回调函数
  * @param  None. 
  * @retval None.
  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef * huart, uint16_t Size)
{
	if(huart->Instance == USART2)
	{
		if (Size <= MAX_USART_SIZE)
		{
//			printf("串口2接收到数据\r\n");
//			for(uint8_t i = 0; i < Size; i++)
//				printf("%02X ", Usart2RxBuffer[i]);
//			printf("\r\n");
			
			Usart2RxFlag = 1;
			Usart2RxLength = Size;

			HAL_UARTEx_ReceiveToIdle_DMA(&huart2, Usart2RxBuffer, MAX_USART_SIZE);   // 接收完毕后重启
			__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);                        // 手动关闭DMA_IT_HT中断
		}
		else  // 接收数据长度大于BUFF_SIZE，错误处理
		{
				
		}
	}

	if(huart->Instance == USART3)
	{
		if (Size <= MAX_USART_SIZE)
		{
			Usart3RxFlag = 1;
			Usart3RxLength = Size;
			
//			HAL_UARTEx_ReceiveToIdle_DMA(&huart3, Usart3RxBuffer, MAX_USART_SIZE);   // 接收完毕后重启
//			__HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);                        // 手动关闭DMA_IT_HT中断
//			printf("串口3接收到数据\r\n");
		}
		else  // 接收数据长度大于BUFF_SIZE，错误处理
		{
				
		}
	}
}


/**
  * @brief  串口错误回调函数
  * @param  None. 
  * @retval None.
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef * huart)
{
	if(huart->Instance == USART2)
	{
		HAL_UARTEx_ReceiveToIdle_DMA(&huart2, Usart2RxBuffer, MAX_USART_SIZE);      // 接收发生错误后重启
		__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);                           // 手动关闭DMA_IT_HT中断
		memset(Usart2RxBuffer, 0, MAX_USART_SIZE);                                  // 清除接收缓存
	}
	
	if(huart->Instance == USART3)
	{
		HAL_UARTEx_ReceiveToIdle_DMA(&huart3, Usart3RxBuffer, MAX_USART_SIZE);      // 接收发生错误后重启
		__HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);                           // 手动关闭DMA_IT_HT中断
		memset(Usart3RxBuffer, 0, MAX_USART_SIZE);                                  // 清除接收缓存
	}
}


/**
  * @brief  触摸中断回调函数
  * @param  None. 
  * @retval None.
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == TP_INT_Pin)
	{
		tp_flag = true;
		HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
//		printf("有触摸!\r\n");
	}
}


/**
  * @brief  触摸500ms定时器中断回调函数
  * @param  None. 
  * @retval None.
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		fp_flag = true;
    timer_500ms_flag = true;
	}
	
	if(htim->Instance == TIM7)
	{
		lv_tick_inc(1);		// 给LVGL提供1ms的心跳时期
	}
}

/*############################################################################*/

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
