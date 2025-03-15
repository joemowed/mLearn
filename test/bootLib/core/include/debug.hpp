#ifndef __debug__INC__GRD__
#define __debug__INC__GRD__
#include "SEGGER_RTT.hpp"
class debug {
  private:
#ifdef DEBUG
    constexpr static bool enabled = true;
#else
    constexpr static bool enabled = false;
#endif
    constexpr static unsigned buffer_index = 0;

    static void vprintf(const char *str, va_list *args) {
        if (debug::enabled) {
            SEGGER_RTT_vprintf(debug::buffer_index, str, args);
        }
    }

  public:
    using LogClass = char[9];
    static void printf(const char *str, ...) {
        if (debug::enabled) {
            va_list args;
            va_start(args, str);
            SEGGER_RTT_vprintf(debug::buffer_index, str, &args);
            va_end(args);
        }
    }
    static void printErr(const bool locally_enabled, const char *log_class, const char *str, ...) {
        if (!locally_enabled) {
            return;
        }
        if (debug::enabled) {
            va_list args;
            va_start(args, str);
            debug::printf(RTT_CTRL_TEXT_RED);
            debug::printf("ERROR: ");
            debug::printf("%s ", log_class);
            debug::vprintf(str, &args);
            debug::printf(RTT_CTRL_TEXT_BLACK);
            debug::printf("\n");
            va_end(args);
        }
    }
    static void printOK(const bool locally_enabled, const char *log_class, const char *str, ...) {
        if (!locally_enabled) {
            return;
        }
        if (debug::enabled) {
            va_list args;
            va_start(args, str);
            debug::printf(RTT_CTRL_TEXT_GREEN);
            debug::printf("OK:    ");
            debug::printf("%s ", log_class);
            debug::vprintf(str, &args);
            debug::printf(RTT_CTRL_TEXT_BLACK);
            debug::printf("\n");
            va_end(args);
        }
    }
    static void printInfo(const bool locally_enabled, const char *log_class, const char *str, ...) {
        if (!locally_enabled) {
            return;
        }
        if (debug::enabled) {
            va_list args;
            va_start(args, str);
            debug::printf("INFO   ");
            debug::printf("%s ", log_class);
            debug::vprintf(str, &args);
            debug::printf("\n");
            va_end(args);
        }
    }
};
#endif
