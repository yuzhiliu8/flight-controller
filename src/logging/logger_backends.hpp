#ifndef LOGGER_BACKEND_HPP
#define LOGGER_BACKEND_HPP

#include "usbd_cdc_if.h"
#include "usbd_def.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "log_types.hpp"
#include "config.hpp"

class ILoggerBackend {
    public:
        virtual void start_task() = 0;
        virtual WriteStatus write(const LogRecord& log_record) = 0;
        virtual uint32_t drops() = 0;
};

class SdLogger
: public ILoggerBackend
{
    public:
        SdLogger() {};
        void start_task() override;
        WriteStatus write(const LogRecord& log_record) override;
        uint32_t drops() override;

    private:
        uint32_t drop_count_{};


};



class UsbVcpLogger
: public ILoggerBackend
{
    public:
        UsbVcpLogger() {};
        void start_task() override;
        WriteStatus write(const LogRecord& log_record) override;
        uint32_t drops() override;

    private:
        uint32_t drop_count_{};
        char buf[96];
        LogRecord queue_buffer[cfg::USB_LOGGER_QUEUE_SIZE];
        QueueHandle_t log_queue_;

};


#endif
