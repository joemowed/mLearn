#ifndef __debug__INC__GRD__
#define __debug__INC__GRD__
#include "SEGGER_RTT.hpp"
#include <cstring>
#include <string>
class debugConsole {
  public:
#ifdef DEBUG
    // this is the global enable switch
    constexpr static bool enabled = true;
#else
    // this is the global enable switch
    constexpr static bool enabled = false;
#endif
    constexpr static unsigned buffer_index = 0;

    static void vprintf(const char *str, va_list *args) {
        if (debugConsole::enabled) {
            SEGGER_RTT_vprintf(debugConsole::buffer_index, str, args);
        }
    }

    using LogClass = char[9];
    static void printf(const char *str, ...) {
        if (debugConsole::enabled) {
            va_list args;
            va_start(args, str);
            SEGGER_RTT_vprintf(debugConsole::buffer_index, str, &args);
            va_end(args);
        }
    }
    static void vprintError(const bool locally_enabled, const char *log_class, const char *str,
                            va_list *args) {
        if (!locally_enabled) {
            return;
        }
        if (debugConsole::enabled) {
            debugConsole::printf(RTT_CTRL_TEXT_RED);
            debugConsole::printf("ERROR: ");
            debugConsole::printf("%s ", log_class);
            debugConsole::vprintf(str, args);
            debugConsole::printf(RTT_CTRL_TEXT_BLACK);
            debugConsole::printf("\n");
        }
    }
    static void vprintOK(const bool locally_enabled, const char *log_class, const char *str,
                         va_list *args) {
        if (!locally_enabled) {
            return;
        }
        if (debugConsole::enabled) {
            debugConsole::printf(RTT_CTRL_TEXT_GREEN);
            debugConsole::printf("OK:    ");
            debugConsole::printf("%s ", log_class);
            debugConsole::vprintf(str, args);
            debugConsole::printf(RTT_CTRL_TEXT_BLACK);
            debugConsole::printf("\n");
        }
    }
    static void vprintInfo(const bool locally_enabled, const char *log_class, const char *str,
                           va_list *args) {
        if (!locally_enabled) {
            return;
        }
        if (debugConsole::enabled) {
            debugConsole::printf("INFO   ");
            debugConsole::printf("%s ", log_class);
            debugConsole::vprintf(str, args);
            debugConsole::printf("\n");
        }
    }
};
class debugClient {
  private:
    // max number of characters before " - " (e.g 'Clock - ')
    constexpr static uint32_t log_class_name_length = 8;
    constexpr static uint32_t log_class_length = log_class_name_length + sizeof(" - \000");

  public:
    using LogClassPrefix = char[log_class_name_length + 4];

  private:
    LogClassPrefix log_class_prefix;
    const bool locally_enabled;
    std::string trimLogClass(std::string &input_str) {
        uint32_t len = input_str.length();
        if (len > this->log_class_name_length) {
            // trim the string to 8 chars
            input_str.resize(this->log_class_name_length);
        }
        if (len < this->log_class_name_length) {
            for (; len <= this->log_class_name_length; len++) {
                // pad the string to the length
                input_str.push_back(' ');
            }
        }
        // add the ' - ' and the null byte
        input_str += " - \000";
        return input_str;
    }
    void copyToPrefix(std::string &prefix) {
        const char *tmp = prefix.c_str();
        memcpy(log_class_prefix, tmp, this->log_class_length);
    }

  public:
    debugClient(const debugClient &) = delete;
    debugClient &operator=(const debugClient &) = delete;
    debugClient(debugClient &&) = delete;
    debugClient &operator=(debugClient &&) = delete;

    debugClient(std::string log_class, const bool locally_enabled)
        // only enable if the global debug switch is also enabled
        : locally_enabled{(debugConsole::enabled && locally_enabled)} {
        std::string tmp = this->trimLogClass(log_class);
        this->copyToPrefix(tmp);
    }
    void printError(const char *str, ...) {
        va_list args;
        va_start(args, str);
        debugConsole::vprintError(this->locally_enabled, this->log_class_prefix, str, &args);
        va_end(args);
    }
    void printOK(const char *str, ...) {
        debugConsole::printf("%s %s", str, this->log_class_prefix);
        va_list args;
        va_start(args, str);
        debugConsole::vprintf(str, &args);
        debugConsole::vprintOK(this->locally_enabled, this->log_class_prefix, str, &args);
        va_end(args);
    }
    void printInfo(const char *str, ...) {
        va_list args;
        va_start(args, str);
        debugConsole::vprintInfo(this->locally_enabled, this->log_class_prefix, str, &args);
        va_end(args);
    }
};
#endif
