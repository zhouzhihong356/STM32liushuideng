#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

/*
 * LED wiring (active high):
 *   PA0 -> 220 ohm -> LED1 anode, LED1 cathode -> GND
 *   PA1 -> 220 ohm -> LED2 anode, LED2 cathode -> GND
 *   PA2 -> 220 ohm -> LED3 anode, LED3 cathode -> GND
 *   PA3 -> 220 ohm -> LED4 anode, LED4 cathode -> GND
 *
 * To use active-low LEDs (3.3V -> LED -> 220 ohm -> GPIO), simply swap
 * Bit_SET/Bit_RESET inside LED_Show() in led.c.
 */
#define LED_GPIO_PORT       GPIOA
#define LED_GPIO_CLK        RCC_APB2Periph_GPIOA

#define LED1_PIN            GPIO_Pin_0
#define LED2_PIN            GPIO_Pin_1
#define LED3_PIN            GPIO_Pin_2
#define LED4_PIN            GPIO_Pin_3

#define LED_ALL_PINS        (LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN)

/* Bit masks used by the running pattern (bit0 = LED1 ... bit3 = LED4) */
#define LED1_MASK           0x01
#define LED2_MASK           0x02
#define LED3_MASK           0x04
#define LED4_MASK           0x08
#define LED_ALL_MASK        0x0F

#define LED_COUNT           4

void LED_Init(void);
void LED_Show(uint8_t pattern);
void LED_AllOff(void);

#endif /* __LED_H */
