#include "logger_backends.hpp"
#include "logger.hpp"
#include "usb_device.h"


extern "C" {
    extern USBD_HandleTypeDef hUsbDeviceFS;
}

void SdLogger::start_task() {

}

WriteStatus SdLogger::write(const LogRecord& log_record) {

    return WriteStatus::OK;
}


// USB Logger

void UsbVcpLogger::start_task() {

}

WriteStatus UsbVcpLogger::write(const LogRecord& log_record) {

    if (hUsbDeviceFS.dev_state != USBD_STATE_CONFIGURED ||
      hUsbDeviceFS.pClassData == nullptr) {
      return WriteStatus::FAIL;
    }

    const char* dbg_level;
    const char* dbg_color;
    switch (log_record.log_level) {
        case LogLevel::DBG:
            dbg_level = "DEBUG";
            dbg_color = "\033[34m";
            break;
        case LogLevel::INFO:
            dbg_level = "INFO";
            dbg_color = "\033[0m";   // default/white (reset)
            break;
        case LogLevel::WARN:
            dbg_level = "WARN";
            dbg_color = "\033[33m";  // yellow
            break;
        case LogLevel::ERR:
            dbg_level = "ERROR";
            dbg_color = "\033[31m";
            break;
    }

    int len = snprintf(
            buf,
            sizeof(buf),
            "%s[%lu] [%s] %s\033[0m\r\n",
            dbg_color,
            log_record.time_ms,
            dbg_level,
            log_record.msg);


    uint8_t res = CDC_Transmit_FS(reinterpret_cast<uint8_t*>(buf), len);


    if (res != USBD_OK) {
        drop_count_++;
        return WriteStatus::FAIL;
    }
    return WriteStatus::OK;
}

uint32_t UsbVcpLogger::drops() {
    return drop_count_;
}
