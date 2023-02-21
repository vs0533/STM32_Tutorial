#ifndef __EXTI_H
#define __EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

//EXTI
//#define EXTI_GPIO_CLK_ENABLE() __HAL_RCC_GPIOE_CLK_ENABLE()
//#define EXTI_GPIO_PIN GPIO_PIN_4

void exti_init(void);

#ifdef __cplusplus
}
#endif
#endif