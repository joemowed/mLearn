#include "debug.hpp"
#include "reg.hpp"
#include <vector>
void init(void) {
    RMW(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN, 1); // enable GPIO clock
    while (!fld2val(RCC_AHB1ENR_GPIOCEN, RCC->AHB1ENR)) {
        // wait for gpio clock enabled
    }
    RMW(GPIOC->MODER, GPIO_MODER_MODER6, 0x1); // 0x1 for output mode
    RMW(GPIOC->OSPEEDR, GPIO_OSPEEDR_OSPEEDR6, 0x3);
}

void loop(void) {
    debugClient dbc("TEST", true);
    volatile void *v = malloc(32768);
    std::vector<int> vc;
    for (int i = 0; i < UINT32_MAX; i++) {
        vc.push_back(i);
    }
    while (1) {
        // RMW(GPIOC->ODR, GPIO_ODR_OD6, 1);
        // RMW(GPIOC->ODR, GPIO_ODR_OD6, 0);
        GPIOC->BSRR = GPIO_BSRR_BS_6;
        GPIOC->BSRR = GPIO_BSRR_BR_6;
    }
}
