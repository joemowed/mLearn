// called by main, this is entry point.  Runs in loop.
#include "reg.hpp"
#include "stm32f767xx.h"
#include <string>
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
consteval void consteval_error_trigger(std::string);

consteval uint32_t shiftValueToMask(const uint32_t msk, const uint32_t value) {
    int maskStartIndex = 0;
    for (; maskStartIndex < 32; maskStartIndex++) {

        bool curMskBit = (msk & (1U << maskStartIndex));
        if (curMskBit) {
            break;
            // maskStartIndex now is the index of first non-zero bit in mask
        }
    }
    return (value << maskStartIndex);
}
consteval void validateMask(const uint32_t msk) {

    if (msk == 0) {
        consteval_error_trigger("Error: mask is equal to zero.");
    }
    bool inMask = false;
    int i = 0;
    for (; i < 32; i++) {
        bool curMskBit = (msk & (1U << i));
        if ((!inMask) && curMskBit) {
            inMask = true;
        }
        if (inMask) {
            if (!curMskBit) {
                // break when i indexes to first zero after mask
                break;
            }
        }
    }
    // make sure the rest of the mask is zeros
    for (; i < 32; i++) {

        bool curMskBit = (msk & (1U << i));
        if (curMskBit) {
            consteval_error_trigger("Error: mask is fragmented");
        }
    }
}
consteval void validateValue(const uint32_t msk, const uint32_t value) {
    if (false) {
        consteval_error_trigger("test");
    }
    // check lower part, where mask is 0 before first bit in mask
    for (int i = 0; i < 32; i++) {
        bool curValueBit = (value & (1U << i));
        bool curMskBit = (msk & (1U << i));
        if (curMskBit) {
            break;
        }

        if (curValueBit) {
            consteval_error_trigger("Error: value writes bits below mask.");
        }
    }
    int i = 0;
    bool firstFlag = false;
    for (; i < 32; i++) {
        bool curMskBit = msk & (1U << i);
        if (firstFlag) {
            if (!curMskBit) {
                // break at the first zero of the msk,
                // i now indexes the first zero bit of msk
                break;
            }
        }
        if (curMskBit) {
            firstFlag = true;
        }
    }
    // check upper part
    for (; i < 32; i++) {
        bool curValueBit = value & (1U << i);
        if (curValueBit) {
            consteval_error_trigger("Error: value writes bits below mask.");
        }
    }
}
consteval uint32_t validateValueMask(const uint32_t msk, const uint32_t value) {

    validateMask(msk);
    const uint32_t shiftedValue = shiftValueToMask(msk, value);
    validateValue(msk, shiftedValue);
    return shiftedValue;
}
#define RMW(reg, msk, value) (reg = ((reg & (~(msk))) | (validateValueMask(msk, value))))
void loop(void) {
    while (1) {
        RMW(GPIOC->BSRR, GPIO_BSRR_BR6, 1);
        RMW(GPIOC->BSRR, GPIO_BSRR_BS6, 1);
        GPIOC->BSRR = GPIO_BSRR_BR6;
        GPIOC->BSRR = GPIO_BSRR_BS6;
    }
}
