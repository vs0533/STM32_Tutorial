#include <stdio.h>

#define POINTER (volatile unsigned int *)0x400208C00

int main() {
    /*加入volatile关键字 就是防止编译器对寄存器进行优化
        比如
        *pointer += 1;
        *pointer += 2;
        编译器会优化为 *pointer += 3;两条语句执行完结果一样的语句被优化为一条
    */
    volatile unsigned int *pointer = (unsigned int *) 0x400208C00;
    *pointer = 1;
    //或者使用宏 一般工程中会这样用 下面语句等同于(volatile unsigned int *)0x400208C00
    *POINTER = 1;
}
