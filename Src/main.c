/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32_u8g2.h"
#include <stdio.h>
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//??:??? 16*16
unsigned char hz_wang[] = {
0x00,0x02,0x82,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x82,0x02,0x00,0x00,
0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,/*"?",0*/
};

unsigned char hz_dong[] = {
0x00,0x08,0x88,0x48,0x28,0x18,0x0F,0xE8,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,
0x00,0x20,0x11,0x09,0x05,0x41,0x81,0x7F,0x01,0x01,0x05,0x09,0x11,0x20,0x00,0x00,/*"?",1*/
};

unsigned char hz_yang[] = {
0x00,0xFE,0x02,0x22,0xDA,0x06,0x00,0xFC,0x04,0x04,0x04,0x04,0x04,0xFC,0x00,0x0,
0x00,0xFF,0x08,0x10,0x08,0x07,0x00,0xFF,0x41,0x41,0x41,0x41,0x41,0xFF,0x00,0x00,/*"?",2*/
};
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
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  MX_GPIO_Init();
  MX_I2C2_Init();
  MX_TIM1_Init();

  /* USER CODE BEGIN 2 */
  u8g2_t u8g2;
  HAL_TIM_Base_Start(&htim1);
  u8g2Init(&u8g2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    static uint8_t mode = 1;
    static int16_t scroll_x = 0;
    static int16_t scroll_y = 0;
    static uint8_t dir = 0;
    static uint8_t anim_step = 0;

    switch(mode)
    {
        //=====??1:U8G2 DEMO??=====
        case 1:
            u8g2_ClearBuffer(&u8g2);
            u8g2_SetFont(&u8g2, u8g2_font_10x20_tf);
            u8g2_DrawStr(&u8g2, 0, 18, "U8G2 DEMO");
            u8g2_SetFont(&u8g2, u8g2_font_6x10_tf);
            u8g2_DrawFrame(&u8g2, 0, 24, 60, 30);
            u8g2_DrawCircle(&u8g2, 90, 38, 12, U8G2_DRAW_ALL);
            u8g2_DrawLine(&u8g2, 0, 60, 127, 60);
            u8g2_SendBuffer(&u8g2);
            HAL_Delay(2500);
            mode = 2;
            break;

        //=====??2:??+??=====
        case 2:
            u8g2_ClearBuffer(&u8g2);
            u8g2_SetFont(&u8g2, u8g2_font_ncenB10_tf);
            u8g2_DrawStr(&u8g2, 5, 15, "632407030310");
            u8g2_DrawXBMP(&u8g2, 10, 35, 16,16,hz_wang);
            u8g2_DrawXBMP(&u8g2, 30, 35, 16,16,hz_dong);
            u8g2_DrawXBMP(&u8g2, 50, 35, 16,16,hz_yang);
            u8g2_SendBuffer(&u8g2);
            HAL_Delay(2500);
            mode = 3;
            scroll_x = 0;
            scroll_y = 0;
            dir = 0;
            break;

        //=====??3:?????????=====
        case 3:
            u8g2_ClearBuffer(&u8g2);
            u8g2_SetFont(&u8g2, u8g2_font_8x13_tf);
            if(dir == 0)
            {
                //??
                u8g2_DrawStr(&u8g2, scroll_x, 32, "SCROLL TEST");
                scroll_x += 1;
                if(scroll_x > 128) { scroll_x = -60; dir = 1; }
            }
            else if(dir == 1)
            {
                //??
                u8g2_DrawStr(&u8g2, scroll_x, 32, "SCROLL TEST");
                scroll_x -= 1;
                if(scroll_x < -60) { scroll_x = 128; dir = 2; }
            }
            else if(dir == 2)
            {
                //??
                u8g2_DrawStr(&u8g2, 20, scroll_y, "SCROLL TEST");
                scroll_y += 1;
                if(scroll_y > 64) { scroll_y = -15; dir = 3; }
            }
            else if(dir == 3)
            {
                //??
                u8g2_DrawStr(&u8g2, 20, scroll_y, "SCROLL TEST");
                scroll_y -= 1;
                if(scroll_y < -15) { scroll_y = 64; dir = 0; }
            }
            u8g2_SendBuffer(&u8g2);
            HAL_Delay(35);
            anim_step ++;
            if(anim_step > 220)
            {
                anim_step = 0;
                mode = 4;
            }
            break;

        //=====??4:??????(????)=====
        case 4:
            u8g2_ClearBuffer(&u8g2);
            uint8_t jump_y;
            if(anim_step < 15) jump_y = 20;
            else if(anim_step < 30) jump_y = 12;
            else if(anim_step < 45) jump_y = 20;
            else jump_y = 28;

            //???:?+??+??
            u8g2_DrawCircle(&u8g2, 64, jump_y, 6, U8G2_DRAW_ALL);
            u8g2_DrawLine(&u8g2, 64, jump_y+6, 64, jump_y+18);
            u8g2_DrawLine(&u8g2, 64, jump_y+9, 54, jump_y+14);
            u8g2_DrawLine(&u8g2, 64, jump_y+9, 74, jump_y+14);
            u8g2_DrawLine(&u8g2, 64, jump_y+18, 54, jump_y+28);
            u8g2_DrawLine(&u8g2, 64, jump_y+18, 74, jump_y+28);
            u8g2_SendBuffer(&u8g2);
            HAL_Delay(60);
            anim_step ++;
            if(anim_step > 80)
            {
                anim_step = 0;
                mode = 1;
            }
            break;
    }
    /* USER CODE END 3 */
  }
  return 0;
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

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

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */

  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/