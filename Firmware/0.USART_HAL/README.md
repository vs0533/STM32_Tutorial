#### 波特率计算公式

baund = Fck / (16 * USARTDIV)

其中fck ck是下标 fck是串口的时钟，如：USART1的时钟是PCLK2，其他串口都是PCLK1
；PCLK1 PCLK2在cubemx时钟设置里可以设置，这以最大频率举例：
> PCLK1 = 42M \
> PCLK2 = 84M
> 使用串口1（USART1）则频率为84 \
> 9600波特率 = 84000000 / ( 16 * USARTDIV )  = USARTDIV = 84 / (16 * 9600波特率) \
> USARTDIV = 546.875

#### 设置波特率

将USARTDIV的整数和小数部分写入USART_BRR寄存器对应的位即可

```
uint16_t mantissa;
uint16_t fraction;
mantissa = 546;
fraction = 0.875 * 16 + 0.5;   //USARTDIV = DIVMantissa + (DIV_Fraction / 16) \
USART1->BBR=(mantissa << 4) + fraction;
//+0.5主要是为了进行四舍五入 因为uint16_t是整型 为了防止丢位
```

#### 总而言之上面都是理论 实践中直接使用HAL