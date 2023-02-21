#include "led.h"
#include "exti.h"

void exti_init(void) {
    GPIO_InitTypeDef gpio_init_struct;
    __HAL_RCC_GPIOE_CLK_ENABLE(); //时钟使能

    gpio_init_struct.Pin = GPIO_PIN_4;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING; //下沿触发
    gpio_init_struct.Pull = GPIO_PULLUP;          //上拉
    //gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOE, &gpio_init_struct);

    HAL_NVIC_SetPriority(EXTI4_IRQn, 2, 0); //设置优先级
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);//使能中断
}

void EXTI4_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4); //公共处理函数
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    HAL_Delay(20);
    if (GPIO_Pin == GPIO_PIN_4) {
        if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == 0) {
            HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_9);
        }
    }
}