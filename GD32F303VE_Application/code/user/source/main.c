#include "gd32f30x.h"
#include "systick.h"
#include "main.h"

#define APP_OFFSET      0x10000

int main(void)
{
    //重定向中断向量表
		nvic_vector_table_set(NVIC_VECTTAB_FLASH, APP_OFFSET);
		gpio_bit_set(GPIOB, GPIO_PIN_5);
    //开启全局中断
    __enable_irq();
    while(1)
    {
        gpio_bit_reset(GPIOB, GPIO_PIN_0);
        delay_1ms(100);
        gpio_bit_set(GPIOB, GPIO_PIN_0);
        delay_1ms(100);
    }
}
