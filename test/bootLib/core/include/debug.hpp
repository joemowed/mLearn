#ifndef __debug__INC__GRD__
#define __debug__INC__GRD__
#include "SEGGER_RTT.hpp"
#include <array>
#include <string>
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
    static void printError(const bool locally_enabled, LogClass log_class, const char *str, ...) {
        if (!locally_enabled) {
            return;
        }
        if (debug::enabled) {
            va_list args;
            va_start(args, str);
            debug::printf(RTT_CTRL_TEXT_RED);
            debug::printf("ERROR: ");
            debug::printf("%s ", log_class.data());
            debug::vprintf(str, &args);
            debug::printf(RTT_CTRL_TEXT_BLACK);
            debug::printf("\n");
            va_end(args);
        }
    }
    static void printOK(const bool locally_enabled, LogClass log_class, const char *str, ...) {
        if (!locally_enabled) {
            return;
        }
        if (debug::enabled) {
            va_list args;
            va_start(args, str);
            debug::printf(RTT_CTRL_TEXT_GREEN);
            debug::printf("OK:    ");
            debug::printf("%s ", log_class.data());
            debug::vprintf(str, &args);
            debug::printf(RTT_CTRL_TEXT_BLACK);
            debug::printf("\n");
            va_end(args);
        }
    }
    static void printInfo(const bool locally_enabled, LogClass log_class, const char *str, ...) {
        if (!locally_enabled) {
            return;
        }
        if (debug::enabled) {
            va_list args;
            va_start(args, str);
            debug::printf("INFO   ");
            debug::printf("%s ", log_class.data());
            debug::vprintf(str, &args);
            debug::printf("\n");
            va_end(args);
        }
    }
};
class debugClient {
  private:
    const bool locally_enabled;

    debug::LogClass log_class;

  public:
    debugClient(std::string log_class, const bool locally_enabled)
        : locally_enabled{locally_enabled} {
        if ((log_class.length() + 1) > sizeof(debug::LogClass)) {
            log_class.erase(sizeof(debug::LogClass) - 2, log_class.length() - 1);
        } else {
            std::string tmp((sizeof(debug::LogClass) - 1) - log_class.length(), ' ');
            log_class += tmp;
        }
        log_class += '\0';
        this->log_class = log_class.c_str();
    }
};
#endif
