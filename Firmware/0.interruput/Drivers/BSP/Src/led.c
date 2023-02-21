#include "led.h"

void led_init() {
    LED_GPIO_CLK_ENABLE();
    GPIO_InitTypeDef gpio_init_struct;
    gpio_init_struct.Pull = LED_READ_GPIO_PIN | LED_GREEN_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP; //推挽输出
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW; //低速

    HAL_GPIO_Init(LED_GPIO, &gpio_init_struct);
    LED_READ_LIGHT(1); //默认输出3.3伏特 led接入3.3所以不导通 如果输入0则输出低电压led3.3就导通
    LED_GREEN_LIGHT(1);
}