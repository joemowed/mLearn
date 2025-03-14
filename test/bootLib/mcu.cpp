// SystemInit called by startup.asm, executes after reset
#include "stm32f767xx.h"
extern "C" void SystemInit(void) {

#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10 and CP11 Full Access */
#endif
}
namespace MCU {}
