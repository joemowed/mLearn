#include "debug.hpp"
#include "SEGGER_RTT.hpp"

debugClient::debugClient(std::string log_class, const bool locally_enabled)
    // only enable if the global debug switch is also enabled
    : locally_enabled((debugConsole::enabled & locally_enabled)) {
    std::string tmp = this->trimLogClass(log_class);
    this->copyToPrefix(tmp);
}
void debugClient::printError(const char *str, ...) {
    va_list args;
    va_start(args, str);
    debugConsole::vprintError(this->locally_enabled, this->log_class_prefix, str, &args);
    va_end(args);
}
void debugClient::printOK(const char *str, ...) {
    va_list args;
    va_start(args, str);
    debugConsole::vprintOK(this->locally_enabled, this->log_class_prefix, str, &args);
    va_end(args);
}
void debugClient::printInfo(const char *str, ...) {
    va_list args;
    va_start(args, str);
    debugConsole::vprintInfo(this->locally_enabled, this->log_class_prefix, str, &args);
    va_end(args);
}
std::string debugClient::trimLogClass(std::string &input_str) {
    uint32_t len = input_str.length();
    if (len > this->log_class_name_length) {
        // trim the string to the name length
        input_str.resize(this->log_class_name_length);
    }
    if (len < this->log_class_name_length) {
        for (; len < this->log_class_name_length; len++) {
            // pad the string to the length
            input_str.push_back(' ');
        }
    }
    // add the ' - ' and the null byte
    input_str += " - \000";
    return input_str;
}
void debugClient::copyToPrefix(std::string &prefix) {
    const char *tmp = prefix.c_str();
    memcpy(log_class_prefix, tmp, this->log_class_length);
}

void debugConsole::vprintf(const char *str, va_list *args) {
    if (debugConsole::enabled) {
        SEGGER_RTT_vprintf(debugConsole::buffer_index, str, args);
    }
}
void debugConsole::printf(const char *str, ...) {
    if (debugConsole::enabled) {
        va_list args;
        va_start(args, str);
        SEGGER_RTT_vprintf(debugConsole::buffer_index, str, &args);
        va_end(args);
    }
}
void debugConsole::vprintError(const bool locally_enabled, const char *log_class, const char *str,
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
void debugConsole::vprintOK(const bool locally_enabled, const char *log_class, const char *str,
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
void debugConsole::vprintInfo(const bool locally_enabled, const char *log_class, const char *str,
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
void debugConsole::init() { SEGGER_RTT_Init(); }
