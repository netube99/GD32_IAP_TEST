#include "gd32f30x.h"
#include "systick.h"
#include "main.h"

#define NEED_UPDATE                             0
#define USER_FLASH_BANK0_FIRST_PAGE_ADDRESS     0x8010000

void(*Jump_To_Application)();

void led_init(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5);
    gpio_bit_reset(GPIOB, GPIO_PIN_5);
    gpio_bit_set(GPIOB, GPIO_PIN_0);
    delay_1ms(2000);
}

int main(void)
{
    systick_config();
    led_init();
    if(NEED_UPDATE)
    {
        //擦写APP
    }
    else
    {
        //跳转到APP
        //检查APP地址首位是否为栈顶指针，如果为真则APP存在
        if (0x20000000 == ((*(__IO uint32_t*)USER_FLASH_BANK0_FIRST_PAGE_ADDRESS) & 0x2FFE0000))
        {
            //关闭全局中断
            nvic_irq_disable(EXTI0_IRQn);
            //设置APP的跳转地址
            Jump_To_Application = *(__IO uint32_t*)(USER_FLASH_BANK0_FIRST_PAGE_ADDRESS + 4);
            //MSP设置为APP首地址保存的栈顶指针
            __set_MSP(*(__IO uint32_t*) USER_FLASH_BANK0_FIRST_PAGE_ADDRESS);
            //CPU跳转到APP
            Jump_To_Application();
        }
    }
    while(1)
    {

    }
}
