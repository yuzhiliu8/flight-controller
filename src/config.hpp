#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <cstdint>

namespace cfg {
    constexpr uint32_t NUM_LOG_BACKENDS = 4;


    constexpr uint32_t USB_LOGGER_BUF_CAP = 128;
    constexpr uint32_t USB_LOGGER_QUEUE_SIZE = 128;


}


#endif
