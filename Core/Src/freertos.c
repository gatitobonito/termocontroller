/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#define NTC1  1
#define NTC2  2

extern void get_adc_data(uint8_t ntc);
extern uint16_t median_filter (uint16_t *p, size_t n);
extern void CAN_send_data(int8_t data1, int8_t data2);
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskNTC1 */
osThreadId_t TaskNTC1Handle;
const osThreadAttr_t TaskNTC1_attributes = {
  .name = "TaskNTC1",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskNTC2 */
osThreadId_t TaskNTC2Handle;
const osThreadAttr_t TaskNTC2_attributes = {
  .name = "TaskNTC2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTaskNTC1(void *argument);
void StartTaskNTC2(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of TaskNTC1 */
  TaskNTC1Handle = osThreadNew(StartTaskNTC1, NULL, &TaskNTC1_attributes);

  /* creation of TaskNTC2 */
  TaskNTC2Handle = osThreadNew(StartTaskNTC2, NULL, &TaskNTC2_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  int8_t temp_ntc1=0;
  int8_t temp_ntc2=0;
  for(;;)
  {
    temp_ntc1 = aggregate_data(NTC1);
    temp_ntc2 = aggregate_data(NTC2);
    CAN_send_data(temp_ntc1, temp_ntc2);
    osDelay(100);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTaskNTC1 */
/**
* @brief Function implementing the TaskNTC1 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskNTC1 */
void StartTaskNTC1(void *argument)
{
  /* USER CODE BEGIN StartTaskNTC1 */
  /* Infinite loop */
  for(;;)
  {
    get_adc_data(NTC2);
    osDelay(10);
  }
  /* USER CODE END StartTaskNTC1 */
}

/* USER CODE BEGIN Header_StartTaskNTC2 */
/**
* @brief Function implementing the TaskNTC2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskNTC2 */
void StartTaskNTC2(void *argument)
{
  /* USER CODE BEGIN StartTaskNTC2 */
  /* Infinite loop */
  for(;;)
  {
    get_adc_data(NTC1);
    osDelay(10);
  }
  /* USER CODE END StartTaskNTC2 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

