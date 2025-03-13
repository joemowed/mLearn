#ifndef REG_INC_GRD
#define REG_INC_GRD

#include "stm32f767xx.h"
#include <cstdint>
#include <string>

#define SILENCE_UNUSED_INCLUDE_WARN_REG_INC GPIOC

consteval void consteval_error_trigger(std::string errMessage);

consteval uint32_t shiftValueToMask(const uint32_t msk, const uint32_t value) {
    int maskStartIndex = 0;
    for (; maskStartIndex < 32; maskStartIndex++) {

        bool curMskBit = (msk & (1U << maskStartIndex));
        if (curMskBit) {
            break;
            // maskStartIndex now is the index of first non-zero bit in mask
        }
    }
    return (value << maskStartIndex);
}
consteval uint32_t validateMask(const uint32_t msk) {

    if (msk == 0) {
        consteval_error_trigger("Error: mask is equal to zero.");
    }
    bool inMask = false;
    int i = 0;
    for (; i < 32; i++) {
        bool curMskBit = (msk & (1U << i));
        if ((!inMask) && curMskBit) {
            inMask = true;
        }
        if (inMask) {
            if (!curMskBit) {
                // break when i indexes to first zero after mask
                break;
            }
        }
    }
    // make sure the rest of the mask is zeros
    for (; i < 32; i++) {

        bool curMskBit = (msk & (1U << i));
        if (curMskBit) {
            consteval_error_trigger("Error: mask is fragmented");
        }
    }
    return msk;
}
consteval uint32_t validateValue(const uint32_t msk, const uint32_t value) {
    if (false) {
        consteval_error_trigger("test");
    }
    // check lower part, where mask is 0 before first bit in mask
    for (int i = 0; i < 32; i++) {
        bool curValueBit = (value & (1U << i));
        bool curMskBit = (msk & (1U << i));
        if (curMskBit) {
            break;
        }

        if (curValueBit) {
            consteval_error_trigger("Error: value writes bits below mask.");
        }
    }
    int i = 0;
    bool firstFlag = false;
    for (; i < 32; i++) {
        bool curMskBit = msk & (1U << i);
        if (firstFlag) {
            if (!curMskBit) {
                // break at the first zero of the msk,
                // i now indexes the first zero bit of msk
                break;
            }
        }
        if (curMskBit) {
            firstFlag = true;
        }
    }
    // check upper part
    for (; i < 32; i++) {
        bool curValueBit = value & (1U << i);
        if (curValueBit) {
            consteval_error_trigger("Error: value writes bits below mask.");
        }
    }
    return value;
}
consteval uint32_t val2fld(const uint32_t msk, const uint32_t value) {

    validateMask(msk);
    const uint32_t shiftedValue = shiftValueToMask(msk, value);
    validateValue(msk, shiftedValue);
    return shiftedValue;
}
#define RMW(reg, msk, value) (reg = ((reg & (~(msk))) | (val2fld(msk, value))))
#define fld2val(msk, reg) (((uint32_t)(reg) << (msk##_Pos) & validateMask(msk##_Msk))
#endif
