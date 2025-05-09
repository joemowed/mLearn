#include "gpio.hpp"

GPIO::Pin::Pin(const uint32_t pin_number, GPIO_TypeDef *const port)
    : pin_number(pin_number), port(port) {}

void GPIO::configPin(const Pin &pin, const RESISTOR resistor, const SPEED speed,
                     const MODE mode) {

    uint32_t resitor_bits, speed_bits, mode_bits;

    switch (resistor) {
        using enum RESISTOR;
    case FLOATING:
        resitor_bits = 0b00;
        break;
    case PULL_UP:
        resitor_bits = 0b01;
        break;
    case PULL_DOWN:
        resitor_bits = 0b10;
        break;
    }
    switch (speed) {
        using enum SPEED;
    case LOW:
        speed_bits = 0b00;
        break;
    case MEDIUM:
        speed_bits = 0b01;
        break;
    case HIGH:
        speed_bits = 0b10;
        break;
    case VERY_HIGH:
        speed_bits = 0b11;
        break;
    }
    switch (mode) {}
};
