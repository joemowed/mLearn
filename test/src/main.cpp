// called by main, this is entry point.  Runs in loop.
#include "reg.hpp"
volatile int _Cnt;
void init(void) {
    uint32_t tmp = val2fld(RCC_PLLCFGR_PLLM, 8U); // divide refrence clock by 8 for main PLL
    tmp |= val2fld(RCC_PLLCFGR_PLLN, 216U);       // multiply by 216 main PLL
    tmp |= val2fld(RCC_PLLCFGR_PLLP, 0U);         // no division on main PLL
    RCC->PLLCFGR = tmp;                           // configure PLLs
    tmp = 0;

    RMW(RCC->CR, RCC_CR_PLLON, 0x1); // turn PLL on

    tmp |= val2fld(RCC_CFGR_PPRE1, 0x5);
    tmp |= val2fld(RCC_CFGR_PPRE2, 0x5);
    tmp |= val2fld(RCC_CFGR_HPRE, 0x0); //
    RCC->CFGR = tmp;                    // set APB1,APB2,and AHB prescalers
    tmp = 0;

    RMW(RCC->APB1ENR, RCC_APB1ENR_PWREN, 1);
    while (!fld2val(RCC_APB1ENR_PWREN, RCC->APB1ENR)) {
        // wait for PWR peripherial clock to be online
    }

    PWR->CR1 |= PWR_CR1_ODEN;                     // set overdrive enable bit
    while (!fld2val(PWR_CSR1_ODRDY, PWR->CSR1)) { // wait for overdrive to be ready
    }

    RMW(PWR->CR1, PWR_CR1_ODSWEN, 1);               // switch to overdrive
    while (!fld2val(PWR_CSR1_ODSWRDY, PWR->CSR1)) { // wait for overdrive switch to complete
    }

    RMW(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_7WS); // set flash to 7 wait states
    RMW(FLASH->ACR, FLASH_ACR_ARTEN, 1);                       // enable ART accelerator (and thus caching)
    RMW(FLASH->ACR, FLASH_ACR_PRFTEN, 1);                      // enable prefetching
    while (!fld2val(RCC_CR_PLLRDY, RCC->CR)) {
        // wait for PLL to be ready
    }
    RMW(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL); // switch system clock to PLL
    RMW(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN, 1);    // enable GPIO clock
    while (!fld2val(RCC_AHB1ENR_GPIOCEN, RCC->AHB1ENR)) {
        // wait for gpio clock enabled
    }
    RMW(GPIOC->MODER, GPIO_MODER_MODER6, 0x1); // 0x1 for output mode
    RMW(GPIOC->OSPEEDR, GPIO_OSPEEDR_OSPEEDR6, 0x3);
}

void loop(void) {
    while (1) {
        // RMW(GPIOC->ODR, GPIO_ODR_OD6, 1);
        // RMW(GPIOC->ODR, GPIO_ODR_OD6, 0);
        GPIOC->BSRR = GPIO_BSRR_BR_6;
        GPIOC->BSRR = GPIO_BSRR_BS_6;
    }
}
