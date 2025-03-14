#include "clock.hpp"
#include "reg.hpp"
consteval uint32_t divisionFactorToPLLP(uint32_t division_factor) {
    uint32_t ret = 0;
    switch (division_factor) {
    case 2:
        ret = val2fld(RCC_PLLCFGR_PLLP, 0x0);
    case 4:
        ret = val2fld(RCC_PLLCFGR_PLLP, 0x1);
    case 6:
        ret = val2fld(RCC_PLLCFGR_PLLP, 0x2);
    case 8:
        ret = val2fld(RCC_PLLCFGR_PLLP, 0x3);
    }
    return ret;
}

consteval uint32_t divisionFactorToPPREx(uint32_t division_factor) {
    uint32_t ret = 0;
    switch (division_factor) {
    case 1:
        ret = RCC_CFGR_PPRE1_DIV1;
    case 2:
        ret = RCC_CFGR_PPRE1_DIV2;
    case 4:
        ret = RCC_CFGR_PPRE1_DIV4;
    case 8:
        ret = RCC_CFGR_PPRE1_DIV8;
    case 16:
        ret = RCC_CFGR_PPRE1_DIV16;
    }
    return ret;
}

consteval uint32_t divisionFactorToHPRE(uint32_t division_factor) {

    uint32_t ret = 0;
    switch (division_factor) {
    case 1:
        ret = RCC_CFGR_HPRE_DIV1;
    case 2:
        ret = RCC_CFGR_HPRE_DIV2;
    case 4:
        ret = RCC_CFGR_HPRE_DIV4;
    case 8:
        ret = RCC_CFGR_HPRE_DIV8;
    case 16:
        ret = RCC_CFGR_HPRE_DIV16;
    case 64:
        ret = RCC_CFGR_HPRE_DIV64;
    case 128:
        ret = RCC_CFGR_HPRE_DIV128;
    case 256:
        ret = RCC_CFGR_HPRE_DIV256;
    case 512:
        ret = RCC_CFGR_HPRE_DIV512;
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
    tmp |= divisionFactorToPPREx(clk::APB1_prescaler);
    tmp |= divisionFactorToPPREx(clk::APB2_prescaler);
    tmp |= divisionFactorToHPRE(clk::AHB_prescaler);
    RCC->CFGR = tmp; // set APB1,APB2,and AHB prescalers
}
// only works when mask contains only a single non-zero bit
static void initPeriphrialClock(volatile uint32_t &reg, const uint32_t msk) {
    xRMW(reg, msk);
    while (!xfld2val(msk, RCC->APB1ENR)) {
        // wait for PWR peripherial clock to be online
    }
}
void clk::reset() {}
