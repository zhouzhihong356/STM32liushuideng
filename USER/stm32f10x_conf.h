/**
  ******************************************************************************
  * @file    stm32f10x_conf.h
  * @brief   Standard peripheral library configuration for this project.
  *          Only the modules used by the running-light demo are enabled.
  ******************************************************************************
  */

#ifndef __STM32F10x_CONF_H
#define __STM32F10x_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Peripherals used by this project */
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

/* Uncomment the next line to enable full assertion checks in the library */
/* #define USE_FULL_ASSERT    1 */

#ifdef  USE_FULL_ASSERT
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_CONF_H */
