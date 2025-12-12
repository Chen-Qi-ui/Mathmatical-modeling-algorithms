/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "keyled.h"
#include "lcd.h"

#include <stdint.h>
#include "adc.h"
#include <stdio.h>
#include "queue.h"
#include "stdio.h"
#include "semphr.h"
#include "USART.h"
#include "event_groups.h"
volatile uint32_t voltage = 0;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define BITMASK_KEY_LEFT   (0b00000001<<2)
#define BITMASK_KEY_DOWN   (0b00000001<<1)
#define BITMASK_KEY_RIGHT  (0b00000001<<0)
#define BITMASK_SYNC      (BITMASK_KEY_LEFT | BITMASK_KEY_DOWN | BITMASK_KEY_RIGHT)
uint16_t curScreenX=90;
uint16_t curScreenY=150;
uint16_t lastScreenX=120;
uint16_t lastScreenY=180;
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
/* Definitions for Task_Buzzer */
osThreadId_t Task_BuzzerHandle;
const osThreadAttr_t Task_Buzzer_attributes = {
  .name = "Task_Buzzer",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_LED */
osThreadId_t Task_LEDHandle;
const osThreadAttr_t Task_LED_attributes = {
  .name = "Task_LED",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_LED2 */
osThreadId_t Task_LED2Handle;
const osThreadAttr_t Task_LED2_attributes = {
  .name = "Task_LED2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for eventGroup */
osEventFlagsId_t eventGroupHandle;
const osEventFlagsAttr_t eventGroup_attributes = {
  .name = "eventGroup"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void AppTask_Buzzer(void *argument);
void AppTask_LED(void *argument);
void AppTask_LED2(void *argument);

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
  /* creation of Task_Buzzer */
  Task_BuzzerHandle = osThreadNew(AppTask_Buzzer, NULL, &Task_Buzzer_attributes);

  /* creation of Task_LED */
  Task_LEDHandle = osThreadNew(AppTask_LED, NULL, &Task_LED_attributes);

  /* creation of Task_LED2 */
  Task_LED2Handle = osThreadNew(AppTask_LED2, NULL, &Task_LED2_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of eventGroup */
  eventGroupHandle = osEventFlagsNew(&eventGroup_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_AppTask_Buzzer */
/**
  * @brief  Function implementing the Task_Buzzer thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_AppTask_Buzzer */
void AppTask_Buzzer(void *argument)
{
  /* USER CODE BEGIN AppTask_Buzzer */
  /* Infinite loop */
  for(;;)
  {
      if(ScanPressedKey(50)!=KEY_DOWN)
      {
        vTaskDelay(pdMS_TO_TICKS(50));
        continue;
      }
      lcd_show_str(0, 40, 16, "Task_Buzzer reaches sync point", RED);
      xEventGroupSync(eventGroupHandle, BITMASK_KEY_DOWN, BITMASK_SYNC, portMAX_DELAY);
      while(1)
      {
        Buzzer_Toggle();
        vTaskDelay(pdMS_TO_TICKS(500));
      }
  }
  /* USER CODE END AppTask_Buzzer */
}

/* USER CODE BEGIN Header_AppTask_LED */
/**
* @brief Function implementing the Task_LED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_LED */
void AppTask_LED(void *argument)
{
  /* USER CODE BEGIN AppTask_LED */
  /* Infinite loop */
  for(;;)
  {
    if(ScanPressedKey(50)!=KEY_LEFT)
      {
        vTaskDelay(pdMS_TO_TICKS(50));
        continue;
      }
      lcd_show_str(0, 60, 16, "Task_LED1 reaches sync point", RED);
      xEventGroupSync(eventGroupHandle, BITMASK_KEY_LEFT, BITMASK_SYNC, portMAX_DELAY);
      while(1)
      {
        LED1_Toggle();
        vTaskDelay(pdMS_TO_TICKS(500));
      }
  }
  /* USER CODE END AppTask_LED */
}

/* USER CODE BEGIN Header_AppTask_LED2 */
/**
* @brief Function implementing the Task_LED2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_LED2 */
void AppTask_LED2(void *argument)
{
  /* USER CODE BEGIN AppTask_LED2 */
  /* Infinite loop */
  for(;;)
  {
     if(ScanPressedKey(50)!=KEY_RIGHT)
      {
        vTaskDelay(pdMS_TO_TICKS(50));
        continue;
      }
      lcd_show_str(0, 80, 16, "Task_LED2 reaches sync point", RED);
      xEventGroupSync(eventGroupHandle, BITMASK_KEY_RIGHT, BITMASK_SYNC, portMAX_DELAY);
      while(1)
      {
        LED2_Toggle();
        vTaskDelay(pdMS_TO_TICKS(500));
      }
  }
  /* USER CODE END AppTask_LED2 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

