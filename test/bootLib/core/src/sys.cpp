#include "sys.hpp"
#include "clock.hpp"
#include "debug.hpp"
#include "reg.hpp"

debugClient sys::dbc("SYSTEM", true);
void sys::enableOverdrive() {
    clk::initPeriphrialClock(RCC->APB1ENR,
                             RCC_APB1ENR_PWREN); // enable PWR periphrial clock
    PWR->CR1 |= PWR_CR1_ODEN;                    // set overdrive enable bit
    while (
        !fld2val(PWR_CSR1_ODRDY, PWR->CSR1)) { // wait for overdrive to be ready
    }

    RMW(PWR->CR1, PWR_CR1_ODSWEN, 1); // switch to overdrive
    while (!fld2val(PWR_CSR1_ODSWRDY,
                    PWR->CSR1)) { // wait for overdrive switch to complete
    }
    dbc.printOK("PWR overdrive mode active");
}
void sys::enableART() {
    RMW(FLASH->ACR, FLASH_ACR_LATENCY,
        FLASH_ACR_LATENCY_7WS); // set flash to 7 wait states
    RMW(FLASH->ACR, FLASH_ACR_ARTEN,
        1); // enable ART accelerator (and thus caching)
    RMW(FLASH->ACR, FLASH_ACR_PRFTEN, 1); // enable prefetching
    dbc.printOK("ART enabled");
}
void sys::init() {
    debugConsole::init();
    dbc.printInfo("System start up initialized, RTT enabled");
    sys::enableOverdrive();
    sys::enableART();
    clk::init();
}
