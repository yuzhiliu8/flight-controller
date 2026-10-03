/*
 * Main entrypoint for the FC. This fc_main function gets called in the main.c entrypoint
 *
*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "gpio.hpp"
#include "logger.hpp"
#include "logger_backends.hpp"
#include <cstdio>
#include "bmi160_spi.hpp"

// extern I2C_HandleTypeDef hi2c1;

// #define QMC5883P_ADDR   (0x2C << 1)
static UsbVcpLogger usb_logger;

extern "C"
void fc_main(void) {
    GpioPin led(GPIOC, GPIO_PIN_13);
    Logger::add_backend(&usb_logger);
    BMI160 imu;

    // LogRecord record(LogLevel::DBG, "Hello world");


    while (1) {
        led.toggle();
        uint8_t id = imu.read_id();
        Logger::info("0x%02X", id);
        // Logger::error("%s", "Hello world");
        // Logger::debug("%s", "Hello world");
        // usb_logger.write(record);
        osDelay(500);
    }


    vTaskDelete(NULL);
}
