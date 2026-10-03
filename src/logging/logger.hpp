#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <stddef.h>
#include <stdarg.h>
#include "log_types.hpp"
#include "logger_backends.hpp"


// Singleton Logger class
class Logger {
    public:
        Logger() = delete; //prevent instantiation
        static void debug(const char* fmt, ...);
        static void info(const char* fmt, ...);
        static void warn(const char* fmt, ...);
        static void error(const char* fmt, ...);

        static void add_backend(ILoggerBackend* backend);

    private:
        static constexpr uint8_t BACKENDS_CAP = 4;
        static constexpr uint16_t BUF_CAPACITY = 256;

        static void log(LogLevel level, const char* fmt, va_list args);
        static ILoggerBackend* backends_[BACKENDS_CAP];
        // static LogRecord log_buffer[BUF_CAPACITY];
        static uint8_t backend_count_;
};


#endif
