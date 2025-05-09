#include "stm32f767xx.h"
#include <cstdint>

namespace GPIO {

//"FLOATING" is open drain when pin is in output mode (STM32F7)
enum class RESISTOR { FLOATING, PULL_DOWN, PULL_UP };
enum class SPEED { LOW, MEDIUM, HIGH, VERY_HIGH };
enum class MODE { OUTPUT, AF, INPUT, ANALOG };

class Pin {
  public:
    // pin number in port (i.e. 13 for pin A13)
    const uint32_t pin_number;

    // refrence to the port
    GPIO_TypeDef *const port;
    Pin() = delete;
    Pin(const uint32_t pin_number, GPIO_TypeDef *const port);
};

void configPin(const Pin &pin, const RESISTOR resistor, const SPEED speed,
               const MODE mode);
} // namespace GPIO
