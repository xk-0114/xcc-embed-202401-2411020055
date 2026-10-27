// STM32F407 ??????? PF0~PF7
// ?????????!???????
#define RCC_AHB1ENR   *(volatile unsigned int *)0x40023830
#define GPIOF_MODER   *(volatile unsigned int *)0x40021400
#define GPIOF_OTYPER  *(volatile unsigned int *)0x40021404
#define GPIOF_OSPEEDR *(volatile unsigned int *)0x40021408
#define GPIOF_PUPDR   *(volatile unsigned int *)0x4002140C
#define GPIOF_BSRR    *(volatile unsigned int *)0x40021418

//??????,F4??168MHz
void delay_ms(volatile unsigned int t)
{
    unsigned int i,j;
    for(i = t; i > 0; i--)
        for(j = 1680; j > 0; j--);
}

void LED_Init(void)
{
    //1. ??GPIOF??:AHB1ENR?5??1,??PortF??
    RCC_AHB1ENR |= (1 << 5);

    //2. PF0~PF7 ????????? MODER
    //???PF0~PF7???16bit,????01(??)
    GPIOF_MODER &= ~(0x0000FFFF);
    GPIOF_MODER |=  (0x00005555);

    //3. OTYPER:????,???0
    GPIOF_OTYPER &= ~(0x00FF);

    //4. OSPEEDR:??100MHz
    GPIOF_OSPEEDR &= ~(0x0000FFFF);
    GPIOF_OSPEEDR |=  (0x0000FFFF);

    //5. PUPDR:??????
    GPIOF_PUPDR &= ~(0x0000FFFF);

    //6. BSRR?16??1 = ????,LED????(?????)
    GPIOF_BSRR = (0x00FF << 16);
}

int main(void)
{
    unsigned char i;
    LED_Init();

    while(1)
    {
        //PF0 ? PF7???????
        for(i = 0; i < 8; i++)
        {
            //BSRR?16bit?1 ? ????,??LED
            GPIOF_BSRR = (1 << i);
            delay_ms(300);
            //BSRR?16bit?1 ? ????,??LED
            GPIOF_BSRR = (1 << (i + 16));
        }
    }
}