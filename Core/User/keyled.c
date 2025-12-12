#include "keyled.h"
#include "stm32f4xx_hal_gpio.h"
#include  "main.h"
#include <stdint.h>
 KEYS ScanPressedKey(uint32_t timeout)
{
    uint32_t tickstart = HAL_GetTick();
    const uint32_t btnDelay = 20;
    while(1)
    {
      if(HAL_GPIO_ReadPin(KeyRight_GPIO_Port, KeyRight_Pin) == GPIO_PIN_RESET)
     {
        HAL_Delay(btnDelay);
        return KEY_RIGHT;
     }
      if(HAL_GPIO_ReadPin(KeyDown_GPIO_Port, KeyDown_Pin) == GPIO_PIN_RESET)
     {
        HAL_Delay(btnDelay);
        return KEY_DOWN;
     }
      if(HAL_GPIO_ReadPin(KeyLeft_GPIO_Port, KeyLeft_Pin) == GPIO_PIN_RESET)
     {
        HAL_Delay(btnDelay);
        return KEY_LEFT;
     }
      if(HAL_GPIO_ReadPin(KeyUp_GPIO_Port, KeyUp_Pin) == GPIO_PIN_SET)
     {
        HAL_Delay(btnDelay);
        return KEY_UP;
     }
        if(timeout != KEY_WAIT_ALWAYS)
        {
            if((HAL_GetTick() - tickstart) >= timeout)
            {
                break;
            }
        }
    }
    return KEY_NONE;
}