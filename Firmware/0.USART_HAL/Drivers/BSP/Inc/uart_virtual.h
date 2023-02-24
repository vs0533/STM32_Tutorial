#ifndef __UART_H_
#define __UART_H_

#ifdef __cplusplus
extern "C" {
#endif

#define VIRTUAL_GPIO_PORT GPIOA
#define VIRTUAL_GPIO_PIN GPIO_PIN_9

#define VIRTUAL_DATABITS_8 ((uint32_t)0x00)
#define VIRTUAL_DATABITS_9 ((uint32_t)0x01)

#define VIRTUAL_STOPBITS_1 ((uint32_t)0x00)
#define VIRTUAL_STOPBITS_2 ((uint32_t)0x01)

#define VIRTUAL_NOPARITY ((uint32_t)0x00)
#define VIRTUAL_ODDPARITY ((uint32_t)0x01) //奇校验
#define VIRTUAL_EVENPARITY ((uint32_t)0x02) //偶校验

#define VIRTUAL_DELAY_1_SYMBOL() n = 1836; do { __NOP(); } while (n--);

typedef struct {
    uint32_t DataBits;  //数据位长度
    uint32_t Parity;    //奇偶校验位 有或无 ;校验方式 奇校验 或 偶校验
    uint32_t StopBits;  //停止位长度
    uint32_t Baudrate;  //波特率
} VIRTUAL_InitTypeDef;

//串口句柄 句柄就是所有数据的集合 类似类的聚合
typedef struct {
    VIRTUAL_InitTypeDef Init;

} VIRTUAL_HandleTypeDef;

static uint32_t n;
static VIRTUAL_HandleTypeDef hvuart;


void uart_virtual_init(VIRTUAL_HandleTypeDef *hvuart);

void uart_virtual_transmit(VIRTUAL_HandleTypeDef *hvuart, uint16_t *pdata, uint32_t len);

void uart_virtual_sendframe(VIRTUAL_HandleTypeDef *hvuart, uint16_t data);

#ifdef __cplusplus
}
#endif
#endif