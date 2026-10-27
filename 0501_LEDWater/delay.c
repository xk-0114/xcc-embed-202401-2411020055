#include "delay.h"

static uint32_t fac_us=0;

void delay_init(uint8_t SYSCLK)
{
    SysTick->CTRL &= ~(1<<2);
    fac_us = SYSCLK;
}

void delay_us(uint32_t nus)
{
    uint32_t temp;
    SysTick->LOAD = nus*fac_us;
    SysTick->VAL = 0;
    SysTick->CTRL |= 1<<0;
    do
    {
        temp = SysTick->CTRL;
    }while((temp&0x01) && !(temp&(1<<16)));
    SysTick->CTRL &= ~(1<<0);
    SysTick->VAL =0;
}

void delay_ms(uint16_t nms)
{
    uint16_t i;
    for(i=0;i<nms;i++) delay_us(1000);
}