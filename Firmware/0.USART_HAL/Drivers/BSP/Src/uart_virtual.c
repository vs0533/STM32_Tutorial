#include "main.h"
#include "uart_virtual.h"

// use PA0 virtual uart

void uart_virtual_init(VIRTUAL_HandleTypeDef *hvuart) {

    UNUSED(hvuart); //使用宏告诉编译器这个参数不用

    GPIO_InitTypeDef gpio_init_struct;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pin = VIRTUAL_GPIO_PIN;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;

    __HAL_RCC_GPIOA_CLK_ENABLE();

    HAL_GPIO_WritePin(VIRTUAL_GPIO_PORT, VIRTUAL_GPIO_PIN, GPIO_PIN_SET);
    HAL_GPIO_Init(VIRTUAL_GPIO_PORT, &gpio_init_struct);
}

//使用时发一堆数据 len为数组长度减1
void uart_virtual_transmit(VIRTUAL_HandleTypeDef *hvuart, uint16_t *pdata, uint32_t len) {
    do {
        uart_virtual_sendframe(hvuart, *pdata++);
    } while (len--);
}

//安帧发送数据位
void uart_virtual_sendframe(VIRTUAL_HandleTypeDef *hvuart, uint16_t data) {
    uint32_t i, ctr_bitIsOne = 0; //收集是1的位数
    //引脚输出0 即准备发送
    HAL_GPIO_WritePin(VIRTUAL_GPIO_PORT, VIRTUAL_GPIO_PIN, GPIO_PIN_RESET);
    VIRTUAL_DELAY_1_SYMBOL();//延迟相当于切换到下一位
    //先不管校验位，把前七位发完
    //从0位开始到6位结束 也就是数据前7位 按位做与1操作 判断数据位是1或者0 如果是1 if语句就执行
    for (i = 0; i < 7; i++) {
        if ((data & (0x01 << i)) != 0) {
            HAL_GPIO_WritePin(VIRTUAL_GPIO_PORT, VIRTUAL_GPIO_PIN, GPIO_PIN_SET);
            ctr_bitIsOne++;
        } else {
            HAL_GPIO_WritePin(VIRTUAL_GPIO_PORT, VIRTUAL_GPIO_PIN, GPIO_PIN_RESET);
        }
        VIRTUAL_DELAY_1_SYMBOL();
    }
    //如果数据位是8 并且 使用了校验位 则不发送了 否则 发送
    if (hvuart->Init.DataBits == VIRTUAL_DATABITS_8 && hvuart->Init.Parity != VIRTUAL_NOPARITY) {

    } else {
        if ((data & (0x01 << 7)) != 0) {
            HAL_GPIO_WritePin(VIRTUAL_GPIO_PORT, VIRTUAL_GPIO_PIN, GPIO_PIN_SET);
            ctr_bitIsOne++;
        } else {
            HAL_GPIO_WritePin(VIRTUAL_GPIO_PORT, VIRTUAL_GPIO_PIN, GPIO_PIN_RESET);
        }
        VIRTUAL_DELAY_1_SYMBOL();
    }
    //如果数据位是9位 并且没有使用校验位 则发送第9位
    if (hvuart->Init.DataBits == VIRTUAL_DATABITS_9 && hvuart->Init.Parity == VIRTUAL_NOPARITY) {
        if ((data & (0x01 << 8)) != 0) {
            HAL_GPIO_WritePin(VIRTUAL_GPIO_PORT, VIRTUAL_GPIO_PIN, GPIO_PIN_SET);
            ctr_bitIsOne++;
        } else {
            HAL_GPIO_WritePin(VIRTUAL_GPIO_PORT, VIRTUAL_GPIO_PIN, GPIO_PIN_RESET);
        }
        VIRTUAL_DELAY_1_SYMBOL();
    }
    //如果是奇校验 且 数据有效位中是偶数则发送1 是奇数发0
    if (hvuart->Init.Parity == VIRTUAL_ODDPARITY) {
        if (ctr_bitIsOne % 2 == 0) {
            HAL_GPIO_WritePin(VIRTUAL_GPIO_PORT, VIRTUAL_GPIO_PIN, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(VIRTUAL_GPIO_PORT, VIRTUAL_GPIO_PIN, GPIO_PIN_RESET);
        }
        VIRTUAL_DELAY_1_SYMBOL();
    }
    //如果是偶校验 且 数据有效位中是奇数则发送1 是偶数发0
    if (hvuart->Init.Parity == VIRTUAL_EVENPARITY) {
        if (ctr_bitIsOne % 2 == 1) {
            HAL_GPIO_WritePin(VIRTUAL_GPIO_PORT, VIRTUAL_GPIO_PIN, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(VIRTUAL_GPIO_PORT, VIRTUAL_GPIO_PIN, GPIO_PIN_RESET);
        }
        VIRTUAL_DELAY_1_SYMBOL();
    }
    //停止位输出
    HAL_GPIO_WritePin(VIRTUAL_GPIO_PORT, VIRTUAL_GPIO_PIN, GPIO_PIN_SET);
    VIRTUAL_DELAY_1_SYMBOL();
    if (hvuart->Init.StopBits == VIRTUAL_STOPBITS_2) {
        VIRTUAL_DELAY_1_SYMBOL();
    }
}