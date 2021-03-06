/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */
//mrg-104-170607a => mrg-104-170612a
//?????? ????
//D1T1STOP ack command?? D1T1AXXXXTXX?? ???? ???? ????

//mrg-104-170612a => mrg-104-170613a
//?????? ????
//D1T1AXXXXTXX ack command?? D1T1STOPTXX?? ???? ???? ????

//mrg-104-170613a => mrg-104-170614a
//?????? ????
//cc off command ch1, ch2?????? cc off?? ???? ???????? 
//channel???? off ???? ?????? ????

//mrg-104-170703a => mrg-104-170901a
//?????? ????
//1???? ???? ???? ?????? CC Off???? ?????? SoftReset?? ????

//mrg-104-170901a => mrg-104-190211a
//??????,??????,??????
//EDID Write(4K60Hz??, 4K30Hz??) :D1S0EDW2 :D1S0EDW3
//EDID Data State ?????? :D1R0EDS2 :D1R0EDS3

//mrg-104-190220a => mrg-104-191205a
//??????
//????,???? ???? ???? ?? ???? Command ????

//mrg-104-191205a => mrg-104-201029a
//??????,??????,??????
//?????? ???????? ???????? Command?? ???? ?????? ???? ?????? ???????? ?????? ????
//Rx Interrupt?? ?????????? ?????? ?????? while?? ????



#include "string.h"
#include "global_var.h"
#include "define.c"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_UART4_Init(void);
static void MX_UART5_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void SystemClock_Config(void);
static void MX_TIM2_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/


/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
// printf ?????? ???? ???? ?? ????/////////////////////
//void printf_port(unsigned char port)
//{
#ifdef __GNUC__
   /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf  
      set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
  
PUTCHAR_PROTOTYPE
{
  uint8_t buf0;
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  buf0 = ch;
  if(Printf_port == COM_PORT1)
    HAL_UART_Transmit(&huart1,&buf0,1,100); // ?????? ?????? ????
  else if(Printf_port == COM_PORT2)
    HAL_UART_Transmit(&huart2,&buf0,1,100); // ?????? ?????? ????
  else if(Printf_port == COM_PORT3)
    HAL_UART_Transmit(&huart5,&buf0,1,100); // ?????? ?????? ????
  else if(Printf_port == COM_PORT4)
    HAL_UART_Transmit(&huart4,&buf0,1,100); // ?????? ?????? ????      
  else if(Printf_port == COM_RS485)
  {
     RS485_RX_OFF;
     RS485_TX_ON;
     HAL_UART_Transmit(&huart3,&buf0,1,100); // ?????? ?????? ????
     RS485_TX_OFF;
     RS485_RX_ON;
  }
  /* Loop until the end of transmission */
  //while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) // ?????? ?????? ????
  //{}
  while(HAL_UART_STATE_BUSY_TX == 0)
  {
  }
  return ch;
}
////////////////////////////////////////////////////
   

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
  unsigned char i;
  
re_start:  

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  SystemClock_Config();
  MX_TIM2_Init();

  /* USER CODE BEGIN 2 */
  RS485_TX_OFF;
  RS485_RX_ON;
  
  Re_start_mode = 0;
  
	Printf_port = COM_RS485;
	Pro_ver[0] = '2';
	Pro_ver[1] = '0';
	Pro_ver[2] = '1';
	Pro_ver[3] = '0';
	Pro_ver[4] = '2';
	Pro_ver[5] = '9';
	Pro_ver[6] = 'a';
  //printf("\n\rMCU  : MRG-104-1%s\n\r",Pro_ver);
  
  
  HAL_UART_Receive_IT(&huart1,&Data_com1,1);
  HAL_UART_Receive_IT(&huart2,&Data_com2,1);
  HAL_UART_Receive_IT(&huart3,&Data_com3,1);
  HAL_UART_Receive_IT(&huart4,&Data_com4,1);
  HAL_UART_Receive_IT(&huart5,&Data_com5,1);
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  Com_input_time_state = 0;
  Com1_input_tim_chk = 0;
  Com2_input_tim_chk = 0;
  Com3_input_tim_chk = 0;
  Com4_input_tim_chk = 0;
  Ack_tim_chk = 0;
  Ack_06_check = 0;
  Time_sec = 0;
  Time_hour = 0;
  Com1_jig_state1 = 0;
  Com1_jig_state2 = 0;
  Com2_jig_state1 = 0;
  Com2_jig_state2 = 0;
  Com3_jig_state1 = 0;
  Com3_jig_state2 = 0;
  Com4_jig_state1 = 0;
  Com4_jig_state2 = 0;
  
  
  while (1)
  {      
    if(Com5_state == 3)//rs485 port
    {
      com5_work();
      Com5_state = 0;
      HAL_UART_Receive_IT(&huart3,&Data_com3,1);
      for(i = 0;i < Com3_num;i++)
        Com3_data[i] = 0x20;
    }
    else
    {
      if((Com1_state == 3)||((Com1_state == 1)&&(Com1_input_tim_chk > OVER_TIME)))
      {
        com1_work(); 
        Com1_state = 0;
        Com_input_time_state &= 0xfe;
        Com1_input_tim_chk = 0;
        HAL_UART_Receive_IT(&huart1,&Data_com1,1);
        for(i = 0;i < Com1_num;i++)
          Com1_data[i] = 0x20;
      }
      if((Com2_state == 3)||((Com2_state == 1)&&(Com2_input_tim_chk > OVER_TIME)))
      {
        com2_work();
        Com2_state = 0;
        Com_input_time_state &= 0xfd;
        Com2_input_tim_chk = 0;
        HAL_UART_Receive_IT(&huart2,&Data_com2,1);
        for(i = 0;i < Com2_num;i++)
          Com2_data[i] = 0x20;
      }
      if((Com3_state == 3)||((Com3_state == 1)&&(Com3_input_tim_chk > OVER_TIME)))
      {
        com3_work();
        Com3_state = 0;
        Com_input_time_state &= 0xfb;
        Com3_input_tim_chk = 0;
        HAL_UART_Receive_IT(&huart5,&Data_com5,1);
        for(i = 0;i < Com5_num;i++)
          Com5_data[i] = 0x20;
      }
      if((Com4_state == 3)||((Com4_state == 1)&&(Com4_input_tim_chk > OVER_TIME)))
      {
        com4_work();
        Com4_state = 0;
        Com_input_time_state &= 0xf7;
        Com4_input_tim_chk = 0;
        HAL_UART_Receive_IT(&huart4,&Data_com4,1);
        for(i = 0;i < Com4_num;i++)
          Com4_data[i] = 0x20;
      }
    }
    
    if(Time_sec > 9999)
    {
      Time_sec = 0;
      Time_hour++;
      if((Time_hour > 3599)&&(Com1_jig_state1 == 0x00)&&(Com2_jig_state1 == 0x00)&&(Com3_jig_state1 == 0x00)&&(Com4_jig_state1 == 0x00)
                           &&(Com1_jig_state2 == 0x00)&&(Com2_jig_state2 == 0x00)&&(Com3_jig_state2 == 0x00)&&(Com4_jig_state2 == 0x00))
      {
        Re_start_mode = 1;
      
        Com5_data[0] = 0x30;
        Com5_data[2] = 'R';
        Com5_data[3] = 'E';
        Com5_data[4] = 'S';
        Com5_data[5] = 'E';
        Com5_data[6] = 'T';
        Com5_num = 8;
        rs485_ack_command();
        Time_hour = 0;
      }
    }
    
    if(Re_start_mode)
    {
         goto re_start;     
    }  
	HAL_UART_Receive_IT(&huart1,&Data_com1,1);//mrg-104-201029a
	HAL_UART_Receive_IT(&huart2,&Data_com2,1);//mrg-104-201029a
	HAL_UART_Receive_IT(&huart3,&Data_com3,1);//mrg-104-201029a
	HAL_UART_Receive_IT(&huart4,&Data_com4,1);//mrg-104-201029a
	HAL_UART_Receive_IT(&huart5,&Data_com5,1);//mrg-104-201029a
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 144;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* TIM2 init function */
void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_SlaveConfigTypeDef sSlaveConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 7450;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim2);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);

  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
  sSlaveConfig.InputTrigger = TIM_TS_ITR0;
  HAL_TIM_SlaveConfigSynchronization(&htim2, &sSlaveConfig);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);

}

/* UART4 init function */
void MX_UART4_Init(void)
{

  huart4.Instance = UART4;
  huart4.Init.BaudRate = 19200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart4);

}

/* UART5 init function */
void MX_UART5_Init(void)
{

  huart5.Instance = UART5;
  huart5.Init.BaudRate = 19200;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart5);

}

/* USART1 init function */
void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 19200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart1);

}

/* USART2 init function */
void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 19200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart2);

}

/* USART3 init function */
void MX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart3);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __GPIOE_CLK_ENABLE();
  __GPIOH_CLK_ENABLE();
  __GPIOA_CLK_ENABLE();
  __GPIOB_CLK_ENABLE();
  __GPIOC_CLK_ENABLE();
  __GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PE6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
