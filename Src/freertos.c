/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     

#include "Ass-03.h"

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
osThreadId ControlTaskHandle;
osThreadId CameraTaskHandle;
osThreadId LCDTaskHandle;
osThreadId SDTaskHandle;
osThreadId TimeTaskHandle;
osThreadId TPTaskHandle;
osMutexId SDIODCMIMutexHandle;
osSemaphoreId DCMILineCompleteHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartControlTask(void const * argument);
void StartCameraTask(void const * argument);
void StartLCDTask(void const * argument);
void StartSDTask(void const * argument);
void StartTimeTask(void const * argument);
void StartTPTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];
  
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )  
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}                   
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* definition and creation of SDIODCMIMutex */
  osMutexDef(SDIODCMIMutex);
  SDIODCMIMutexHandle = osMutexCreate(osMutex(SDIODCMIMutex));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of DCMILineComplete */
  osSemaphoreDef(DCMILineComplete);
  DCMILineCompleteHandle = osSemaphoreCreate(osSemaphore(DCMILineComplete), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  // STEPIEN: Semaphore starts with resource available, so do a wait first to make resource unavailable
  osSemaphoreWait(DCMILineCompleteHandle,osWaitForever);
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of ControlTask */
  osThreadDef(ControlTask, StartControlTask, osPriorityNormal, 0, 1024);
  ControlTaskHandle = osThreadCreate(osThread(ControlTask), NULL);

  /* definition and creation of CameraTask */
  osThreadDef(CameraTask, StartCameraTask, osPriorityNormal, 0, 1024);
  CameraTaskHandle = osThreadCreate(osThread(CameraTask), NULL);

  /* definition and creation of LCDTask */
  osThreadDef(LCDTask, StartLCDTask, osPriorityNormal, 0, 1024);
  LCDTaskHandle = osThreadCreate(osThread(LCDTask), NULL);

  /* definition and creation of SDTask */
  osThreadDef(SDTask, StartSDTask, osPriorityNormal, 0, 1024);
  SDTaskHandle = osThreadCreate(osThread(SDTask), NULL);

  /* definition and creation of TimeTask */
  osThreadDef(TimeTask, StartTimeTask, osPriorityNormal, 0, 1024);
  TimeTaskHandle = osThreadCreate(osThread(TimeTask), NULL);

  /* definition and creation of TPTask */
  osThreadDef(TPTask, StartTPTask, osPriorityNormal, 0, 1024);
  TPTaskHandle = osThreadCreate(osThread(TPTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartControlTask */
/**
  * @brief  Function implementing the ControlTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartControlTask */
__weak void StartControlTask(void const * argument)
{
  /* USER CODE BEGIN StartControlTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartControlTask */
}

/* USER CODE BEGIN Header_StartCameraTask */
/**
* @brief Function implementing the CameraTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCameraTask */
__weak void StartCameraTask(void const * argument)
{
  /* USER CODE BEGIN StartCameraTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartCameraTask */
}

/* USER CODE BEGIN Header_StartLCDTask */
/**
* @brief Function implementing the LCDTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLCDTask */
__weak void StartLCDTask(void const * argument)
{
  /* USER CODE BEGIN StartLCDTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartLCDTask */
}

/* USER CODE BEGIN Header_StartSDTask */
/**
* @brief Function implementing the SDTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSDTask */
__weak void StartSDTask(void const * argument)
{
  /* USER CODE BEGIN StartSDTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartSDTask */
}

/* USER CODE BEGIN Header_StartTimeTask */
/**
* @brief Function implementing the TimeTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTimeTask */
__weak void StartTimeTask(void const * argument)
{
  /* USER CODE BEGIN StartTimeTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTimeTask */
}

/* USER CODE BEGIN Header_StartTPTask */
/**
* @brief Function implementing the TPTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTPTask */
__weak void StartTPTask(void const * argument)
{
  /* USER CODE BEGIN StartTPTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTPTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
