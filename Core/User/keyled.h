#ifndef __KEYLED_H
#define __KEYLED_H

#include "main.h"



#ifdef LED1_Pin
#define LED1_Toggle()     HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin)
#define LED1_ON()         HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET)
#define LED1_OFF()        HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET)
#endif


#ifdef LED2_Pin
#define LED2_Toggle()     HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin)
#define LED2_ON()         HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET)
#define LED2_OFF()        HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET)
#endif

#ifdef Buzzer_Pin
#define Buzzer_Toggle()  HAL_GPIO_TogglePin(Buzzer_GPIO_Port, Buzzer_Pin)
#define Buzzer_ON()      HAL_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_RESET)
#define Buzzer_OFF()     HAL_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_SET)
#endif

typedef enum{
    KEY_NONE = 0,
    KEY_LEFT = 1,
    KEY_RIGHT = 2,
    KEY_UP = 3,
    KEY_DOWN = 4
} KEYS;

#define KEY_WAIT_ALWAYS    0
KEYS ScanPressedKey(uint32_t timeout);
#endif