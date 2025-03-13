// called by main, this is entry point.  Runs in loop.
#include "reg.hpp"
volatile int _Cnt;
void init(void) {
    // RCC->APB1ENR = RCC_APB1ENR_PWREN;
    // asm("nop");
    // asm("nop");
    // asm("nop");
    // asm("nop");
    // asm("nop");
    // asm("nop");
    // asm("nop");
    // asm("nop");
    // asm("nop");
    // __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    // uint32_t PLLCfg = 0x0;
    // PLLCfg |= _VAL2FLD(RCC_PLLCFGR_PLLM, 0x8);
    // PLLCfg |= _VAL2FLD(RCC_PLLCFGR_PLLN, 100UL);
    // PLLCfg |= _VAL2FLD(RCC_PLLCFGR_PLLP, 0x0);
    //
    // RCC->PLLCFGR = PLLCfg;
    // RCC->CR |= RCC_CR_PLLON;
    //
    // uint32_t RCCCfg = 0x0;
    // RCCCfg |= _VAL2FLD(RCC_CFGR_PPRE1, 0x5);
    // RCCCfg |= _VAL2FLD(RCC_CFGR_PPRE2, 0x5);
    // RCCCfg |= _VAL2FLD(RCC_CFGR_HPRE, 0x0);
    // RCCCfg |= _VAL2FLD(RCC_CFGR_SW, RCC_CFGR_SW_PLL);
    // RCC->CFGR = RCCCfg;
    RCC->AHB1ENR = RCC_AHB1ENR_GPIOCEN;
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    GPIOC->MODER |= GPIO_MODER_MODER6_0;
}

void loop(void) {

    constexpr uint32_t i = val2fld(GPIO_BSRR_BR6, 1) | val2fld(GPIO_BSRR_BR7, 1);
    RMW(GPIOC->BSRR, GPIO_BSRR_BR6, 1);
    RMW(GPIOC->BSRR, GPIO_BSRR_BS6, 1);
    GPIOC->BSRR = ((GPIOC->BSRR & (~(GPIO_BSRR_BR6))) | (1U << GPIO_BSRR_BR6_Pos));
    GPIOC->BSRR = ((GPIOC->BSRR & (~(GPIO_BSRR_BS6))) | (1U << GPIO_BSRR_BS6_Pos));
}
