#include "logger.hpp"

#include "stm32f4xx_hal.h"
#include <cstdio>


uint8_t Logger::backend_count_ = 0;
ILoggerBackend* Logger::backends_[BACKENDS_CAP] = { nullptr };
// LogRecord Logger::log_buffer[BUF_CAPACITY] = {};

void Logger::debug(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  log(LogLevel::DBG, fmt, args);
  va_end(args);
}

void Logger::info(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  log(LogLevel::INFO, fmt, args);
  va_end(args);
}

void Logger::warn(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  log(LogLevel::WARN, fmt, args);
  va_end(args);
}

void Logger::error(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  log(LogLevel::ERR, fmt, args);
  va_end(args);
}

// TODO: Move this to a ring buffer, w/ a logger task that flushes output
void Logger::log(LogLevel level, const char* fmt, va_list args) {
  if (fmt == nullptr) {
    return;
  }

  LogRecord record;
  record.log_level = level;
  record.time_ms = HAL_GetTick();
  int result = vsnprintf(record.msg, sizeof(record.msg), fmt, args);

  if (result < 0) {
    return;
  }

  for (int i = 0; i < backend_count_; ++i) {
    if (backends_[i] != nullptr) {
      backends_[i]->write(record);
    }
  }
}


void Logger::add_backend(ILoggerBackend* backend) {
    if (backend_count_ == BACKENDS_CAP) {
        Logger::warn("Cannot add any more logger backends!");
        return;
    }
    backends_[backend_count_++] = backend;
}

