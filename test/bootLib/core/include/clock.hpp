#ifndef __clock__INC_GRD__
#define __clock__INC_GRD__
#include "debug.hpp"
#include "reg.hpp"
#include <cstdint>
class clk {
  private:
    static constexpr uint32_t PLL_osc_source = RCC_PLLCFGR_PLLSRC_HSI;
    static constexpr uint32_t PLLP_prescaler = 2; // valid values are 2,4,6,8
    static constexpr uint32_t osc_input_clock = 16'000'000;
    static constexpr uint32_t osc_input_source = RCC_CFGR_SW_HSI;
    static constexpr uint32_t PLLM_prescaler = 8; // divide osc input clock by 8
    static constexpr uint32_t PLLN_mult_factor = 216;
    static constexpr uint32_t APB2_prescaler = 4; // valid values are 1,2,4,8,16
    static constexpr uint32_t APB1_prescaler = 4; // valid values are 1,2,4,8,16
    static constexpr uint32_t AHB_prescaler = 1;  // valid values are 1,2,4,8,16,64,128,256,512
    static constexpr uint32_t system_core_clock = (((osc_input_clock / PLLM_prescaler) * PLLN_mult_factor) / PLLP_prescaler);
    static constexpr uint32_t APB1_timer_clock = system_core_clock * 2 / APB1_prescaler;
    static constexpr uint32_t APB2_timer_clock = system_core_clock * 2 / APB2_prescaler;
    static constexpr uint32_t APB1_clock = system_core_clock / APB1_prescaler;
    static constexpr uint32_t APB2_clock = system_core_clock / APB2_prescaler;
    static constexpr uint32_t AHB_clock = system_core_clock / AHB_prescaler;
    static bool is_clock_initialized;
    static constexpr uint32_t system_core_clock_reset = 16'000'000;
    constexpr static bool logging_active = true;
    constexpr static debugConsole::LogClass log_class = "Clock  -";
    static void logClock(const uint32_t freq, const char *clock_name);

  public:
    static void infoClocks();
    static float toMHZ(const uint32_t freq);
    static uint32_t getSystemCoreClock();
    static uint32_t getAPB1Clock();
    static uint32_t getAHBClock();
    static uint32_t getAPB2Clock();
    static uint32_t getAPB1TimerClock();
    static uint32_t getAPB2TimerClock();

    static void initPeriphrialClock(volatile uint32_t &reg, const uint32_t msk);
    // starts clocks as configured in the clk class header
    static void init();
    // resets clocks to reset state
    static void reset();
    clk() = delete;
};

#endif
