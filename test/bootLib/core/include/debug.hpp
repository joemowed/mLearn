#include "SEGGER_RTT.hpp"
class debug {
  private:
    constexpr static bool enabled = true;
    constexpr static unsigned bufferIndex = 0;

  public:
    static void printf(const char *str, ...) {
        if (debug::enabled) {
            va_list args;
            SEGGER_RTT_vprintf(debug::bufferIndex, str, &args);
        }
    }
};
