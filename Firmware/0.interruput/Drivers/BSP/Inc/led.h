#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

//LED
#define LED_GPIO GPIOF
#define LED_READ_GPIO_PIN GPIO_PIN_9
#define LED_GREEN_GPIO_PIN GPIO_PIN_10

#define LED_GPIO_CLK_ENABLE() __HAL_RCC_GPIOF_CLK_ENABLE()
#define LED_READ_LIGHT(STATE) HAL_GPIO_WritePin(LED_GPIO,LED_READ_GPIO_PIN,STATE)
#define LED_GREEN_LIGHT(STATE) HAL_GPIO_WritePin(LED_GPIO,LED_GREEN_GPIO_PIN,STATE)

void led_init(void);

#ifdef __cplusplus
}
#endif
#endif