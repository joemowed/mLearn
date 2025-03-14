#include "clock.hpp"
#include "reg.hpp"
consteval uint32_t divisionFactorToPLLP(uint32_t division_factor) {
    uint32_t ret = 0;
    switch (division_factor) {
    case 2:
        ret = val2fld(RCC_PLLCFGR_PLLP, 0x0);
        break;
    case 4:
        ret = val2fld(RCC_PLLCFGR_PLLP, 0x1);
        break;
    case 6:
        ret = val2fld(RCC_PLLCFGR_PLLP, 0x2);
        break;
    case 8:
        ret = val2fld(RCC_PLLCFGR_PLLP, 0x3);
        break;
    default:
        consteval_error_trigger("Error: invalid clock prescaler selection");
    }
    return ret;
}

consteval uint32_t divisionFactorToPPRE1(uint32_t division_factor) {
    uint32_t ret = 0;
    switch (division_factor) {
    case 1:
        ret = RCC_CFGR_PPRE1_DIV1;
        break;
    case 2:
        ret = RCC_CFGR_PPRE1_DIV2;
        break;
    case 4:
        ret = RCC_CFGR_PPRE1_DIV4;
        break;
    case 8:
        ret = RCC_CFGR_PPRE1_DIV8;
        break;
    case 16:
        ret = RCC_CFGR_PPRE1_DIV16;
        break;
    default:
        consteval_error_trigger("Error: invalid clock prescaler selection");
    }
    return ret;
}
consteval uint32_t divisionFactorToPPRE2(uint32_t division_factor) {
    uint32_t ret = 0;
    switch (division_factor) {
    case 1:
        ret = RCC_CFGR_PPRE2_DIV1;
        break;
    case 2:
        ret = RCC_CFGR_PPRE2_DIV2;
        break;
    case 4:
        ret = RCC_CFGR_PPRE2_DIV4;
        break;
    case 8:
        ret = RCC_CFGR_PPRE2_DIV8;
        break;
    case 16:
        ret = RCC_CFGR_PPRE2_DIV16;
        break;
    default:
        consteval_error_trigger("Error: invalid clock prescaler selection");
    }
    return ret;
}

consteval uint32_t divisionFactorToHPRE(uint32_t division_factor) {

    uint32_t ret = 0;
    switch (division_factor) {
    case 1:
        ret = RCC_CFGR_HPRE_DIV1;
        break;
    case 2:
        ret = RCC_CFGR_HPRE_DIV2;
        break;
    case 4:
        ret = RCC_CFGR_HPRE_DIV4;
        break;
    case 8:
        ret = RCC_CFGR_HPRE_DIV8;
        break;
    case 16:
        ret = RCC_CFGR_HPRE_DIV16;
        break;
    case 64:
        ret = RCC_CFGR_HPRE_DIV64;
        break;
    case 128:
        ret = RCC_CFGR_HPRE_DIV128;
        break;
    case 256:
        ret = RCC_CFGR_HPRE_DIV256;
        break;
    case 512:
        ret = RCC_CFGR_HPRE_DIV512;
        break;
    default:
        consteval_error_trigger("Error: invalid clock prescaler selection");
    }
    return ret;
}

uint32_t clk::getSystemCoreClock() {
    if (clk::isInitialized) {
        return clk::system_core_clock;
    } else {
        return clk::system_core_clock_reset;
    }
}
uint32_t clk::getAPB1Clock() {

    if (clk::isInitialized) {
        return clk::APB1_clock;
    } else {
        return clk::system_core_clock_reset;
    }
}
uint32_t clk::getAPB2Clock() {

    if (clk::isInitialized) {
        return clk::APB2_clock;
    } else {
        return clk::system_core_clock_reset;
    }
}
uint32_t clk::getAPB1TimerClock() {

    if (clk::isInitialized) {
        return clk::APB1_timer_clock;
    } else {
        return clk::system_core_clock_reset;
    }
}
uint32_t clk::getAPB2TimerCLock() {

    if (clk::isInitialized) {
        return clk::APB2_timer_clock;
    } else {
        return clk::system_core_clock_reset;
    }
}
void clk::init() {

    uint32_t tmp = 0;
    tmp |= val2fld(RCC_PLLCFGR_PLLM, clk::PLLM_prescaler);   // divide refrence clock by x for main PLL
    tmp |= val2fld(RCC_PLLCFGR_PLLN, clk::PLLN_mult_factor); // multiply by x main PLL
    tmp |= divisionFactorToPLLP(clk::PLLP_prescaler);        // division on main PLL
    RCC->PLLCFGR = tmp;                                      // configure PLLs

    RMW(RCC->CR, RCC_CR_PLLON, 0x1); // turn PLL on

    tmp = 0;
    tmp |= divisionFactorToPPRE1(clk::APB1_prescaler);
    tmp |= divisionFactorToPPRE2(clk::APB2_prescaler);
    tmp |= divisionFactorToHPRE(clk::AHB_prescaler);
    RCC->CFGR = tmp; // set APB1,APB2,and AHB prescalers

    while (!fld2val(RCC_CR_PLLRDY, RCC->CR)) {
        // wait for PLL to be ready
    }
    RMW(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL); // switch system clock to PLL
}
// only works when mask contains only a single non-zero bit
void clk::initPeriphrialClock(volatile uint32_t &reg, const uint32_t msk) {
    xRMW(reg, msk);
    while (!xfld2val(msk, RCC->APB1ENR)) {
        // wait for peripherial clock to be online
    }
}
void clk::reset() {}
