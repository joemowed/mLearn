#include <cstdint>
class sys {
  public:
    sys() = delete;
    // enables the Adaptive Real-Time Accelerator (ART)
    static void enableART();
    //
    static void systemCoreClockInit();
    static consteval uint32_t f() { return 2; }
    constexpr static uint32_t i2 = 3 / f();
    struct CoreClockConfig {

        static constexpr uint32_t system_core_clock = 216'000'000;
        static constexpr uint32_t APB1_clock = 100 / sys::f();
        static constexpr uint32_t APB2_clock = system_core_clock / 4;
        static constexpr uint32_t

    } constexpr static coreClockConfig;
};
