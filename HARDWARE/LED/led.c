#include "led.h"

/**
  * @brief  Configure PA0..PA3 as push-pull outputs and turn all LEDs off.
  */
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable the GPIOA clock (APB2) */
    RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin   = LED_ALL_PINS;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);

    LED_AllOff();
}

/**
  * @brief  Drive the four LEDs according to a bit pattern.
  * @param  pattern: bit0 -> PA0 (LED1), bit1 -> PA1 ... bit3 -> PA3 (LED4)
  *                  A '1' bit turns the corresponding LED on (active high).
  */
void LED_Show(uint8_t pattern)
{
    GPIO_WriteBit(LED_GPIO_PORT, LED1_PIN,
                  (BitAction)((pattern & LED1_MASK) ? Bit_SET : Bit_RESET));
    GPIO_WriteBit(LED_GPIO_PORT, LED2_PIN,
                  (BitAction)((pattern & LED2_MASK) ? Bit_SET : Bit_RESET));
    GPIO_WriteBit(LED_GPIO_PORT, LED3_PIN,
                  (BitAction)((pattern & LED3_MASK) ? Bit_SET : Bit_RESET));
    GPIO_WriteBit(LED_GPIO_PORT, LED4_PIN,
                  (BitAction)((pattern & LED4_MASK) ? Bit_SET : Bit_RESET));
}

/**
  * @brief  Turn off all LEDs.
  */
void LED_AllOff(void)
{
    GPIO_ResetBits(LED_GPIO_PORT, LED_ALL_PINS);
}
