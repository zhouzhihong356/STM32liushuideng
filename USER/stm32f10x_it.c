#include "stm32f10x_it.h"

/**
  * @brief  Cortex-M3 exception handlers.
  *         Fault handlers stay in an infinite loop so that a debugger can
  *         catch the failure; the demo does not use any peripheral interrupt.
  */

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
    while (1)
    {
    }
}

void MemManage_Handler(void)
{
    while (1)
    {
    }
}

void BusFault_Handler(void)
{
    while (1)
    {
    }
}

void UsageFault_Handler(void)
{
    while (1)
    {
    }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
}
