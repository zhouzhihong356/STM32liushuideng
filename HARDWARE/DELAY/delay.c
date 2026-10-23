#include "delay.h"

static uint32_t fac_us = 0;

/**
  * @brief  Prepare the SysTick timer for 1 us time base.
  */
void Delay_Init(void)
{
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->CTRL |=  SysTick_CTRL_CLKSOURCE_Msk;   /* clock source = HCLK */

    fac_us = SystemCoreClock / 1000000U;            /* ticks per microsecond */
}

/**
  * @brief  Microsecond delay (busy wait on SysTick).
  * @param  us: 1 .. 1864 at 72 MHz (SysTick is a 24-bit counter)
  */
void Delay_us(uint32_t us)
{
    uint32_t temp;

    if (us == 0U)
    {
        return;
    }

    SysTick->LOAD = us * fac_us;
    SysTick->VAL  = 0U;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    do
    {
        temp = SysTick->CTRL;
    }
    while ((temp & SysTick_CTRL_ENABLE_Msk) &&
           !(temp & SysTick_CTRL_COUNTFLAG_Msk));

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL   = 0U;
}

/**
  * @brief  Millisecond delay.
  * @param  ms: number of milliseconds
  */
void Delay_ms(uint16_t ms)
{
    while (ms--)
    {
        Delay_us(1000U);
    }
}
