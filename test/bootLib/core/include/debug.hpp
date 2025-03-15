#ifndef __debug__INC__GRD__
#define __debug__INC__GRD__
#include <cstdint>
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

    static void init();

    static void vprintf(const char *str, va_list *args);
    using LogClass = char[9];
    static void printf(const char *str, ...);
    static void vprintError(const bool locally_enabled, const char *log_class, const char *str,
                            va_list *args);
    static void vprintOK(const bool locally_enabled, const char *log_class, const char *str,
                         va_list *args);
    static void vprintInfo(const bool locally_enabled, const char *log_class, const char *str,
                           va_list *args);
};
/* From SEGGER_RTT_printf:
 *  Notes
 *    (1) Conversion specifications have following syntax:
 *          %[flags][FieldWidth][.Precision]ConversionSpecifier
 *    (2) Supported flags:
 *          -: Left justify within the field width
 *          +: Always print sign extension for signed conversions
 *          0: Pad with 0 instead of spaces. Ignored when using '-'-flag or precision
 *        Supported conversion specifiers:
 *          c: Print the argument as one char
 *          d: Print the argument as a signed integer
 *          u: Print the argument as an unsigned integer
 *          x: Print the argument as an hexadecimal integer
 *          s: Print the string pointed to by the argument
 *          p: Print the argument as an 8-digit hexadecimal integer.
 *          (Argument shall be a pointer to void.)*/

class debugClient {
  private:
    // max number of characters before " - " (e.g 'Clock - ')
    constexpr static uint32_t log_class_name_length = 6;
    constexpr static uint32_t log_class_length = log_class_name_length + sizeof(" - \000");
    const bool locally_enabled;
    std::string trimLogClass(std::string &input_str);
    void copyToPrefix(std::string &prefix);
    using LogClassPrefix = char[log_class_length];
    LogClassPrefix log_class_prefix;

  public:
    debugClient() = delete;
    debugClient(const debugClient &) = delete;
    debugClient &operator=(const debugClient &) = delete;
    debugClient(debugClient &&) = delete;
    debugClient &operator=(debugClient &&) = delete;

    explicit debugClient(std::string log_class, const bool locally_enabled);
    void printError(const char *str, ...);
    void printOK(const char *str, ...);
    void printInfo(const char *str, ...);
};
#endif
