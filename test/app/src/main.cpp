#include "debug.hpp"
#include "reg.hpp"
debugClient testC();
void init(void) {
    RMW(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN, 1); // enable GPIO clock
    while (!fld2val(RCC_AHB1ENR_GPIOCEN, RCC->AHB1ENR)) {
        // wait for gpio clock enabled
    }
    RMW(GPIOC->MODER, GPIO_MODER_MODER6, 0x1); // 0x1 for output mode
    RMW(GPIOC->OSPEEDR, GPIO_OSPEEDR_OSPEEDR6, 0x3);
}

volatile uint32_t reg;

void loop(void) {}
