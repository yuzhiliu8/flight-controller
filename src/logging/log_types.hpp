#ifndef LOG_TYPES_HPP
#define LOG_TYPES_HPP

#include <cstdint>
#include <cstdio>
#include "stm32f4xx_hal.h"

enum class LogLevel {
    DBG,
    INFO,
    WARN,
    ERR
};

struct LogRecord {
    LogLevel log_level;
    uint32_t time_ms;
    char msg[64];

    LogRecord() = default;
    LogRecord(LogLevel level, const char* message)
        : log_level(level), time_ms(HAL_GetTick())
    {
      // snprintf(msg, sizeof(msg), "%s", message == nullptr ? message : "");
      snprintf(msg, sizeof(msg), "%s", message ? message : "");

    }
};

enum class WriteStatus {
    OK = 0,
    FAIL = 1
};

#endif
