#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "delay.h"

/* Time each LED stays on (ms) and the polling slice used for the key */
#define LED_SPEED_MS        200U
#define KEY_SCAN_STEP_MS    10U

/**
  * @brief  Running-light demo with direction control.
  *         PA0..PA3 drive four LEDs (active high).
  *         KEY1 on PA4 toggles the running direction.
  */
int main(void)
{
    uint8_t pattern   = LED1_MASK;   /* only LED1 on at start */
    uint8_t direction = 1U;          /* 1 = LED1 -> LED4, 0 = LED4 -> LED1 */
    uint8_t i;

    LED_Init();
    KEY_Init();
    Delay_Init();

    /* Power-on self test: all four LEDs on for 500 ms, then off */
    LED_Show(LED_ALL_MASK);
    Delay_ms(500U);
    LED_AllOff();
    Delay_ms(500U);

    while (1)
    {
        LED_Show(pattern);

        /* Wait one step, scanning the key every 10 ms so a press reacts fast */
        for (i = 0U; i < (LED_SPEED_MS / KEY_SCAN_STEP_MS); i++)
        {
            Delay_ms(KEY_SCAN_STEP_MS);
            if (KEY_Scan() == KEY_PRES)
            {
                direction = (uint8_t)!direction;
            }
        }

        /* Advance the pattern, wrapping around at both ends */
        if (direction != 0U)
        {
            pattern = (pattern == LED4_MASK) ? LED1_MASK : (uint8_t)(pattern << 1);
        }
        else
        {
            pattern = (pattern == LED1_MASK) ? LED4_MASK : (uint8_t)(pattern >> 1);
        }
    }
}
