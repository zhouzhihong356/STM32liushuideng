#include "key.h"
#include "delay.h"

/**
  * @brief  Configure PA4 as input pull-up for KEY1.
  */
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(KEY_GPIO_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin  = KEY1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   /* input pull-up */
    GPIO_Init(KEY_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  Non-blocking key scan with 10 ms software debounce.
  * @retval KEY_PRES when a new press is detected, KEY_NONE otherwise.
  *         The function returns KEY_PRES only once per press until the
  *         button is released again.
  */
uint8_t KEY_Scan(void)
{
    static uint8_t key_released = 1;

    if (key_released && (KEY_READ() == Bit_RESET))
    {
        Delay_ms(10);                       /* debounce */
        key_released = 0;
        if (KEY_READ() == Bit_RESET)
        {
            return KEY_PRES;
        }
    }
    else if (KEY_READ() == Bit_SET)
    {
        key_released = 1;                   /* button released */
    }

    return KEY_NONE;
}
