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
    void printfTest();
    debugConsole::printf("this is a test\n");
    debugClient dbc("ASR", true);
    std::vector<int> f;
    volatile bool fi = debugConsole::enabled;
    dbc.printOK("WORKING");
    dbc.printError("WORKING");
    dbc.printInfo("WORKING\nWORKING\n");
    f.push_back(2);
    // debugConsole::printInfo(true, "Clock -", "%u", f.at(0));
}

void loop(void) {
    while (1) {
        // RMW(GPIOC->ODR, GPIO_ODR_OD6, 1);
        // RMW(GPIOC->ODR, GPIO_ODR_OD6, 0);
        GPIOC->BSRR = GPIO_BSRR_BS_6;
        GPIOC->BSRR = GPIO_BSRR_BR_6;
    }
}
