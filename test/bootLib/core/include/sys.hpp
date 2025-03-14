#include <cstdint>
consteval uint32_t f2() { return 3; }
class sys {
  public:
    sys() = delete;
    // enables the Adaptive Real-Time Accelerator (ART)
    static void enableART();
    // turns on overdrive scale 1 within PWR peripherial
    static void enableOverdrive();
    // performs clock/flash/power system initialization
    static void init();
};
