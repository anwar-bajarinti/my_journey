/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  */
/* USER CODE END Header */

#include "main.h"
#include "stm32f4xx_it.h"

/* USER CODE BEGIN 0 */
extern volatile uint32_t capture;   // FIX: must match volatile in main.c
/* USER CODE END 0 */

extern TIM_HandleTypeDef htim2;

void NMI_Handler(void)          { while (1) {} }
void HardFault_Handler(void)    { while (1) {} }
void MemManage_Handler(void)    { while (1) {} }
void BusFault_Handler(void)     { while (1) {} }
void UsageFault_Handler(void)   { while (1) {} }
void SVC_Handler(void)          {}
void DebugMon_Handler(void)     {}
void PendSV_Handler(void)       {}

void SysTick_Handler(void)
{
  HAL_IncTick();
}

/**
  * @brief TIM2 global interrupt handler
  *        capture is updated ONLY here — i.e., only when button/signal
  *        triggers a rising edge on PA0 (TIM2 CH1).
  *        counter in main() runs freely via __HAL_TIM_GET_COUNTER.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
  /* USER CODE END TIM2_IRQn 0 */

  HAL_TIM_IRQHandler(&htim2);   // let HAL clear the flag first

  /* USER CODE BEGIN TIM2_IRQn 1 */
  capture = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);  // snapshot on press
  /* USER CODE END TIM2_IRQn 1 */
}

/* USER CODE BEGIN 1 */
/* USER CODE END 1 */