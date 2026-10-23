#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

/*
 * KEY1 wiring:
 *   PA4 ---- push button ---- GND
 *   PA4 is configured as input pull-up, so it reads 1 when released
 *   and 0 when pressed.
 */
#define KEY_GPIO_PORT       GPIOA
#define KEY_GPIO_CLK        RCC_APB2Periph_GPIOA
#define KEY1_PIN            GPIO_Pin_4

#define KEY_READ()          GPIO_ReadInputDataBit(KEY_GPIO_PORT, KEY1_PIN)

#define KEY_NONE            0
#define KEY_PRES            1

void KEY_Init(void);
uint8_t KEY_Scan(void);

#endif /* __KEY_H */
