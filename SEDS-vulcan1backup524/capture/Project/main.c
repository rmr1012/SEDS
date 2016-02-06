/**
  ******************************************************************************
  * @file    TIM/PWM_Input/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
void Usart1Init(void);
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_PWM_Input
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_ICInitTypeDef  TIM_ICInitStructure;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     
  Usart1Init();      
  /* System Clocks Configuration */
  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  /* GPIOA clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);


  /* NVIC configuration */

  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM4 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);


	
  /* Configure the GPIO ports */

  GPIO_InitTypeDef GPIO_InitStructure;

  /* TIM4 channel 2 pin (PA.07) configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOB, &GPIO_InitStructure);



  /* TIM4 configuration: PWM Input mode ------------------------
     The external signal is connected to TIM4 CH2 pin (PA.01), 
     The Rising edge is used as active edge,
     The TIM4 CCR2 is used to compute the frequency value 
     The TIM4 CCR1 is used to compute the duty cycle value
  ------------------------------------------------------------ */

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;

  TIM_PWMIConfig(TIM4, &TIM_ICInitStructure);

  /* Select the TIM4 Input Trigger: TI2FP2 */
  TIM_SelectInputTrigger(TIM4, TIM_TS_TI2FP2);

  /* Select the slave Mode: Reset Mode */
  TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Reset);

  /* Enable the Master/Slave Mode */
  TIM_SelectMasterSlaveMode(TIM4, TIM_MasterSlaveMode_Enable);

  /* TIM enable counter */
  TIM_Cmd(TIM4, ENABLE);

  /* Enable the CC2 Interrupt Request */
  TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);

  while (1);
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */


/**
  * @brief  Configure the GPIO Pins.
  * @param  None
  * @retval None
  */

/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void Usart1Init(void) 
{
 
	GPIO_InitTypeDef GPIO_InitStructure;
	 
	USART_InitTypeDef USART_InitStructure;
	 
	USART_ClockInitTypeDef USART_ClockInitStructure;
	 
	//enable bus clocks
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	 
	//Set USART1 Tx (PA.09) as AF push-pull
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	 
	//Set USART1 Rx (PA.10) as input floating
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	 
	USART_ClockStructInit(&USART_ClockInitStructure);
	 
	USART_ClockInit(USART1, &USART_ClockInitStructure);
	 
	USART_InitStructure.USART_BaudRate = 9600;
	 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	 
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	 
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	 
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	 
	//Write USART1 parameters
	 
	USART_Init(USART1, &USART_InitStructure);
	 
	//Enable USART1
	 
	USART_Cmd(USART1, ENABLE);
	USART_ClockStructInit(&USART_ClockInitStructure);
	USART_ClockInit(USART1, &USART_ClockInitStructure);
 
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  while (1)
  {}
}

#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
