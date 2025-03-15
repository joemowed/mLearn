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
void printfTest() {

    volatile int _Cnt;
    // SEGGER_RTT_printf(0,"Float") ;SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0,
    // SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);

    SEGGER_RTT_WriteString(0, "SEGGER Real-Time-Terminal Sample\r\n\r\n");
    SEGGER_RTT_WriteString(0, "###### Testing SEGGER_printf() ######\r\n");

    SEGGER_RTT_printf(0, "printf Test: %%c,         'S' : %c.\r\n", 'S');
    SEGGER_RTT_printf(0, "printf Test: %%5c,        'E' : %5c.\r\n", 'E');
    SEGGER_RTT_printf(0, "printf Test: %%-5c,       'G' : %-5c.\r\n", 'G');
    SEGGER_RTT_printf(0, "printf Test: %%5.3c,      'G' : %-5c.\r\n", 'G');
    SEGGER_RTT_printf(0, "printf Test: %%.3c,       'E' : %-5c.\r\n", 'E');
    SEGGER_RTT_printf(0, "printf Test: %%c,         'R' : %c.\r\n", 'R');

    SEGGER_RTT_printf(0, "printf Test: %%s,      \"RTT\" : %s.\r\n", "RTT");
    SEGGER_RTT_printf(0, "printf Test: %%s, \"RTT\\r\\nRocks.\" : %s.\r\n", "RTT\r\nRocks.");

    SEGGER_RTT_printf(0, "printf Test: %%u,       12345 : %u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%+u,      12345 : %+u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%.3u,     12345 : %.3u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%.6u,     12345 : %.6u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%6.3u,    12345 : %6.3u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%8.6u,    12345 : %8.6u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%08u,     12345 : %08u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%08.6u,   12345 : %08.6u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%0u,      12345 : %0u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%-.6u,    12345 : %-.6u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%-6.3u,   12345 : %-6.3u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%-8.6u,   12345 : %-8.6u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%-08u,    12345 : %-08u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%-08.6u,  12345 : %-08.6u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%-0u,     12345 : %-0u.\r\n", 12345);

    SEGGER_RTT_printf(0, "printf Test: %%u,      -12345 : %u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%+u,     -12345 : %+u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%.3u,    -12345 : %.3u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%.6u,    -12345 : %.6u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%6.3u,   -12345 : %6.3u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%8.6u,   -12345 : %8.6u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%08u,    -12345 : %08u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%08.6u,  -12345 : %08.6u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%0u,     -12345 : %0u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-.6u,   -12345 : %-.6u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-6.3u,  -12345 : %-6.3u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-8.6u,  -12345 : %-8.6u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-08u,   -12345 : %-08u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-08.6u, -12345 : %-08.6u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-0u,    -12345 : %-0u.\r\n", -12345);

    SEGGER_RTT_printf(0, "printf Test: %%d,      -12345 : %d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%+d,     -12345 : %+d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%.3d,    -12345 : %.3d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%.6d,    -12345 : %.6d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%6.3d,   -12345 : %6.3d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%8.6d,   -12345 : %8.6d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%08d,    -12345 : %08d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%08.6d,  -12345 : %08.6d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%0d,     -12345 : %0d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-.6d,   -12345 : %-.6d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-6.3d,  -12345 : %-6.3d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-8.6d,  -12345 : %-8.6d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-08d,   -12345 : %-08d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-08.6d, -12345 : %-08.6d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-0d,    -12345 : %-0d.\r\n", -12345);

    SEGGER_RTT_printf(0, "printf Test: %%x,      0x1234ABC : %x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%+x,     0x1234ABC : %+x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%.3x,    0x1234ABC : %.3x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%.6x,    0x1234ABC : %.6x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%6.3x,   0x1234ABC : %6.3x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%8.6x,   0x1234ABC : %8.6x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%08x,    0x1234ABC : %08x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%08.6x,  0x1234ABC : %08.6x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%0x,     0x1234ABC : %0x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%-.6x,   0x1234ABC : %-.6x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%-6.3x,  0x1234ABC : %-6.3x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%-8.6x,  0x1234ABC : %-8.6x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%-08x,   0x1234ABC : %-08x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%-08.6x, 0x1234ABC : %-08.6x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%-0x,    0x1234ABC : %-0x.\r\n", 0x1234ABC);

    SEGGER_RTT_printf(0, "printf Test: %%p,      &_Cnt      : %p.\r\n", &_Cnt);

    SEGGER_RTT_WriteString(0, "###### SEGGER_printf() Tests done. ######\r\n");
}
